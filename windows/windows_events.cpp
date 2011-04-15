#include <stdlib.h>
#include <stdio.h>
#include "windows_events.h"

extern "C" unsigned int _click(int x, int y, unsigned int button){
    printf("Hello world\n");
    return 0;
}

