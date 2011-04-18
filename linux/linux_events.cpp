#include "linux_events.h"
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>

// Creates a key event
guint createKeyEvent(GdkEventType type, guint keyval, guint state) {

    guint timestamp = getTimestamp();
    GdkEvent *event = gdk_event_new(type);
    event->key.window = getActiveWindow();
    event->key.send_event = false; // Not a synthesized event
    event->key.time = timestamp;
    event->key.state = state;

    GdkKeymapKey *keys;
    gint num_keys;
    if (keyval != 0 && gdk_keymap_get_entries_for_keyval(
                            gdk_keymap_get_default(), keyval, &keys, &num_keys)) {
        if (num_keys > 0) {
            event->key.hardware_keycode = keys[0].keycode;
            event->key.group = keys[0].group;
            g_free(keys);

            gdk_keymap_translate_keyboard_state(gdk_keymap_get_default(), keys[0].keycode, (GdkModifierType)state, keys[0].group, &keyval, 0, 0, 0);
            printf("key: %s, type: %i, state: %i, hkc: %i, level: %i\n", gdk_keyval_name(keyval), type, state, event->key.hardware_keycode, keys[0].level);
        }
    }
    event->key.keyval = keyval;
    
    // Submit and free the event
    gdk_event_put(event);
    //gdk_event_free(event);
    return timestamp;
}

// Create modifier key events
guint createModifierEvents(GdkEventType type, modifiers *mods, guint state) {
    // Control key event
    if (mods->ctrl == 1) {
        createKeyEvent(type, gdk_keyval_from_name("Control_L"), state);
        state ^= GDK_CONTROL_MASK;  // ^ is the xor operator, this toggles the appropriate bit
    }
    // Shift key event
    if (mods->shift == 1) {
        createKeyEvent(type, gdk_keyval_from_name("Shift_L"), state);
        state ^= GDK_SHIFT_MASK;
    }
    // Alt key event
    if (mods->alt == 1) {
        createKeyEvent(type, gdk_keyval_from_name("Alt_L"), state);
        state ^= GDK_MOD1_MASK;
    }
    // Return the resulting bit mask
    return state;
}

extern "C" guint _keypress(guint32 c, modifiers *mods) {
    guint state = createModifierEvents(GDK_KEY_PRESS, mods, 0);
    
    createKeyEvent(GDK_KEY_PRESS, c, state);
    createKeyEvent(GDK_KEY_RELEASE, c, state);

    createModifierEvents(GDK_KEY_RELEASE, mods, state);
    return true;
}


extern "C" guint _sendKeys(char *val, modifiers *mods) {
    guint state = createModifierEvents(GDK_KEY_PRESS, mods, 0);

    printf("str: %s\n", val);
    for (int i = 0; val[i] != '\0'; i++) {
        guint keyval = gdk_unicode_to_keyval(val[i]);
        createKeyEvent(GDK_KEY_PRESS, keyval, state);
        createKeyEvent(GDK_KEY_RELEASE, keyval, state);
    }

    createModifierEvents(GDK_KEY_RELEASE, mods, state);
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

