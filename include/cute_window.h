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

#ifndef CUTE_APP_WINDOW_H
#define CUTE_APP_WINDOW_H

#include "cute_defines.h"

CUTE_API void CUTE_CALL cf_window_size(int* w, int* h);
CUTE_API void CUTE_CALL cf_window_position(int* x, int* y);

CUTE_API bool CUTE_CALL cf_window_was_size_changed();
CUTE_API bool CUTE_CALL cf_window_was_moved();

CUTE_API bool CUTE_CALL cf_window_keyboard_lost_focus();
CUTE_API bool CUTE_CALL cf_window_keyboard_gained_focus();
CUTE_API bool CUTE_CALL cf_window_keyboard_has_focus();

CUTE_API bool CUTE_CALL cf_window_was_minimized();
CUTE_API bool CUTE_CALL cf_window_was_maximized();
CUTE_API bool CUTE_CALL cf_window_is_minimized();
CUTE_API bool CUTE_CALL cf_window_is_maximized();
CUTE_API bool CUTE_CALL cf_window_was_restored();

CUTE_API bool CUTE_CALL cf_window_mouse_entered();
CUTE_API bool CUTE_CALL cf_window_mouse_exited();
CUTE_API bool CUTE_CALL cf_window_mouse_inside();

enum cf_window_message_box_type_t
{
	CF_WINDOW_MESSAGE_BOX_TYPE_ERROR,
	CF_WINDOW_MESSAGE_BOX_TYPE_WARNING,
	CF_WINDOW_MESSAGE_BOX_TYPE_INFORMATION,
};

CUTE_API void CUTE_CALL cf_window_message_box(cf_window_message_box_type_t type, const char* title, const char* text);

#ifdef  CUTE_CPP

namespace cute
{

}

#endif //  CUTE_CPP

#endif // CUTE_APP_WINDOW_H
