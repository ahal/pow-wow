#include "native_events.h"

guint click(gint x, gint y, guint button) {
    return _click(x, y, button);
}

guint keypress(char val, modifiers mods) {
    return _keypress(val, &mods);
}
