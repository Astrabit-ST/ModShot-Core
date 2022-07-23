#include "notifications.h"
#include "debugwriter.h"
#include "eventthread.h"
#include "sharedstate.h"
#include <windows.h>
#include <gdiplus.h>
#include <SDL2/SDL_syswm.h>
#include "resource.h"

static WCHAR *w32_toWide(const char *str)
{
	if (str)
	{
		int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);

		if (size > 0)
		{
			WCHAR *ustr = new WCHAR[size];

			if (MultiByteToWideChar(CP_UTF8, 0, str, -1, ustr, size) == size)
				return ustr;

			delete [] ustr;
		}
	}

	// Return empty string
	WCHAR *ustr = new WCHAR[1];
	*ustr = 0;

	return ustr;
}

bool Notification::addTrayIcon(const char* tip)
{
	if (hasTrayIcon)
		return false;

	// Convert to wide char string
	const wchar_t* wTip = w32_toWide(tip);

	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(shState->rtData().window, &wmInfo);
	HWND hWnd = wmInfo.info.win.window;

	// Get Win32 handle
	HINSTANCE hInst = GetModuleHandle(NULL);

	// Prepare Notify Icon Data
	NOTIFYICONDATAW nid;
	ZeroMemory(&nid, sizeof(NOTIFYICONDATAW));
	nid.cbSize = sizeof(NOTIFYICONDATAW);
	nid.hWnd = hWnd;
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.uCallbackMessage = WM_APP + 1; // 32769
	nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)); // main app icon
	wcscpy_s(nid.szTip, sizeof(nid.szTip), wTip);

	// Add notify icon on tray
	bool result = Shell_NotifyIconW(NIM_ADD, &nid);

	if (result)
		hasTrayIcon = true;

	return result;
}

bool Notification::delTrayIcon()
{
	if (!hasTrayIcon)
		return true;

	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(shState->rtData().window, &wmInfo);
	HWND hWnd = wmInfo.info.win.window;

	// Prepare Notify Icon Data
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uFlags = 0x0;

	// Delete notify icon from tray
	bool result = Shell_NotifyIcon(NIM_DELETE, &nid);

	if (result)
		hasTrayIcon = false;

	return true;
}

bool Notification::send(const char *title, const char *body, const int iconId, const char *iconPath)
{
	// Convert to wide char strings
	const wchar_t* wTitle = w32_toWide(title);
	const wchar_t* wBody = w32_toWide(body);

	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(shState->rtData().window, &wmInfo);
	HWND hWnd = wmInfo.info.win.window;

	// Prepare Notify Icon Data
	NOTIFYICONDATAW nid;
	ZeroMemory(&nid, sizeof(NOTIFYICONDATAW));
	nid.cbSize = sizeof(NOTIFYICONDATAW);
	nid.hWnd = hWnd;
	nid.uID = 0;
	nid.uFlags = NIF_INFO;
	wcscpy_s(nid.szInfo, sizeof(nid.szInfo), wBody);
	wcscpy_s(nid.szInfoTitle, sizeof(nid.szInfoTitle), wTitle);

	if (iconId > 0 && iconId <= 4)
	{
		switch (iconId)
		{
			case 1:
				// An information icon
				nid.dwInfoFlags = NIIF_INFO;
				break;
			case 2:
				// A warning icon
				nid.dwInfoFlags = NIIF_WARNING;
				break;
			case 3:
				// An error icon
				nid.dwInfoFlags = NIIF_ERROR;
				break;
			case 4:
				// An icon from executable
				nid.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
				break;
			default:
				// No icon
				nid.dwInfoFlags = NIIF_NONE;
				break;
		}
	}
	else if (iconPath)
	{
		const wchar_t* wIconPath = w32_toWide(iconPath);

		// Startup GDI+
		Gdiplus::GdiplusStartupInput gdiStartupInput;
		ULONG_PTR gdiToken;
		Gdiplus::GdiplusStartup(&gdiToken, &gdiStartupInput, NULL);

		// Load image and get icon handle
		Gdiplus::Bitmap* gdiBitmap = Gdiplus::Bitmap::FromFile(wIconPath, false);
		HICON hIcon;
		gdiBitmap->GetHICON(&hIcon);

		// Shutdown GDI+
		Gdiplus::GdiplusShutdown(gdiToken);

		nid.hBalloonIcon = hIcon;
		nid.dwInfoFlags = NIIF_USER | NIIF_LARGE_ICON;
	}

	// Modify notify icon data to show balloon
	bool result = Shell_NotifyIconW(NIM_MODIFY, &nid);

	return result;
}
