#include "linux_events.h"
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>

using namespace std;

guint submit_event_list(list<GdkEvent*> events) {
    list<GdkEvent*>::iterator it; 
    for (it = events.begin(); it != events.end(); ++it) {
        gdk_event_put(*it);
        gdk_event_free(*it);
    }
    return true;
}

// Creates a key event
GdkEvent* createKeyEvent(GdkEventType type, guint keyval, guint state) {
    GdkEvent *event = gdk_event_new(type);
    event->key.window = getActiveWindow();
    event->key.send_event = false; // Not a synthesized event
    event->key.time = getTimestamp();
    event->key.state = state;

    GdkKeymapKey *keys;
    gint num_keys;
    if (keyval != 0 && gdk_keymap_get_entries_for_keyval(
                            gdk_keymap_get_default(), keyval, &keys, &num_keys)) {
        if (num_keys > 0) {
            event->key.hardware_keycode = keys[0].keycode;
            event->key.group = keys[0].group;
            g_free(keys);

            gdk_keymap_translate_keyboard_state(gdk_keymap_get_default(), keys[0].keycode,
                                                    (GdkModifierType)state, keys[0].group, &keyval, 0, 0, 0);
            printf("key: %s, type: %i, state: %i, hkc: %i, level: %i\n", gdk_keyval_name(keyval), type, state, event->key.hardware_keycode, keys[0].level);
        }
    }
    event->key.keyval = keyval;
    return event;
}

/**
 * Create and submit modifier key events
 *
 * type - The type of the event, e.g GDK_KEY_PRESS [IN]
 * modifiers - A modifier struct [IN]
 * state - The state of the modifier keys [IN/OUT]
 */ 
list<GdkEvent*> createModifierEvents(GdkEventType type, modifiers *mods, guint *state) {
    list<GdkEvent*> events;
    // Control key event
    if (mods->ctrl == 1) {
        events.push_back(createKeyEvent(type, gdk_keyval_from_name("Control_L"), *state));
        *state ^= GDK_CONTROL_MASK;  // ^ is the xor operator, this toggles the appropriate bit
    }
    // Shift key event
    if (mods->shift == 1) {
        events.push_back(createKeyEvent(type, gdk_keyval_from_name("Shift_L"), *state));
        *state ^= GDK_SHIFT_MASK;
    }
    // Alt key event
    if (mods->alt == 1) {
        events.push_back(createKeyEvent(type, gdk_keyval_from_name("Alt_L"), *state));
        *state ^= GDK_MOD1_MASK;
    }
    // Meta key event
    if (mods->meta == 1) {
        events.push_back(createKeyEvent(type, gdk_keyval_from_name("Meta_L"), *state));
        *state ^= GDK_META_MASK;
    }
    // Return the event list
    return events;
}

// Send a keypress event
extern "C" guint32 _keypress(guint32 c, modifiers *mods) {
    list<GdkEvent*> events;
    guint state = 0;
    list<GdkEvent*> ret_list = createModifierEvents(GDK_KEY_PRESS, mods, &state);
    events.splice(events.end(), ret_list);
    
    GdkEvent *press = createKeyEvent(GDK_KEY_PRESS, c, state);
    events.push_back(press);

    GdkEvent *release = gdk_event_copy(press);
    release->key.type = GDK_KEY_RELEASE;
    release->key.time = getTimestamp();
    events.push_back(release);

    ret_list = createModifierEvents(GDK_KEY_RELEASE, mods, &state);
    events.splice(events.end(), ret_list);

    submit_event_list(events);
    return getTimestamp();
}

// Send a string of key events
extern "C" guint32 _sendKeys(char *val, modifiers *mods) {
    guint state = 0;
    list<GdkEvent*> events; 
    list<GdkEvent*> ret_list = createModifierEvents(GDK_KEY_PRESS, mods, &state);
    events.splice(events.end(), ret_list);

    printf("str: %s\n", val);
    for (int i = 0; val[i] != '\0'; i++) {
        guint keyval = gdk_unicode_to_keyval(val[i]);
        GdkEvent *press = createKeyEvent(GDK_KEY_PRESS, keyval, state);
        events.push_back(press);

        GdkEvent *release = gdk_event_copy(press);
        release->key.type = GDK_KEY_RELEASE;
        release->key.time = getTimestamp();
        events.push_back(release);
    }

    ret_list = createModifierEvents(GDK_KEY_RELEASE, mods, &state);
    events.splice(events.end(), ret_list);

    submit_event_list(events);
    return getTimestamp();
}

// Send a click event
extern "C" guint32 _click(gint x, gint y, guint button) {
    list<GdkEvent*> events;

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

    events.push_back(press); 
   
    // Create the release event
    GdkEvent *release = gdk_event_copy(press);
    release->button.type = GDK_BUTTON_RELEASE;
    release->button.time = getTimestamp();

    events.push_back(release);
    submit_event_list(events);
    return getTimestamp();
}

