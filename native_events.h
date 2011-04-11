#ifndef __SEND_EVENT_H
#define __SEND_EVENT_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#ifndef __cplusplus
// Define C shim methods here
guint sendClick(gint x, gint y, guint button);

#else
// Define C++ 'private' methods here
GdkDevice* getSomeDevice();
guint32 TimeSinceBootMsec();

extern "C"
#endif

// Define C++ method implementations here
guint click(gint x, gint y, guint button);

#endif
