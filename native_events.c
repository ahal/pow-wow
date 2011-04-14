#include "native_events.h"
// We need to talk about this interface.  This isn't going to work
#ifdef __linux
guint click(gint x, gint y, guint button) {
    return _click(x, y, button);
}

guint keypress(char val, modifiers mods) {
    return _keypress(val, &mods);
}
#endif

#ifdef __WIN32
#define DllExport __declspec( dllexport )
DllExport unsigned int click(int x, int y, char flags[32], int button) {
    return _click(x, y, flags, button);
}
#endif
