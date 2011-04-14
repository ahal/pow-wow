#include <stdlib.h>
#include <stdio.h>
#include "../native_events.h"

extern "C" unsigned int _click(int x, int y, char flags[32], int button){
    printf("Hello world\n");
    return 0;
}

