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

#ifndef CUTE_ARRAY_H
#define CUTE_ARRAY_H

#include <cute_defines.h>
#include <cute_c_runtime.h>
#include <cute_alloc.h>

/*
	Implements a basic growable array data structure for POD items. Items can
	use constructors and destructors, but must have trivial "memcpy" assignment
	operators (such as the default compiler-generated assignment operator).

	cute::array does *not* work as a drop-in replacement for std::vector as it
	has a few special properties. Here is the list of important points for using
	this array data structure.

	1. Items stored in the array is assumed to be POD. Sometimes the assignment
	   operator is used, and sometimes `CUTE_MEMCPY` or `CUTE_MEMMOVE` is used.
	   Items in the array should *not* have specialized assignment operators
	   beyond simply copying byte-for-byte POD data.
	2. There is no way to perform a proper "deep-copy" by using the assignment
	   operator on cute::array. Instead, assignment steals the pointer from one
	   array to another (like an rvalue reference) with the `steal_from` function.
	3. Items stored in the array do have constructors and destructors called, but
	   only upon insertion or removal (not during grow or other operations). The
	   idea is to facilitate easy initializing of values stored in the array, such
	   as working with an array of arrays.
	4. No iterators.
	5. No rvalue semantics are supported. Instead, the `steal_from` function can
	   be used to cleanup any current items, and then steal items from another
	   cute::array. `steal_from` is called within the assignment operator.
*/

namespace cute
{

template <typename T>
struct array
{
	array();
	explicit array(void* user_allocator_context);
	explicit array(int capacity, void* user_allocator_context);
	~array();

	T& add();
	T& add(const T& item);
	T& insert(int index);
	T& insert(int index, const T& item);
	void set(int index, const T& item);
	void remove(int index);
	T& pop();
	void unordered_remove(int index);
	void clear();
	void ensure_capacity(int num_elements);
	void steal_from(array<T>* steal_from_me);

	int capacity() const;
	int count() const;

	T& operator[](int index);
	const T& operator[](int index) const;

	T* operator+(int index);
	const T* operator+(int index) const;

	array<T>& operator=(array<T>& rhs);

	T& last();
	const T& last() const;

	T* data();
	const T* data() const;

private:
	int m_capacity = 0;
	int m_count = 0;
	T* m_items = NULL;
	void* m_mem_ctx = NULL;
};

// -------------------------------------------------------------------------------------------------

template <typename T>
array<T>::array()
{
}

template <typename T>
array<T>::array(void* user_allocator_context)
	: m_mem_ctx(user_allocator_context)
{
}

template <typename T>
array<T>::array(int capacity, void* user_allocator_context)
	: m_capacity(capacity)
	, m_mem_ctx(user_allocator_context)
{
	m_items = (T*)CUTE_ALLOC(sizeof(T), m_mem_ctx);
	CUTE_ASSERT(m_items);
}

template <typename T>
array<T>::~array()
{
	for (int i = 0; i < m_count; ++i)
	{
		T* slot = m_items + i;
		slot->~T();
	}
	CUTE_FREE(m_items, m_mem_ctx);
}

template <typename T>
T& array<T>::add()
{
	ensure_capacity(m_count + 1);
	T* slot = m_items + m_count++;
	CUTE_PLACEMENT_NEW(slot) T;
	return *slot;
}

template <typename T>
T& array<T>::add(const T& item)
{
	ensure_capacity(m_count + 1);
	T* slot = m_items + m_count++;
	CUTE_PLACEMENT_NEW(slot) T(item);
	return *slot;
}

template <typename T>
T& array<T>::insert(int index)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	add();
	int count_to_move = m_count - 1 - index;
	CUTE_MEMMOVE(m_items + index + 1, m_items + index, sizeof(T) * count_to_move);
	return m_items[index];
}

template <typename T>
T& array<T>::insert(int index, const T& item)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	add();
	int count_to_move = m_count - 1 - index;
	CUTE_MEMMOVE(m_items + index + 1, m_items + index, sizeof(T) * count_to_move);
	T* slot = m_items + index;
	CUTE_PLACEMENT_NEW(slot) T(item);
	return *slot;
}

template <typename T>
void array<T>::set(int index, const T& item)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	T* slot = m_items + index;
	*slot = item;
}

template <typename T>
void array<T>::remove(int index)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	T* slot = m_items + index;
	slot->~T();
	int count_to_move = m_count - 1 - index;
	CUTE_MEMMOVE(items + index, items + index + 1, sizeof(T) * count_to_move);
	--m_count;
}

template <typename T>
T& array<T>::pop()
{
	CUTE_ASSERT(m_count > 0);
	return m_items[--m_count];
}

template <typename T>
void array<T>::unordered_remove(int index)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	T* slot = m_items + index;
	slot->~T();
	m_items[index] = m_items[--m_count];
}

template <typename T>
void array<T>::clear()
{
	for (int i = 0; i < m_count; ++i)
	{
		T* slot = m_items + i;
		slot->~T();
	}
	m_count = 0;
}

template <typename T>
void array<T>::ensure_capacity(int num_elements)
{
	if (num_elements > m_capacity) {
		int new_capacity = m_capacity ? m_capacity * 2 : 256;
		while (new_capacity < num_elements)
		{
			new_capacity <<= 1;
			CUTE_ASSERT(new_capacity); // Detect overflow.
		}

		size_t new_size = sizeof(T) * new_capacity;
		T* new_items = (T*)CUTE_ALLOC(new_size, m_mem_ctx);
		CUTE_ASSERT(new_items);
		CUTE_MEMCPY(new_items, m_items, sizeof(T) * m_count);
		CUTE_FREE(m_items, m_mem_ctx);
		m_items = new_items;
		m_capacity = new_capacity;
	}
}

template <typename T>
void array<T>::steal_from(array<T>* steal_from_me)
{
	this->~array<T>();
	m_capacity = steal_from_me->m_capacity;
	m_count = steal_from_me->m_count;
	m_items = steal_from_me->m_items;
	m_mem_ctx = steal_from_me->m_mem_ctx;
	CUTE_PLACEMENT_NEW(steal_from_me) array<T>();
}

template <typename T>
int array<T>::capacity() const
{
	return m_capacity;
}

template <typename T>
int array<T>::count() const
{
	return m_count;
}

template <typename T>
T& array<T>::operator[](int index)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	return m_items[index];
}

template <typename T>
const T& array<T>::operator[](int index) const
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	return m_items[index];
}

template <typename T>
T* array<T>::data()
{
	return m_items;
}

template <typename T>
const T* array<T>::data() const
{
	return m_items;
}

template <typename T>
T* array<T>::operator+(int index)
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	return m_items + index;
}

template <typename T>
const T* array<T>::operator+(int index) const
{
	CUTE_ASSERT(index >= 0 && index < m_count);
	return m_items + index;
}

template <typename T>
array<T>& array<T>::operator=(array<T>& rhs)
{
	steal_from(rhs);
	return *this;
}

template <typename T>
T& array<T>::last()
{
	return (*this)[m_count - 1];
}

template <typename T>
const T& array<T>::last() const
{
	return (*this)[m_count - 1];
}

}

#endif // CUTE_ARRAY_H
