#include "why.h"

#include <stdio.h>
#include <stdlib.h>

// static Uint test_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static Uint array[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                        11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

int main()
{
    Uint lcm;

    // lcm = MathLCMArray(test_array, 10);
    lcm = MathLCMArray(array, 20);
    PrintUintN(&lcm);

    return EXIT_SUCCESS;
}