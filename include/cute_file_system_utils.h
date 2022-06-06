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

#ifndef CUTE_FILE_SYSTEM_UTILS_H
#define CUTE_FILE_SYSTEM_UTILS_H

#include "cute_defines.h"

CUTE_API const char* CUTE_CALL cf_file_system_get_backend_specific_error_message();
CUTE_API const char* CUTE_CALL cf_file_system_get_user_directory(const char* org, const char* app);
CUTE_API const char* CUTE_CALL cf_file_system_get_actual_path(const char* virtual_path);
CUTE_API void CUTE_CALL cf_file_system_enable_symlinks();

#ifdef CUTE_CPP

namespace cute
{

}

#endif // CUTE_CPP

#endif // CUTE_FILE_SYSTEM_UTILS_H
