#include "why.h"

#include <stdlib.h>
#include <stdio.h>

static Uint _sum_of_squares(Uint N)
{
    return (N * (N + 1) * (2 * N + 1)) / 6;
}

static Uint _square_of_sum(Uint N)
{
    return ((N * N) * (N + 1) * (N + 1)) / 4;
}

int main()
{
    Uint result;
    Uint N;

    N = 100;
    result = _square_of_sum(N) - _sum_of_squares(N);
    PrintUintN(&result);

    return EXIT_SUCCESS;
}