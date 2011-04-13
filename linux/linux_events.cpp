#include "../native_events.h"
#include <stdlib.h>

// Creates a generic key event
GdkEvent *createKeyEvent(GdkEventType type) {
    GdkWindow *window = getActiveWindow();
    GdkEvent *event = gdk_event_new(type);
    event->key.window = window;
    event->key.send_event = false; // Not a synthesized event
    return event;
}

extern "C" guint _keypress(char c, modifiers *mods) {
    printf("shift: %d\n", mods->shift);
    guint keyval = gdk_unicode_to_keyval(c);
    printf("keyval: %c\n", keyval);
    GdkEvent *keydown = createKeyEvent(GDK_KEY_PRESS);
    keydown->key.time = TimeSinceBootMsec();
    keydown->key.keyval = keyval;
    keydown->key.state = getModifierState(mods);

    gdk_event_put(keydown);

    GdkEvent *keyup = gdk_event_copy(keydown);
    keyup->key.type = GDK_KEY_RELEASE;
    keyup->key.time++;

    gdk_event_free(keyup);
    return true;
}

extern "C" guint _sendKeys() {

}

// Send a click event
extern "C" guint _click(gint x, gint y, guint button) {
    GdkWindow *window = getActiveWindow();
    //printf("window: %p\n", window);
    //printf("window type: %d\n", gdk_window_get_window_type(window));
    
    GdkDevice *device = getSomeDevice();
    
    // Create the press event
    GdkEvent *press = gdk_event_new(GDK_BUTTON_PRESS);
    press->button.window = window;
    press->button.send_event = false; // Not a synthesized event
    press->button.time = TimeSinceBootMsec();
    press->button.x = x ;
    press->button.y = y ;
    press->button.button = button;
    press->button.device = device;

    printf("x: %f\n", press->button.x);
    printf("y: %f\n", press->button.y);
    
    // Submit the press event
    gdk_event_put(press);
   
    // Create the release event
    GdkEvent *release = gdk_event_copy(press);
    release->button.type = GDK_BUTTON_RELEASE;
    release->button.time++;

    // Submit the release event
    gdk_event_put(release);
    
    // Cleanup
    g_object_unref(device);
    // Only free this event because it was copied from the first one
    // (Bad things happen if you free both)
    gdk_event_free(release);

    return true;
}

