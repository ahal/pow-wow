#ifndef __SEND_EVENT_H
#define __SEND_EVENT_H

#include "common/common_utils.h"

#ifdef __linux
#include <gdk/gdk.h>
#include "linux/linux_events.h"
#include "linux/linux_utils.h"
#define libexport
// Type definitions
#define uint guint
#define uint32 guint32
#define int gint
#endif // linux

#ifdef __WIN32
#include "windows/windows_events.h"
#define libexport __declspec( dllexport )
// Type definitions
#define uint unsigned int
#define uint32 unsigned int // TODO Make this whatever the windows equivalent is
#endif // windows

// Define C shim methods here (this is the API exposed to the user)
uint click(int x, int y, uint button);
uint sendKeys(char *val, modifiers mods);
uint keypress(uint32 val, modifiers mods);

#endif // header guard
