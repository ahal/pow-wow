#ifndef __SEND_EVENT_H
#define __SEND_EVENT_H

#include <gdk/gdk.h>
#include "linux/linux_utils.h"

#ifdef __cplusplus
#define ext extern "C"
// Define C++ 'private' methods here
guint createKeyEvent(GdkEventType type, char c, guint state);
guint createModifierEvents(GdkEventType type, modifiers *mods);
#else
#define ext
// Define C shim methods here (this is the API exposed to the user)
guint click(gint x, gint y, guint button);
guint sendKeys(char *val, modifiers mods);
guint keypress(guint32 val, modifiers mods);
#endif

// Define C++ method implementations here
ext guint _click(gint x, gint y, guint button);
ext guint _sendKeys(char *val, modifiers *mods);
ext guint _keypress(guint32 val, modifiers *mods);

#endif
