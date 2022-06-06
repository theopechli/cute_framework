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

#ifndef CUTE_UTF8
#define CUTE_UTF8

#include "cute_defines.h"

CUTE_API const char* CUTE_CALL cf_decode8(const char* text, int* cp);
CUTE_API char* CUTE_CALL cf_encode8(char *text, int cp);
CUTE_API int cf_codepoint8_size(int cp);

CUTE_API const wchar_t* CUTE_CALL cf_decode16(const wchar_t* text, int* cp);
CUTE_API wchar_t* CUTE_CALL cf_encode16(wchar_t* text, int cp);
CUTE_API int CUTE_CALL cf_codepoint16_size(int cp);

CUTE_API void CUTE_CALL cf_widen(const char* in, wchar_t* out);
CUTE_API void CUTE_CALL cf_widen(const char* in, int in_len, wchar_t* out);
CUTE_API void CUTE_CALL cf_widen(const char* in, wchar_t* out, int out_len);
CUTE_API void CUTE_CALL cf_widen(const char* in, int in_len, wchar_t* out, int out_len);
CUTE_API void CUTE_CALL cf_shorten(const wchar_t* in, char* out);
CUTE_API void CUTE_CALL cf_shorten(const wchar_t* in, int in_len, char* out);
CUTE_API void CUTE_CALL cf_shorten(const wchar_t* in, char* out, int out_len);
CUTE_API void CUTE_CALL cf_shorten(const wchar_t* in, int in_len, char* out, int out_len);

#ifdef  CUTE_CPP

namespace cute
{

}

#endif //  CUTE_CPP

#endif // CUTE_UTF8
