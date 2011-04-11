CC := cc
CXX := c++
INCLUDE := /usr/include/atk-1.0
CFLAGS := -fPIC -m32 -I$(INCLUDE)
CXXFLAGS := -fPIC -m32 -I$(INCLUDE)
LFLAGS := -shared -m32
OBJECTS := native_events.o send_event.o
TARGET := libnative_events.so

$(TARGET): $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@
	#cp $(TARGET) ../content/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cxx
	$(CXX) $(CFLAGS) -I -c $< -o $@

.PHONY: clean

clean:
	echo Cleaning up temporary files
	rm -f $(TARGET) $(OBJECTS) *.o
