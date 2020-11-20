/*
	Cute Framework
	Copyright (C) 2021 Randy Gaul https://randygaul.net

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

#include <cute_utf8.h>

namespace cute
{

const char* decode8(const char* text, int* cp)
{
	return NULL;
}

char* encode8(char *text, int cp)
{
	return NULL;
}

int codepoint8_size(int cp)
{
	return 0;
}

const wchar_t* decode16(const wchar_t* text, int* cp)
{
	return NULL;
}

wchar_t* encode16(wchar_t* text, int cp)
{
	return NULL;
}

int codepoint16_size(int cp)
{
	return 0;
}

void widen(const char* in, wchar_t* out)
{
}

void widen(const char* in, int in_len, wchar_t* out)
{
}

void widen(const char* in, wchar_t* out, int out_len)
{
}

void widen(const char* in, int in_len, wchar_t* out, int out_len)
{
}

void shorten(const wchar_t* in, char* out)
{
}

void shorten(const wchar_t* in, int in_len, char* out)
{
}

void shorten(const wchar_t* in, char* out, int out_len)
{
}

void shorten(const wchar_t* in, int in_len, char* out, int out_len)
{
}

}
