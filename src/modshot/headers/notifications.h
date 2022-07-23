#pragma once

#ifdef __linux__
	#include <gio/gio.h>
#endif

class Notification {
public:
#ifdef _WIN32
	bool hasTrayIcon = false;

	bool addTrayIcon(const char *tip);
	bool delTrayIcon();
#elif defined __linux__
	GApplication *gApp;
	bool hasGApp = false;

	bool appIsRegistered();
	bool regApp(const char *appId);
	bool quitApp();
#endif

	bool send(const char *title, const char *body, const int iconId, const char *iconPath);
};
