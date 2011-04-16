#include "linux_utils.h"

// Return the first device we find
GdkDevice* getSomeDevice() {
    GList *pList = gdk_devices_list();
    GList *currNode = pList;
    GdkDevice *currDevice = NULL;
    while (currNode != NULL && currDevice == NULL) {
        currDevice = (GdkDevice*) currNode->data;
        currNode = currNode->next;
    }

    return (GdkDevice*) g_object_ref(currDevice);
}

// Return the window that will receive events
GdkWindow* getActiveWindow() {
    GdkScreen *screen = gdk_screen_get_default();               // Get default screen
    GdkWindow *top = gdk_screen_get_active_window(screen);      // Get active gdk window (assume it is Firefox)
    
    // Firefox creates a child window, get it
    GList *list = gdk_window_get_children(top);
    GdkWindow *window = (GdkWindow*)list->data;
    g_list_free(list);
    // Another child is created inside the first child, also get it
    list = gdk_window_get_children(window);
    window = (GdkWindow*)list->data;
    g_list_free(list);

    g_object_unref(top);
    return window;
}

// This is the timestamp needed in the GDK events.
guint32 getTimestamp() {
    struct timespec clk_tm;
    const int msec_nsec_factor = 1000000;
    const int sec_msec_factor = 1000;

    int clk_ret = clock_gettime(CLOCK_MONOTONIC, &clk_tm);
    if (clk_ret == 0) {
        return (clk_tm.tv_sec * sec_msec_factor +(clk_tm.tv_nsec / msec_nsec_factor));
    }
    return 0;
}
