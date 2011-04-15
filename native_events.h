#ifndef __SEND_EVENT_H
#define __SEND_EVENT_H

#ifdef __cplusplus
#define ext extern "C"
#else
#define ext
#endif

#ifdef __linux
#include <gdk/gdk.h>
#include "linux/linux_utils.h"

#ifdef __cplusplus
// Define C++ 'private' methods here
guint createKeyEvent(GdkEventType type, char c, guint state);
guint createModifierEvents(GdkEventType type, modifiers *mods);
#else
// Define C shim methods here (this is the API exposed to the user)
guint click(gint x, gint y, guint button);
guint sendKeys(char *val, modifiers mods);
guint keypress(guint32 val, modifiers mods);
#endif

// Define C++ method implementations here
ext guint _click(gint x, gint y, guint button);
ext guint _sendKeys(char *val, modifiers *mods);
ext guint _keypress(guint32 val, modifiers *mods);
#endif // linux

#ifdef __WIN32
ext unsigned int _click(int x, int y, char flags[32], int button);
#endif // windows

#endif // header guard
