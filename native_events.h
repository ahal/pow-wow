#ifndef __SEND_EVENT_H
#define __SEND_EVENT_H

#ifdef __linux
#include <gdk/gdk.h>
#include "linux/linux_utils.h"

#ifndef __cplusplus
// Define C shim methods here
guint click(gint x, gint y, guint button);
guint keypress(char val, modifiers mods);

#else
// Define C++ 'private' methods here
GdkEvent *createKeyEvent(GdkEventType type);
#endif

// Define C++ method implementations here
#ifdef __cplusplus
extern "C"
#endif
guint _click(gint x, gint y, guint button);
#ifdef __cplusplus
extern "C"
#endif
guint _keypress(char val, modifiers *mods);
#endif

#ifdef __WIN32
#ifdef __cplusplus
extern "C"
#endif
unsigned int _click(int x, int y, char flags[32], int button);
#endif // windows

#endif // header guard
