#include "oneshot.h"
#include "notifications.h"
#include "etc.h"
#include "sharedstate.h"
#include "binding-util.h"
#include "binding-types.h"
#include "eventthread.h"
#include "debugwriter.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

Notification notifi;

RB_METHOD(modwindowGetWindowPosition)
{
	int x, y;
	SDL_GetWindowPosition(shState->rtData().window, &x, &y);
	return rb_ary_new3(2, LONG2FIX(x), LONG2FIX(y));
}

RB_METHOD(modwindowSetWindowPosition)
{
	int x, y;
	rb_get_args(argc, argv, "ii", &x, &y);
	SDL_SetWindowPosition(shState->rtData().window, x, y);
	return Qnil;
}

RB_METHOD(modwindowSetTitle)
{
	char* wintitle;
	rb_get_args(argc, argv, "z", &wintitle);
	SDL_SetWindowTitle(shState->rtData().window, wintitle);
	return Qnil;
}

RB_METHOD(modwindowSetIcon)
{
	char* path;
	rb_get_args(argc, argv, "z", &path);
	SDL_Surface* icon = IMG_Load(path);

	if (!icon)
	{
		rb_raise(rb_eRuntimeError, "Loading icon from path failed");
	}

	SDL_SetWindowIcon(shState->rtData().window, icon);
	return Qnil;
}

RB_METHOD(modwindowSetWindowOpacity)
{
	float opacity;
	rb_get_args(argc, argv, "f", &opacity);
	SDL_SetWindowOpacity(shState->rtData().window, opacity);
	return Qnil;
}

/*
RB_METHOD(modwindowSetTransparentColor)
{
	RB_UNUSED_PARAM;
	Value colorObj;

	rb_get_args(argc, argv, "o", &colorObj RB_ARG_END);

	Color *c = getPrivateDataCheck<Color>(colorObj, ColorType);

	#ifdef _WIN32
	SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
    SDL_GetWindowWMInfo(shState->rtData().window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Set transparency color
    SetLayeredWindowAttributes(hWnd, RGB(c.r, c.g, c.b), 0, LWA_COLORKEY);
	#else

	#endif
	return Qnil;
}
*/

RB_METHOD(modshotNotify)
{
	RB_UNUSED_PARAM;
	char* title;
	char* info;
	VALUE icon = Qnil;
	rb_get_args(argc, argv, "zz|o", &title, &info, &icon RB_ARG_END);

#ifdef _WIN32
	if (!notifi.hasTrayIcon)
		notifi.addTrayIcon("OneShot");
#elif defined __linux__
	if (!notifi.hasGApp)
		notifi.regApp("org.ModShot.Notifier");
#endif

	switch (TYPE(icon))
	{
		case T_NIL:
			notifi.send(title, info, 0, NULL);
			break;
		case T_FIXNUM:
			notifi.send(title, info, NUM2INT(icon), NULL);
			break;
		case T_STRING:
		{
			std::string iconStr = std::string(RSTRING_PTR(icon), RSTRING_LEN(icon));
			notifi.send(title, info, 0, iconStr.c_str());
			break;
		}
		default:
			notifi.send(title, info, 0, NULL);
			break;
	}

	return Qnil;
}

RB_METHOD(modshotNotifyCleanup)
{
	RB_UNUSED_PARAM;

#ifdef _WIN32
	if (notifi.hasTrayIcon)
		notifi.delTrayIcon();
#elif defined __linux__
	if (notifi.hasGApp)
		notifi.quitApp();
#endif

	return Qnil;
}

void modshotBindingInit()
{
	VALUE modshot_module = rb_define_module("ModShot");
	VALUE modwindow_module = rb_define_module("ModWindow");

	// ModShot:: module functions
	_rb_define_module_function(modshot_module, "notify", modshotNotify);
	_rb_define_module_function(modshot_module, "notify_cleanup", modshotNotifyCleanup);

	// ModWindow:: module functions
	_rb_define_module_function(modwindow_module, "GetWindowPosition", modwindowGetWindowPosition);
	_rb_define_module_function(modwindow_module, "SetWindowPosition", modwindowSetWindowPosition);
	_rb_define_module_function(modwindow_module, "SetTitle", modwindowSetTitle);
	_rb_define_module_function(modwindow_module, "SetIcon", modwindowSetIcon);
	_rb_define_module_function(modwindow_module, "setWindowOpacity", modwindowSetWindowOpacity);
	//_rb_define_module_function(modwindow_module, "setWindowChromaKey", modwindowSetTransparentColor);
}
