#include "why.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_DIGITS (1000)

int main()
{
    char*   f0;
    char*   f1;
    char*   result;
    Uint    n_digits;
    Uint    n;

    n_digits = 0;
    f0 = MemZero(2 * N_DIGITS);
    f1 = MemZero(2 * N_DIGITS);
    result = MemZero(2 * N_DIGITS);

    NaturalInit(f0, 1);
    NaturalInit(f1, 1);
    n = 2;

    while (n_digits < N_DIGITS)
    {
        n_digits = NaturalAddRetDigits(result, f0, f1);

        NaturalSetLength(f0, f1, n_digits);
        NaturalSetLength(f1, result, n_digits);
        ++ n;
    }

    // PrintNatural(result);
    // printf("\n");
    PrintUintN(&n);

    free(f0);
    free(f1);
    free(result);

    return EXIT_SUCCESS;
}