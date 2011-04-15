#ifndef __LINUX_NATIVE_UTILS_H
#define __LINUX_NATIVE_UTILS_H

#include <gdk/gdk.h>

typedef struct {
    unsigned int shift;
    unsigned int ctrl;
    unsigned int meta;
    unsigned int alt;
    unsigned int access;
} modifiers;

// Utility methods for linux events
GdkDevice* getSomeDevice();
GdkWindow* getActiveWindow();
guint32 getTimestamp();
guint getModifierState(modifiers *mods);
#endif
