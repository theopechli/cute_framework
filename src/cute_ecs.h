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

#ifndef CUTE_ECS_H
#define CUTE_ECS_H

#include <cute_error.h>
#include <cute_handle_table.h>
#include <cute_array.h>
#include <cute_typeless_array.h>
#include <cute_dictionary.h>

#include <internal/cute_object_table_internal.h>

namespace cute
{

//--------------------------------------------------------------------------------------------------
// Entity

using entity_type_t = uint32_t;
#define CUTE_INVALID_ENTITY_TYPE ((entity_type_t)(~0))

struct entity_t
{
	entity_type_t type;
	handle_t handle;
};

struct entity_config_t
{
	const char* name = NULL;
	entity_type_t type = CUTE_INVALID_ENTITY_TYPE;

	size_t schema_size = 0;
	const void* schema = NULL;
};

extern CUTE_API error_t CUTE_CALL app_register_entity_type(app_t* app, const entity_config_t* config);

//--------------------------------------------------------------------------------------------------
// Component

using component_type_t = uint32_t;
#define CUTE_INVALID_COMPONENT_TYPE ((component_type_t)(~0))

typedef void (component_initialize_fn)(void* component);
typedef error_t (component_serialize_fn)(struct kv_t* kv, void* component);

struct component_config_t
{
	size_t size = 0;
	const char* name = NULL;
	component_type_t type = CUTE_INVALID_COMPONENT_TYPE;

	component_initialize_fn* initializer_fn = NULL;
	component_serialize_fn* serializer_fn = NULL;

	int dependency_count = 0;
	component_type_t* dependencies = NULL;
};

extern CUTE_API error_t CUTE_CALL app_register_component_type(app_t* app, const component_config_t* component_config);

//--------------------------------------------------------------------------------------------------
// System

typedef void system_fn();
extern CUTE_API void CUTE_CALL app_register_system(app_t* app, system_fn* system_update_function, component_type_t* types, int types_count);

template <typename T>
void app_register_system(app_t* app, T system_update_function, component_type_t* types, int types_count)
{
	app_register_system(app, (system_fn*)system_update_function, types, types_count);
}

//--------------------------------------------------------------------------------------------------
// Run-time functions and entity lifetime management.

extern CUTE_API entity_t CUTE_CALL app_make_entity(app_t* app, entity_type_t type);
extern CUTE_API void CUTE_CALL app_destroy_entity(app_t* app, entity_t entity);
extern CUTE_API bool CUTE_CALL app_is_entity_valid(app_t* app, entity_t entity);
extern CUTE_API error_t CUTE_CALL app_load_entities(app_t* app, const void* memory, size_t size);

// WORKING HERE
// Serialize entities.
// Entities can refer to one another in serialized form.
// Inheritance of schemas.

extern CUTE_API void CUTE_CALL app_update_systems(app_t* app);

}

#endif // CUTE_ECS_H
