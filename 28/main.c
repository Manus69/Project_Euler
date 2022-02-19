#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define SIZE (1001)

static Uint SPIRAL[SIZE][SIZE];

static Uint _compute_shell_top(Uint n, Uint size)
{
    return size / 2 - n;
}

static Uint _compute_shell_bot(Uint n, Uint size)
{
    return size / 2 + n;
}

static Uint _compute_n_shells(Uint size)
{
    return size / 2 + 1;
}

static void _fill_shell(Uint n, Uint size)
{
    Uint number;
    Int low;
    Int high;
    Int j, k;

    low = _compute_shell_top(n, size);
    high = _compute_shell_bot(n, size);

    if (n == 0)
    {
        SPIRAL[low][low] = 1;
        return ;
    }

    number = (high - low + 1);
    number *= number;

    j = low;
    k = high;
    while (k >= low)
    {
        SPIRAL[j][k] = number;
        -- number;
        -- k;
    }

    k = low;
    ++ j;
    while (j <= high)
    {
        SPIRAL[j][k] = number;
        -- number;
        ++ j;
    }

    j = high;
    ++ k;
    while (k <= high)
    {
        SPIRAL[j][k] = number;
        -- number;
        ++ k;
    }

    k = high;
    -- j;
    while (j > low)
    {
        SPIRAL[j][k] = number;
        -- number;
        -- j;
    }
}

static void _spiral_init()
{
    Uint n;
    Uint n_shells;

    n = 0;
    n_shells = _compute_n_shells(SIZE);

    while (n < n_shells)
    {
        _fill_shell(n, SIZE);
        ++ n;
    }
}

static Uint _sum_diagonals()
{
    Uint n;
    Uint sum;

    sum = 0;
    n = 0;
    while (n < SIZE)
    {
        sum += SPIRAL[n][n];
        ++ n;
    }

    n = 0;
    while (n < SIZE)
    {
        sum += SPIRAL[n][SIZE - n - 1];
        ++ n;
    }

    return sum - 1;
}

int main()
{
    Uint sum;

    _spiral_init();
    // _print_spiral();
    sum = _sum_diagonals();
    PrintUintN(&sum);

    return EXIT_SUCCESS;
}