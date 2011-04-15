#include "linux_events.h"
#include <stdlib.h>

// Creates a key event
guint createKeyEvent(GdkEventType type, guint keyval, guint state) {
    guint timestamp = getTimestamp();
    GdkEvent *event = gdk_event_new(type);
    event->key.window = getActiveWindow();
    event->key.send_event = false; // Not a synthesized event
    event->key.time = timestamp;
    event->key.keyval = keyval;
    event->key.state = state;
    
    // Submit and free the event
    gdk_event_put(event);
    //gdk_event_free(event);
    return timestamp;
}

guint createModifierEvents(GdkEventType type, modifiers *mods) {
}

extern "C" guint _keypress(guint32 c, modifiers *mods) {
    createModifierEvents(GDK_KEY_PRESS, mods);
    
    guint state = getModifierState(mods);
    createKeyEvent(GDK_KEY_PRESS, c, state);
    createKeyEvent(GDK_KEY_RELEASE, c, state);

    createModifierEvents(GDK_KEY_RELEASE, mods);
    return true;
}


extern "C" guint _sendKeys(char *val, modifiers *mods) {
    createModifierEvents(GDK_KEY_PRESS, mods);

    printf("str: %s\n", val);
    guint state = getModifierState(mods);
    for (int i = 0; val[i] != '\0'; i++) {
        guint keyval = gdk_unicode_to_keyval(val[i]);
        createKeyEvent(GDK_KEY_PRESS, keyval, state);
        createKeyEvent(GDK_KEY_RELEASE, keyval, state);
    }

    createModifierEvents(GDK_KEY_RELEASE, mods);
    return true;
}

// Send a click event
extern "C" guint _click(gint x, gint y, guint button) {
    GdkWindow *window = getActiveWindow();
    GdkDevice *device = getSomeDevice();
    
    // Create the press event
    GdkEvent *press = gdk_event_new(GDK_BUTTON_PRESS);
    press->button.window = window;
    press->button.send_event = false; // Not a synthesized event
    press->button.time = getTimestamp();
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
    gdk_event_free(release);

    return true;
}

