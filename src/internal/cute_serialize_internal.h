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

#ifndef CUTE_SERIALIZE_INTERNAL_H
#define CUTE_SERIALIZE_INTERNAL_H

#include <cute_defines.h>

namespace cute
{

CUTE_INLINE void write_uint8(uint8_t** p, uint8_t value)
{
	**p = value;
	++(*p);
}

CUTE_INLINE void write_uint16(uint8_t** p, uint16_t value)
{
	(*p)[0] = value & 0xFF;
	(*p)[1] = value >> 8;
	*p += 2;
}

CUTE_INLINE void write_uint32(uint8_t** p, uint32_t value)
{
	(*p)[0] = value & 0xFF;
	(*p)[1] = (value >> 8 ) & 0xFF;
	(*p)[2] = (value >> 16) & 0xFF;
	(*p)[3] = value >> 24;
	*p += 4;
}

CUTE_INLINE void write_uint64(uint8_t** p, uint64_t value)
{
	(*p)[0] = value & 0xFF;
	(*p)[1] = (value >> 8 ) & 0xFF;
	(*p)[2] = (value >> 16) & 0xFF;
	(*p)[3] = (value >> 24) & 0xFF;
	(*p)[4] = (value >> 32) & 0xFF;
	(*p)[5] = (value >> 40) & 0xFF;
	(*p)[6] = (value >> 48) & 0xFF;
	(*p)[7] = value >> 56;
	*p += 8;
}

CUTE_INLINE void write_bytes(uint8_t** p, const uint8_t* byte_array, int num_bytes)
{
	for (int i = 0; i < num_bytes; ++i)
	{
		write_uint8(p, byte_array[i]);
	}
}

CUTE_INLINE uint8_t read_uint8(uint8_t** p)
{
	uint8_t value = **p;
	++(*p);
	return value;
}

CUTE_INLINE uint16_t read_uint16(uint8_t** p)
{
	uint16_t value;
	value = (*p)[0];
	value |= (((uint16_t)((*p)[1])) << 8);
	*p += 2;
	return value;
}

CUTE_INLINE uint32_t read_uint32(uint8_t** p)
{
	uint32_t value;
	value  = (*p)[0];
	value |= (((uint32_t)((*p)[1])) << 8);
	value |= (((uint32_t)((*p)[2])) << 16);
	value |= (((uint32_t)((*p)[3])) << 24);
	*p += 4;
	return value;
}

CUTE_INLINE uint64_t read_uint64(uint8_t** p)
{
	uint64_t value;
	value  = (*p)[0];
	value |= (((uint64_t)((*p)[1])) << 8 );
	value |= (((uint64_t)((*p)[2])) << 16);
	value |= (((uint64_t)((*p)[3])) << 24);
	value |= (((uint64_t)((*p)[4])) << 32);
	value |= (((uint64_t)((*p)[5])) << 40);
	value |= (((uint64_t)((*p)[6])) << 48);
	value |= (((uint64_t)((*p)[7])) << 56);
	*p += 8;
	return value;
}

CUTE_INLINE void read_bytes(uint8_t** p, uint8_t* byte_array, int num_bytes)
{
	for (int i = 0; i < num_bytes; ++i)
	{
		byte_array[i] = read_uint8(p);
	}
}

}

#endif // CUTE_SERIALIZE_INTERNAL_H
