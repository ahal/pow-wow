#ifndef __LINUX_NATIVE_UTILS_H
#define __LINUX_NATIVE_UTILS_H

#include <gdk/gdk.h>

// Utility methods for linux events
GdkDevice* getSomeDevice();
GdkWindow* getActiveWindow();
guint32 getTimestamp();
#endif // header guard
