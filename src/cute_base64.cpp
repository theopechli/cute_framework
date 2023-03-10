/*
	Cute Framework
	Copyright (C) 2023 Randy Gaul https://randygaul.github.io/

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

#include <cute_base64.h>
#include <cute_c_runtime.h>

// Implementation referenced from: https://tools.ietf.org/html/rfc4648

// From: https://tools.ietf.org/html/rfc4648#section-3.2
static const uint8_t s_6bits_to_base64[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

/*
	Generated by:

		int out_array[80];
		for (int i = 0; i < 80; ++i) out_array[i] = -1;
		for (int i = 0; i < 64; ++i)
		{
			int val = s_6bits_to_base64[i];
			int index = val - 43;
			out_array[index] = i;
		}
		for (int i = 0; i < 80; ++i) printf("%d, ", out_array[i]);
*/
static const int s_base64_to_6bits[80] = {

	62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
};

CF_Result cf_base64_encode(void* dst, size_t dst_size, const void* src, size_t src_size)
{
	size_t out_size = CF_BASE64_ENCODED_SIZE(src_size);
	if (dst_size < out_size) return cf_result_error("`dst` buffer too small to place encoded output.");

	size_t triplets = (src_size) / 3;
	int pads = (src_size) % 3 ? 3 - (src_size) % 3 : 0;

	const uint8_t* in = (const uint8_t*)src;
	uint8_t* out = (uint8_t*)dst;

	while (triplets--)
	{
		uint32_t bits = ((uint32_t)in[0]) << 16 | ((uint32_t)in[1]) << 8 | ((uint32_t)in[2]);
		uint32_t a = (bits & 0xFC0000) >> 18;
		uint32_t b = (bits & 0x3F000) >> 12;
		uint32_t c = (bits & 0xFC0) >> 6;
		uint32_t d = (bits & 0x3F);
		in += 3;
		CF_ASSERT(a < 64);
		CF_ASSERT(b < 64);
		CF_ASSERT(c < 64);
		CF_ASSERT(d < 64);
		*out++ = s_6bits_to_base64[a];
		*out++ = s_6bits_to_base64[b];
		*out++ = s_6bits_to_base64[c];
		*out++ = s_6bits_to_base64[d];
	}

	switch (pads)
	{
	case 1:
	{
		uint32_t bits = ((uint32_t)in[0]) << 8 | ((uint32_t)in[1]);
		uint32_t a = (bits & 0xFC00) >> 10;
		uint32_t b = (bits & 0x3F0) >> 4;
		uint32_t c = (bits & 0xF) << 2;
		CF_ASSERT(a < 64);
		CF_ASSERT(b < 64);
		CF_ASSERT(c < 64);
		*out++ = s_6bits_to_base64[a];
		*out++ = s_6bits_to_base64[b];
		*out++ = s_6bits_to_base64[c];
		in += 2;
	}	break;

	case 2:
		uint32_t bits = ((uint32_t)in[0]);
		uint32_t a = (bits & 0xFC) >> 2;
		uint32_t b = (bits & 0x3) << 4;
		CF_ASSERT(a < 64);
		CF_ASSERT(b < 64);
		*out++ = s_6bits_to_base64[a];
		*out++ = s_6bits_to_base64[b];
		in += 1;
		break;
	}

	while (pads--)
	{
		*out++ = '=';
	}

	CF_ASSERT((int)(out - (uint8_t*)dst) == out_size);

	return cf_result_success();
}

CF_Result cf_base64_decode(void* dst, size_t dst_size, const void* src, size_t src_size)
{
	if (!src_size) return cf_result_success();
	if (src_size % 4) return cf_result_error("`src_size` is not a multiple of 4 (all base64 streams must be padded to a multiple of four with `=` characters).");
	size_t quadruplets = src_size / 4;
	
	const uint8_t* in = (const uint8_t*)src;
	uint8_t* out = (uint8_t*)dst;

	const uint8_t* end = in + src_size;
	int pads = 0;
	if (end[-1] == '=') pads++;
	if (end[-2] == '=') pads++;
	if (pads) quadruplets--;

	size_t exact_out_size = CF_BASE64_DECODED_SIZE(src_size);
	switch (pads)
	{
	case 1: dst_size -= 2; break;
	case 2: dst_size -= 1; break;
	}
	if (CF_BASE64_DECODED_SIZE(src_size) < exact_out_size) return cf_result_error("'dst_size' is too small to decode.");

	// RFC describes the best way to handle bad input is to reject the entire input.
	// https://tools.ietf.org/html/rfc4648#page-14

	while (quadruplets--)
	{
		uint32_t a = *in++ - 43;
		uint32_t b = *in++ - 43;
		uint32_t c = *in++ - 43;
		uint32_t d = *in++ - 43;
		if ((a > 79) | (b > 79) | (c > 79) | (d > 79)) return cf_result_error("Found illegal character in input stream.");
		a = s_base64_to_6bits[a];
		b = s_base64_to_6bits[b];
		c = s_base64_to_6bits[c];
		d = s_base64_to_6bits[d];
		if ((a == ~0) | (b == ~0) | (c == ~0) | (d == ~0)) return cf_result_error("Found illegal character in input stream.");
		uint32_t bits = (a << 26) | (b << 20) | (c << 14) | (d << 8);
		*out++ = (bits & 0xFF000000) >> 24;
		*out++ = (bits & 0x00FF0000) >> 16;
		*out++ = (bits & 0x0000FF00) >> 8;
	}

	switch (pads)
	{
	case 1:
	{
		uint32_t a = *in++ - 43;
		uint32_t b = *in++ - 43;
		uint32_t c = *in++ - 43;
		if ((a > 79) | (b > 79) | (c > 79)) return cf_result_error("Found illegal character in input stream.");
		a = s_base64_to_6bits[a];
		b = s_base64_to_6bits[b];
		c = s_base64_to_6bits[c];
		if ((a == ~0) | (b == ~0) | (c == ~0)) return cf_result_error("Found illegal character in input stream.");
		uint32_t bits = (a << 26) | (b << 20) | (c << 14);
		*out++ = (bits & 0xFF000000) >> 24;
		*out++ = (bits & 0x00FF0000) >> 16;
	}	break;

	case 2:
	{
		uint32_t a = *in++ - 43;
		uint32_t b = *in++ - 43;
		if ((a > 79) | (b > 79)) return cf_result_error("Found illegal character in input stream.");
		a = s_base64_to_6bits[a];
		b = s_base64_to_6bits[b];
		if ((a == ~0) | (b == ~0)) return cf_result_error("Found illegal character in input stream.");
		uint32_t bits = (a << 26) | (b << 20);
		*out++ = (bits & 0xFF000000) >> 24;
	}	break;
	}

	CF_ASSERT((int)(out + pads - (uint8_t*)dst) == CF_BASE64_DECODED_SIZE(src_size));

	return cf_result_success();
}
