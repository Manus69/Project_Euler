#include "why.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Uint p;

    p = MathGetNthPrime(10001);
    PrintUintN(&p);

    return EXIT_SUCCESS;
}