#include "native_events.h"

guint click(gint x, gint y, guint button) {
    return _click(x, y, button);
}

guint keypress(guint32 val, modifiers mods) {
    return _keypress(val, &mods);
}

guint sendKeys(char *val, modifiers mods) {
    return _sendKeys(val, &mods);
}
