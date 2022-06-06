/*
	Cute Framework
	Copyright (C) 2019 Randy Gaul https://randygaul.net

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#include <cute_ecs.h>
#include <cute_c_runtime.h>
#include <cute_kv.h>
#include <cute_defer.h>
#include <cute_string.h>

#include <internal/cute_app_internal.h>
#include <internal/cute_object_table_internal.h>

#define INJECT(s) cf_strpool_inject(cf_app->strpool, s, (int)CUTE_STRLEN(s))

static cf_error_t cf_s_load_from_schema(cf_entity_type_t schema_type, cf_entity_t entity, cf_component_config_t* config, void* component, void* udata)
{
	// Look for parent.
	// If parent exists, load values from it first.
	cf_entity_type_t inherits_from = CF_INVALID_ENTITY_TYPE;
	cf_error_t err = cf_app->entity_schema_inheritence.find(schema_type, &inherits_from);
	if (!err.is_error()) {
		err = cf_s_load_from_schema(inherits_from, entity, config, component, udata);
		if (err.is_error()) return err;
	}

	cf_kv_t* schema = NULL;
	err = cf_app->entity_parsed_schemas.find(schema_type, &schema);
	if (err.is_error()) {
		err = cf_error_success();
		if (config->serializer_fn) err = config->serializer_fn(schema, true, entity, component, udata);
	} else {
		err = cf_kv_object_begin(schema, config->name);
		if (!err.is_error()) {
			if (config->serializer_fn) err = config->serializer_fn(schema, true, entity, component, udata);
			if (err.is_error()) return err;
			err = cf_kv_object_end(schema);
		}
	}

	return err;
}

//--------------------------------------------------------------------------------------------------

void cf_ecs_system_begin()
{
	cf_app->system_internal_builder.clear();
}

void cf_ecs_system_end()
{
	cf_app->systems.add(cf_app->system_internal_builder);
}

void cf_ecs_system_set_name(const char* name)
{
	cf_app->system_internal_builder.name = INJECT(name);
}

void cf_ecs_system_set_update(void* update_fn)
{
	cf_app->system_internal_builder.update_fn = update_fn;
}

void cf_ecs_system_require_component(const char* component_type)
{
	cf_app->system_internal_builder.component_type_tuple.add(INJECT(component_type));
}

void cf_ecs_system_set_optional_pre_update(void (*pre_update_fn)(float dt, void* udata))
{
	cf_app->system_internal_builder.pre_update_fn = pre_update_fn;
}

void cf_ecs_system_set_optional_post_update(void (*post_update_fn)(float dt, void* udata))
{
	cf_app->system_internal_builder.post_update_fn = post_update_fn;
}

void cf_ecs_system_set_optional_update_udata(void* udata)
{
	cf_app->system_internal_builder.udata = udata;
}

static CUTE_INLINE uint16_t cf_s_entity_type(cf_entity_t entity)
{
	return (uint16_t)((entity.handle & 0x00000000FFFF0000ULL) >> 16);
}

cf_entity_t cf_entity_make(const char* entity_type, cf_error_t* err_out)
{
	cf_entity_type_t type = CF_INVALID_ENTITY_TYPE;
	cf_app->entity_type_string_to_id.find(INJECT(entity_type), &type);
	if (type == CF_INVALID_ENTITY_TYPE) {
		if (err_out) *err_out = cf_error_failure("`entity_type` is not valid.");
		return CF_INVALID_ENTITY;
	}

	cf_entity_collection_t* collection = cf_app->entity_collections.find(type);
	CUTE_ASSERT(collection);

	int index = collection->entity_handles.count();
	cf_handle_t h = collection->entity_handle_table.alloc_handle(index, type);
	collection->entity_handles.add(h);
	cf_entity_t entity = { h };

	const cf_array<cf_strpool_id>& component_type_tuple = collection->component_type_tuple;
	for (int i = 0; i < component_type_tuple.count(); ++i)
	{
		cf_strpool_id component_type = component_type_tuple[i];
		cf_component_config_t* config = cf_app->component_configs.find(component_type);

		if (!config) {
			if (err_out) *err_out = cf_error_failure("Unable to find component config.");
			return CF_INVALID_ENTITY;
		}

		void* component = collection->component_tables[i].add();
		cf_error_t err = cf_s_load_from_schema(type, entity, config, component, config->serializer_udata);
		if (err.is_error()) {
			// TODO - Unload the components that were added with `.add()` a couple lines above here.
			return CF_INVALID_ENTITY;
		}
	}

	if (err_out) *err_out = cf_error_success();
	return entity;
}

static cf_entity_collection_t* cf_s_collection(cf_entity_t entity)
{
	cf_entity_collection_t* collection = NULL;
	uint16_t entity_type = cf_s_entity_type(entity);
	if (entity_type == cf_app->current_collection_type_being_iterated) {
		// Fast path -- check the current entity collection for this entity type first.
		collection = cf_app->current_collection_being_updated;
		CUTE_ASSERT(collection);
	} else {
		// Slightly slower path -- lookup collection first.
		collection = cf_app->entity_collections.find(entity_type);
		if (!collection) return NULL;
	}
	return collection;
}

void cf_entity_delayed_destroy(cf_entity_t entity)
{
	cf_app->delayed_destroy_entities.add(entity);
}

void cf_entity_destroy(cf_entity_t entity)
{
	uint16_t entity_type = cf_s_entity_type(entity);
	cf_entity_collection_t* collection = cf_app->entity_collections.find(entity_type);
	CUTE_ASSERT(collection);

	if (collection->entity_handle_table.is_valid(entity.handle)) {
		int index = collection->entity_handle_table.get_index(entity.handle);

		// Call cleanup function on each component.
		for (int i = 0; i < collection->component_tables.count(); ++i) {
			cf_component_config_t config;
			cf_app->component_configs.find(collection->component_type_tuple[i], &config);
			if (config.cleanup_fn) {
				config.cleanup_fn(entity, collection->component_tables[i][index], config.cleanup_udata);
			}
		}

		// Update index in case user changed it (by destroying enties).
		index = collection->entity_handle_table.get_index(entity.handle);

		// Free the handle.
		collection->entity_handles.unordered_remove(index);
		collection->entity_handle_table.free_handle(entity.handle);

		// Free each component.
		for (int i = 0; i < collection->component_tables.count(); ++i) {
			collection->component_tables[i].unordered_remove(index);
		}

		// Update handle of the swapped entity.
		if (index < collection->entity_handles.size()) {
			uint64_t h = collection->entity_handles[index];
			collection->entity_handle_table.update_index(h, index);
		}
	}
}

bool cf_entity_is_valid(cf_entity_t entity)
{
	cf_entity_collection_t* collection = cf_s_collection(entity);
	if (collection) return collection->entity_handle_table.is_valid(entity.handle);
	else return false;
}

void* cf_entity_get_component(cf_entity_t entity, const char* component_type)
{
	cf_entity_collection_t* collection = cf_s_collection(entity);
	if (!collection) return NULL;

	cf_strpool_id type = INJECT(component_type);
	const cf_array<cf_strpool_id>& component_type_tuple = collection->component_type_tuple;
	for (int i = 0; i < component_type_tuple.count(); ++i)
	{
		if (component_type_tuple[i].val == type.val) {
			int index = collection->entity_handle_table.get_index(entity.handle);
			return collection->component_tables[i][index];
		}
	}

	return NULL;
}

bool cf_entity_has_component(cf_entity_t entity, const char* component_type)
{
	return cf_entity_get_component(entity, component_type) ? true : false;
}

//--------------------------------------------------------------------------------------------------

static void cf_s_0(float dt, void* fn_uncasted, void* udata)
{
	auto fn = (void (*)(float, void*))fn_uncasted;
	fn(dt, udata);
}

static void cf_s_1(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0)
{
	auto fn = (void (*)(float, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), count);
}

static void cf_s_2(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1)
{
	CUTE_ASSERT(c0.count() == c1.count());
	auto fn = (void (*)(float, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), count);
}

static void cf_s_3(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1, cf_typeless_array& c2)
{
	CUTE_ASSERT(c0.count() == c1.count() && c0.count() == c2.count());
	auto fn = (void (*)(float, void*, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), c2.data(), count);
}

static void cf_s_4(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1, cf_typeless_array& c2, cf_typeless_array& c3)
{
	CUTE_ASSERT(c0.count() == c1.count() && c0.count() == c2.count() && c0.count() == c3.count());
	auto fn = (void (*)(float, void*, void*, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), c2.data(), c3.data(), count);
}

static void cf_s_5(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1, cf_typeless_array& c2, cf_typeless_array& c3, cf_typeless_array& c4)
{
	CUTE_ASSERT(c0.count() == c1.count() && c0.count() == c2.count() && c0.count() == c3.count() && c0.count() == c4.count());
	auto fn = (void (*)(float, void*, void*, void*, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), c2.data(), c3.data(), c4.data(), count);
}

static void cf_s_6(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1, cf_typeless_array& c2, cf_typeless_array& c3, cf_typeless_array& c4, cf_typeless_array& c5)
{
	CUTE_ASSERT(c0.count() == c1.count() && c0.count() == c2.count() && c0.count() == c3.count() && c0.count() == c4.count() && c0.count() == c5.count());
	auto fn = (void (*)(float, void*, void*, void*, void*, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), c2.data(), c3.data(), c4.data(), c5.data(), count);
}

static void cf_s_7(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1, cf_typeless_array& c2, cf_typeless_array& c3, cf_typeless_array& c4, cf_typeless_array& c5, cf_typeless_array& c6)
{
	CUTE_ASSERT(c0.count() == c1.count() && c0.count() == c2.count() && c0.count() == c3.count() && c0.count() == c4.count() && c0.count() == c5.count() && c0.count() == c6.count());
	auto fn = (void (*)(float, void*, void*, void*, void*, void*, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), c2.data(), c3.data(), c4.data(), c5.data(), c6.data(), count);
}

static void cf_s_8(float dt, void* fn_uncasted, void* udata, cf_typeless_array& c0, cf_typeless_array& c1, cf_typeless_array& c2, cf_typeless_array& c3, cf_typeless_array& c4, cf_typeless_array& c5, cf_typeless_array& c6, cf_typeless_array& c7)
{
	CUTE_ASSERT(c0.count() == c1.count() && c0.count() == c2.count() && c0.count() == c3.count() && c0.count() == c4.count() && c0.count() == c5.count() && c0.count() == c6.count() && c0.count() == c7.count());
	auto fn = (void (*)(float, void*, void*, void*, void*, void*, void*, void*, void*, void*, int))fn_uncasted;
	int count = c0.count();
	fn(dt, udata, c0.data(), c1.data(), c2.data(), c3.data(), c4.data(), c5.data(), c6.data(), c7.data(), count);
}

static inline void cf_s_match(cf_array<int>* matches, const cf_array<cf_strpool_id>& a, const cf_array<cf_strpool_id>& b)
{
	for (int i = 0; i < a.count(); ++i)
	{
		for (int j = 0; j < b.count(); ++j)
		{
			if (a[i].val == b[j].val) {
				matches->add(j);
				break;
			}
		}
	}
}

void cf_ecs_run_systems(float dt)
{
	int system_count = cf_app->systems.count();
	for (int i = 0; i < system_count; ++i)
	{
		cf_system_internal_t* system = cf_app->systems + i;
		void* update_fn = system->update_fn;
		auto pre_update_fn = system->pre_update_fn;
		auto post_update_fn = system->post_update_fn;
		void* udata = system->udata;

		if (pre_update_fn) pre_update_fn(dt, udata);

		if (update_fn) {
			for (int j = 0; j < cf_app->entity_collections.count(); ++j)
			{
				cf_entity_collection_t* collection = cf_app->entity_collections.items() + j;
				CUTE_ASSERT(collection->component_tables.count() == collection->component_type_tuple.count());
				int component_count = collection->component_tables.count();
				cf_app->current_collection_type_being_iterated = cf_app->entity_collections.keys()[j];
				cf_app->current_collection_being_updated = collection;
				CUTE_DEFER(cf_app->current_collection_type_being_iterated = CF_INVALID_ENTITY_TYPE);
				CUTE_DEFER(cf_app->current_collection_being_updated = NULL);

				cf_array<int> matches;
				cf_s_match(&matches, system->component_type_tuple, collection->component_type_tuple);

				cf_array<cf_typeless_array>& tables = collection->component_tables;

				if (matches.count() == system->component_type_tuple.count()) {
					switch (matches.count())
					{
					case 0: cf_s_0(dt, update_fn, udata); break;
					case 1: cf_s_1(dt, update_fn, udata, tables[matches[0]]); break;
					case 2: cf_s_2(dt, update_fn, udata, tables[matches[0]], tables[matches[1]]); break;
					case 3: cf_s_3(dt, update_fn, udata, tables[matches[0]], tables[matches[1]], tables[matches[2]]); break;
					case 4: cf_s_4(dt, update_fn, udata, tables[matches[0]], tables[matches[1]], tables[matches[2]], tables[matches[3]]); break;
					case 5: cf_s_5(dt, update_fn, udata, tables[matches[0]], tables[matches[1]], tables[matches[2]], tables[matches[3]], tables[matches[4]]); break;
					case 6: cf_s_6(dt, update_fn, udata, tables[matches[0]], tables[matches[1]], tables[matches[2]], tables[matches[3]], tables[matches[4]], tables[matches[5]]); break;
					case 7: cf_s_7(dt, update_fn, udata, tables[matches[0]], tables[matches[1]], tables[matches[2]], tables[matches[3]], tables[matches[4]], tables[matches[5]], tables[matches[6]]); break;
					case 8: cf_s_8(dt, update_fn, udata, tables[matches[0]], tables[matches[1]], tables[matches[2]], tables[matches[3]], tables[matches[4]], tables[matches[5]], tables[matches[6]], tables[matches[7]]); break;
					default: CUTE_ASSERT(0);
					}
				}
			}
		}

		if (post_update_fn) post_update_fn(dt, udata);
	}

	for (int i = 0; i < cf_app->delayed_destroy_entities.count(); ++i) {
		cf_entity_t e = cf_app->delayed_destroy_entities[i];
		cf_entity_destroy(e);
	}
	cf_app->delayed_destroy_entities.clear();
}

//--------------------------------------------------------------------------------------------------

void cf_ecs_component_begin()
{
	cf_app->component_config_builder.clear();
}

void cf_ecs_component_end()
{
	cf_app->component_configs.insert(INJECT(cf_app->component_config_builder.name), cf_app->component_config_builder);
}

void cf_ecs_component_set_name(const char* name)
{
	cf_app->component_config_builder.name = name;
}

void cf_ecs_component_set_size(size_t size)
{
	cf_app->component_config_builder.size_of_component = size;
}

void cf_ecs_component_set_optional_serializer(cf_component_serialize_fn* serializer_fn, void* udata)
{
	cf_app->component_config_builder.serializer_fn = serializer_fn;
	cf_app->component_config_builder.serializer_udata = udata;
}

void cf_ecs_component_set_optional_cleanup(cf_component_cleanup_fn* cleanup_fn, void* udata)
{
	cf_app->component_config_builder.cleanup_fn = cleanup_fn;
	cf_app->component_config_builder.cleanup_udata = udata;
}

static cf_strpool_id cf_s_kv_string(cf_kv_t* kv, const char* key)
{
	cf_error_t err = cf_kv_key(kv, key);
	if (err.is_error()) {
		if (CUTE_STRCMP(key, "inherits_from")) {
			CUTE_DEBUG_PRINTF("Unable to find the `%s` key.\n", key);
		}
		return { 0 };
	}

	const char* string_raw;
	size_t string_sz;
	err = cf_kv_val_string(kv, &string_raw, &string_sz);
	if (err.is_error()) {
		CUTE_DEBUG_PRINTF("`%s` key found, but is not a string.\n", key);
		return { 0 };
	}

	return cf_strpool_inject(cf_app->strpool, string_raw, (int)string_sz);
}

static void cf_s_register_entity_type(const char* schema)
{
	// Parse the schema.
	cf_kv_t* kv = cf_kv_make();
	bool cleanup_kv = true;
	CUTE_DEFER(if (cleanup_kv) cf_kv_destroy(kv));

	cf_error_t err = cf_kv_parse(kv, schema, CUTE_STRLEN(schema));
	if (err.is_error()) {
		CUTE_DEBUG_PRINTF("Unable to parse the schema when registering entity type.");
		return;
	}

	cf_strpool_id entity_type_string = cf_s_kv_string(kv, "entity_type");
	if (!cf_strpool_isvalid(cf_app->strpool, entity_type_string)) return;
	
	cf_strpool_id inherits_from_string = cf_s_kv_string(kv, "inherits_from");
	cf_entity_type_t inherits_from = CF_INVALID_ENTITY_TYPE;
	if (cf_strpool_isvalid(cf_app->strpool, inherits_from_string)) {
		cf_app->entity_type_string_to_id.find(inherits_from_string, &inherits_from);
	}

	// Search for all component types present in the schema.
	int component_config_count = cf_app->component_configs.count();
	const cf_component_config_t* component_configs = cf_app->component_configs.items();
	cf_array<cf_strpool_id> component_type_tuple;
	for (int i = 0; i < component_config_count; ++i)
	{
		const cf_component_config_t* config = component_configs + i;

		err = cf_kv_key(kv, config->name);
		if (!err.is_error()) {
			component_type_tuple.add(INJECT(config->name));
		}
	}
	cf_kv_reset_read_state(kv);

	// Register component types.
	cf_entity_type_t entity_type = cf_app->entity_type_gen++;
	cf_app->entity_type_string_to_id.insert(entity_type_string, entity_type);
	cf_app->entity_type_id_to_string.add(entity_type_string);
	cf_entity_collection_t* collection = cf_app->entity_collections.insert(entity_type);
	for (int i = 0; i < component_type_tuple.count(); ++i)
	{
		collection->component_type_tuple.add(component_type_tuple[i]);
		cf_typeless_array& table = collection->component_tables.add();
		cf_component_config_t* config = cf_app->component_configs.find(component_type_tuple[i]);
		table.m_element_size = config->size_of_component;
	}

	// Store the parsed schema.
	cf_app->entity_parsed_schemas.insert(entity_type, kv);
	if (inherits_from != CF_INVALID_ENTITY_TYPE) {
		cf_app->entity_schema_inheritence.insert(entity_type, inherits_from);
	}

	cleanup_kv = false;
}

static void cf_s_register_entity_type(cf_array<const char*> component_type_tuple, const char* entity_type_string)
{
	// Search for all component types present in the schema.
	int component_config_count = cf_app->component_configs.count();
	const cf_component_config_t* component_configs = cf_app->component_configs.items();
	cf_array<cf_strpool_id> component_type_ids;
	for (int i = 0; i < component_config_count; ++i)
	{
		const cf_component_config_t* config = component_configs + i;

		bool found = false;
		for (int i = 0; i < component_type_tuple.count(); ++i) {
			if (!CUTE_STRCMP(component_type_tuple[i], config->name)) {
				found = true;
				break;
			}
		}

		if (found) {
			component_type_ids.add(INJECT(config->name));
		}
	}

	// Register component types.
	cf_strpool_id entity_type_string_id = INJECT(entity_type_string);
	cf_entity_type_t entity_type = cf_app->entity_type_gen++;
	cf_app->entity_type_string_to_id.insert(entity_type_string_id, entity_type);
	cf_app->entity_type_id_to_string.add(entity_type_string_id);
	cf_entity_collection_t* collection = cf_app->entity_collections.insert(entity_type);
	for (int i = 0; i < component_type_ids.count(); ++i)
	{
		collection->component_type_tuple.add(component_type_ids[i]);
		cf_typeless_array& table = collection->component_tables.add();
		cf_component_config_t* config = cf_app->component_configs.find(component_type_ids[i]);
		table.m_element_size = config->size_of_component;
	}
}


void cf_ecs_entity_begin()
{
	cf_app->entity_config_builder.clear();
}

void cf_ecs_entity_end()
{
	if (cf_app->entity_config_builder.schema.is_valid()) {
		cf_s_register_entity_type(cf_app->entity_config_builder.schema.c_str());
	} else {
		cf_s_register_entity_type(cf_app->entity_config_builder.component_types, cf_app->entity_config_builder.entity_type);
	}
}

void cf_ecs_entity_set_name(const char* entity_type)
{
	cf_app->entity_config_builder.entity_type = entity_type;
}

void cf_ecs_entity_add_component(const char* component_type)
{
	cf_app->entity_config_builder.component_types.add(component_type);
}

void cf_ecs_entity_set_optional_schema(const char* schema)
{
	cf_app->entity_config_builder.schema = schema;
}

const char* cf_entity_get_type_string(cf_entity_t entity)
{
	cf_entity_type_t entity_type = cf_s_entity_type(entity);
	return cf_strpool_cstr(cf_app->strpool, cf_app->entity_type_id_to_string[entity_type]);
}

bool cf_entity_is_type(cf_entity_t entity, const char* entity_type_name)
{
	if (!cf_entity_is_valid(entity)) return false;
	const char* type_string = cf_entity_get_type_string(entity);
	return !CUTE_STRCMP(type_string, entity_type_name);
}

cf_entity_type_t cf_s_entity_type(cf_kv_t* kv)
{
	cf_strpool_id entity_type_string = cf_s_kv_string(kv, "entity_type");
	if (!cf_strpool_isvalid(cf_app->strpool, entity_type_string)) return CF_INVALID_ENTITY_TYPE;
	cf_entity_type_t entity_type = CF_INVALID_ENTITY_TYPE;
	cf_app->entity_type_string_to_id.find(entity_type_string, &entity_type);
	return entity_type;
}

static cf_error_t cf_s_fill_load_id_table(cf_kv_t* kv)
{
	int entity_count;
	cf_error_t err = cf_kv_array_begin(kv, &entity_count, "entities");
	if (err.is_error()) {
		return cf_error_failure("Unable to find `entities` array in kv file.");
	}

	while (entity_count--)
	{
		cf_kv_object_begin(kv);

		cf_entity_type_t entity_type = cf_s_entity_type(kv);
		if (entity_type == CF_INVALID_ENTITY_TYPE) {
			return cf_error_failure("Unable to find entity type.");
		}

		cf_entity_collection_t* collection = cf_app->entity_collections.find(entity_type);
		CUTE_ASSERT(collection);

		int index = collection->entity_handles.count();
		cf_handle_t h = collection->entity_handle_table.alloc_handle(index, entity_type);
		collection->entity_handles.add(h);

		cf_entity_t entity;
		entity.handle = h;
		cf_app->load_id_table->add(entity);

		cf_kv_object_end(kv);
	}

	cf_kv_array_end(kv);

	return cf_error_success();
}

cf_error_t cf_ecs_load_entities(cf_kv_t* kv, cf_array<cf_entity_t>* entities_out)
{
	if (cf_kv_get_state(kv) != CF_KV_STATE_READ) {
		return cf_error_failure("`kv` must be in `KV_STATE_READ` mode.");
	}
	
	cf_array<cf_entity_t> load_id_table;
	cf_app->load_id_table = &load_id_table;
	CUTE_DEFER(cf_app->load_id_table = NULL);

	cf_error_t err = cf_s_fill_load_id_table(kv);
	if (err.is_error()) return err;

	int entity_count;
	err = cf_kv_array_begin(kv, &entity_count, "entities");
	if (err.is_error()) {
		return cf_error_failure("Unable to find `entities` array in kv file.");
	}

	int entity_index = 0;
	while (entity_count--)
	{
		cf_entity_t entity = load_id_table[entity_index++];
		cf_kv_object_begin(kv);

		cf_entity_type_t entity_type = cf_s_entity_type(kv);
		if (entity_type == CF_INVALID_ENTITY_TYPE) {
			return cf_error_failure("Unable to find entity type.");
		}

		cf_entity_collection_t* collection = cf_app->entity_collections.find(entity_type);
		CUTE_ASSERT(collection);

		const cf_array<cf_strpool_id>& component_type_tuple = collection->component_type_tuple;
		for (int i = 0; i < component_type_tuple.count(); ++i)
		{
			cf_strpool_id component_type = component_type_tuple[i];
			cf_component_config_t* config = cf_app->component_configs.find(component_type);

			if (!config) {
				return cf_error_failure("Unable to find component config.");
			}

			// First load values from the schema.
			void* component = collection->component_tables[i].add();
			err = cf_s_load_from_schema(entity_type, entity, config, component, config->serializer_udata);
			if (err.is_error()) {
				return cf_error_failure("Unable to parse component from schema.");
			}

			// Then load values from the instance.
			cf_error_t err = cf_kv_object_begin(kv, config->name);
			if (!err.is_error()) {
				err = config->serializer_fn(kv, true, entity, component, config->serializer_udata);
				cf_kv_object_end(kv);
				if (err.is_error()) {
					return cf_error_failure("Unable to parse component.");
				}
			}
		}

		cf_kv_object_end(kv);
	}

	cf_kv_array_end(kv);

	if (entities_out) {
		entities_out->steal_from(&load_id_table);
	}

	return cf_error_success();
}

cf_error_t cf_ecs_save_entities(const cf_array<cf_entity_t>& entities, cf_kv_t* kv)
{
	if (cf_kv_get_state(kv) != CF_KV_STATE_WRITE) {
		return cf_error_failure("`kv` must be in `KV_STATE_WRITE` mode.");
	}

	cf_dictionary<cf_entity_t, int> id_table;
	for (int i = 0; i < entities.count(); ++i)
		id_table.insert(entities[i], i);

	cf_app->save_id_table = &id_table;
	CUTE_DEFER(cf_app->save_id_table = NULL);

	int entity_count = entities.count();
	cf_error_t err = cf_kv_array_begin(kv, &entity_count, "entities");
	if (err.is_error()) return err;

	for (int i = 0; i < entities.count(); ++i)
	{
		cf_entity_t entity = entities[i];
		cf_entity_type_t entity_type = cf_s_entity_type(entity);
		cf_entity_collection_t* collection = cf_app->entity_collections.find(entity_type);
		if (!collection) {
			return cf_error_failure("Unable to find entity type.");
		}

		bool is_valid = collection->entity_handle_table.is_valid(entity.handle);
		if (!is_valid) {
			return cf_error_failure("Attempted to save an invalid entity.");
		}
		uint32_t index = collection->entity_handle_table.get_index(entity.handle);

		cf_kv_object_begin(kv);

		cf_kv_key(kv, "entity_type");
		const char* entity_type_string = cf_strpool_cstr(cf_app->strpool, cf_app->entity_type_id_to_string[entity_type]);
		size_t entity_type_string_len = CUTE_STRLEN(entity_type_string);
		cf_kv_val_string(kv, &entity_type_string, &entity_type_string_len);

		const cf_array<cf_strpool_id>& component_type_tuple = collection->component_type_tuple;
		const cf_array<cf_typeless_array>& component_tables = collection->component_tables;
		for (int j = 0; j < component_type_tuple.count(); ++j)
		{
			cf_strpool_id component_type = component_type_tuple[j];
			const cf_typeless_array& component_table = component_tables[j];
			cf_component_config_t* config = cf_app->component_configs.find(component_type);
			const void* component = component_table[index];

			cf_error_t err = cf_kv_object_begin(kv, config->name);
			if (!err.is_error()) {
				err = config->serializer_fn(kv, false, entity, (void*)component, config->serializer_udata);
				cf_kv_object_end(kv);
				if (err.is_error()) {
					return cf_error_failure("Unable to save component.");
				}
			}
		}

		cf_kv_object_end(kv);
	}

	cf_kv_array_end(kv);

	return cf_error_success();
}

cf_error_t cf_ecs_save_entities(const cf_array<cf_entity_t>& entities)
{
	cf_dictionary<cf_entity_t, int> id_table;
	for (int i = 0; i < entities.count(); ++i)
		id_table.insert(entities[i], i);

	cf_app->save_id_table = &id_table;
	CUTE_DEFER(cf_app->save_id_table = NULL);

	int entity_count = entities.count();
	for (int i = 0; i < entities.count(); ++i)
	{
		cf_entity_t entity = entities[i];
		cf_entity_type_t entity_type = cf_s_entity_type(entity);
		cf_entity_collection_t* collection = cf_app->entity_collections.find(entity_type);
		if (!collection) {
			return cf_error_failure("Unable to find entity type.");
		}

		bool is_valid = collection->entity_handle_table.is_valid(entity.handle);
		if (!is_valid) {
			return cf_error_failure("Attempted to save an invalid entity.");
		}
		uint32_t index = collection->entity_handle_table.get_index(entity.handle);

		const char* entity_type_string = cf_strpool_cstr(cf_app->strpool, cf_app->entity_type_id_to_string[entity_type]);

		const cf_array<cf_strpool_id>& component_type_tuple = collection->component_type_tuple;
		const cf_array<cf_typeless_array>& component_tables = collection->component_tables;
		for (int j = 0; j < component_type_tuple.count(); ++j)
		{
			cf_strpool_id component_type = component_type_tuple[j];
			const cf_typeless_array& component_table = component_tables[j];
			cf_component_config_t* config = cf_app->component_configs.find(component_type);
			const void* component = component_table[index];

			cf_error_t err = config->serializer_fn(NULL, false, entity, (void*)component, config->serializer_udata);
			if (err.is_error()) {
				return cf_error_failure("Unable to save component.");
			}
		}
	}

	return cf_error_success();
}

bool cf_ecs_is_entity_type_valid(const char* entity_type)
{
	if (cf_app->entity_type_string_to_id.find(INJECT(entity_type))) {
		return true;
	} else {
		return false;
	}
}

cf_array<const char*> cf_ecs_get_entity_list()
{
	cf_array<const char*> names;

	for (int i = 0; i < cf_app->entity_type_id_to_string.count(); ++i) {
		cf_strpool_id id = cf_app->entity_type_id_to_string[i];
		const char* name = cf_strpool_cstr(cf_app->strpool, id);
		names.add(name);
	}

	return names;
}

cf_array<const char*> cf_ecs_get_component_list()
{
	cf_array<const char*> names;
	int count = cf_app->component_configs.count();
	cf_strpool_id* ids = cf_app->component_configs.keys();

	for (int i = 0; i < count; ++i) {
		cf_strpool_id id = ids[i];
		const char* name = cf_strpool_cstr(cf_app->strpool, id);
		names.add(name);
	}

	return names;
}

cf_array<const char*> cf_ecs_get_system_list()
{
	cf_array<const char*> names;

	for (int i = 0; i < cf_app->systems.count(); ++i) {
		cf_strpool_id id = cf_app->systems[i].name;
		const char* name = id.val != 0 ? cf_strpool_cstr(cf_app->strpool, id) : "System name was not set.";
		names.add(name);
	}

	return names;
}

cf_array<const char*> cf_ecs_get_component_list_for_entity_type(const char* entity_type)
{
	cf_array<const char*> result;

	cf_entity_type_t type = CF_INVALID_ENTITY_TYPE;
	cf_app->entity_type_string_to_id.find(INJECT(entity_type), &type);
	if (type == CF_INVALID_ENTITY_TYPE) {
		return result;
	}

	cf_entity_collection_t* collection = cf_app->entity_collections.find(type);
	CUTE_ASSERT(collection);

	const cf_array<cf_strpool_id>& component_type_tuple = collection->component_type_tuple;
	for (int i = 0; i < component_type_tuple.count(); ++i)
	{
		cf_strpool_id component_type = component_type_tuple[i];
		cf_component_config_t* config = cf_app->component_configs.find(component_type);
		CUTE_ASSERT(config);
		result.add(config->name);
	}

	return result;
}
