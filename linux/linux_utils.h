#ifndef __LINUX_NATIVE_UTILS_H
#define __LINUX_NATIVE_UTILS_H

#include <gdk/gdk.h>
#include "../common/common_utils.h"

// Utility methods for linux events
GdkDevice* getSomeDevice();
GdkWindow* getActiveWindow();
guint32 getTimestamp();
guint getModifierState(modifiers *mods);
#endif // header guard
