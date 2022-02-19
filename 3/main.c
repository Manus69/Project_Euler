#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define NUMBER (600851475143)

int main()
{
    Uint    largest_factor;
    Deck*   factors;
    
    factors = MathFactor(NUMBER);
    DeckLast(&largest_factor, factors);
    PrintUintN(&largest_factor);
    DeckDestroy(factors);

    return EXIT_SUCCESS;
}