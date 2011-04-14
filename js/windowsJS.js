Components.utils.import("resource://gre/modules/ctypes.jsm");

dump("Attempting Library load\n");

var lib = ctypes.open("C:\\Users\\ctalbert\\projects\\pow-wow\\native_events.dll");

dump("Calling click\n");
lib.click(0, 0, '00000', 0);