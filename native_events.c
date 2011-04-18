#include "native_events.h"

libexport uint click(int x, int y, uint button) {
    return _click(x, y, button);
}

libexport uint keypress(uint32 val, modifiers *mods) {
    return _keypress(val, mods);
}

libexport uint sendKeys(char *val, modifiers *mods) {
    return _sendKeys(val, mods);
}
