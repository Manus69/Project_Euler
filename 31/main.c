#include "why.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_VALUES (8)
#define MAX_VALUE (200)

// static Int VALUES[N_VALUES] = {1, 2, 5, 10, 20, 50, 100, 200};
static Uint VALUES[N_VALUES] = {200, 100, 50, 20, 10, 5, 2, 1};
static Int WAYS[N_VALUES][MAX_VALUE + 1];

static Int _compute(Uint n, Int target)
{
    Int result;

    if (target < 0)
        return 0;

    if (WAYS[n][target])
        return WAYS[n][target];

    if (target == 0)
        result = 1;
    else if (n == N_VALUES - 1)
        result = 1;
    else
    {
        result = _compute(n, target - VALUES[n]) + _compute(n + 1, target);
    }

    WAYS[n][target] = result;

    return result;
}

int main()
{
    WhyStart();

    Int target;
    Int n_ways;

    target = 200;
    n_ways = _compute(0, target);
    PrintIntN(&n_ways);

    WhyEnd();

    return EXIT_SUCCESS;
}