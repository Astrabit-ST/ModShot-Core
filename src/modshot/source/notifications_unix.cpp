#include "notifications.h"
#include "debugwriter.h"

bool Notification::regApp(const char *appId)
{
	if (hasGApp)
	{
		Debug() << "Already registered Gio application";
		return true;
	}

	GError **gErr;
	gApp = g_application_new(appId, G_APPLICATION_FLAGS_NONE);
	g_application_register(gApp, nullptr, gErr);

	if (gErr)
	{
		Debug() << "Failed to register Gio application!";
		return false;
	}
	else
	{
		hasGApp = true;
		return true;
	}
}

bool Notification::quitApp()
{
	if (!hasGApp)
		return true;

	g_application_quit(gApp);
	hasGApp = false;

	return true;
}

bool Notification::send(const char *title, const char *body, const int iconId, const char *iconPath)
{
	if (!hasGApp)
		return false;

	// Create Gio notification object
	g_autoptr(GNotification) gioNotify = g_notification_new(title);
	g_notification_set_body(gioNotify, body);

	// Set notification icon
	if (iconId > 0 && iconId <= 4)
	{
		// Set icon from FreeDesktop defineded
		switch (iconId)
		{
			case 1:
				// An information icon
				g_notification_set_icon(gioNotify, g_themed_icon_new("dialog-information"));
				break;
			case 2:
				// A warning icon
				g_notification_set_icon(gioNotify, g_themed_icon_new("dialog-warning"));
				break;
			case 3:
				// An error icon
				g_notification_set_icon(gioNotify, g_themed_icon_new("dialog-error"));
				break;
		}
	}
	else if (iconPath)
	{
		// Set icon from local file (PNG, JPEG, GIF, TIFF, ICO, etc.)
		g_autoptr(GFile) gioFile = g_file_new_for_path(iconPath);
		g_autoptr(GIcon) gioIcon = g_file_icon_new(gioFile);
		g_notification_set_icon(gioNotify, gioIcon);
	}

	// Send notification to Gio application
	g_application_send_notification(gApp, "oneshot-notification", gioNotify);

	return true;
}
