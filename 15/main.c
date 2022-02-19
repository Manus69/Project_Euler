#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE (100)
#define INIT_SIZE (4)

static Uint N_PATHS_FROM_ORIGIN[TABLE_SIZE][TABLE_SIZE];

static Uint _compute_n_paths(Uint x0, Uint y0, Uint x1, Uint y1)
{
    if ((x0 == x1) || (y0 == y1))
        return 1;
    
    return _compute_n_paths(x0 + 1, y0, x1, y1) + _compute_n_paths(x0, y0 + 1, x1, y1);
}

static void _shift(Uint* x0, Uint* y0, Uint* x1, Uint* y1)
{
    *x1 -= *x0;
    *y1 -= *y0;
    *x0 = 0;
    *y0 = 0;
}

static Uint _compute_n_paths_long(Uint x0, Uint y0, Uint x1, Uint y1)
{
    Uint left;
    Uint right;

    if ((x0 == x1) || (y0 == y1))
        return 1;
    
    _shift(&x0, &y0, &x1, &y1);

    if (N_PATHS_FROM_ORIGIN[x1][y1] == 0)
    {
        left = _compute_n_paths_long(0, 0, x1, y1 - 1);
        right = _compute_n_paths_long(0, 0, x1 - 1, y1);

        N_PATHS_FROM_ORIGIN[x1][y1] = left + right;
        N_PATHS_FROM_ORIGIN[y1][x1] = N_PATHS_FROM_ORIGIN[x1][y1];
    }

    return N_PATHS_FROM_ORIGIN[x1][y1];
}

static void _table_init()
{
    Uint x;
    Uint y;

    x = 1;

    while (x <= INIT_SIZE)
    {
        y = 1;
        while (y <= INIT_SIZE)
        {
            N_PATHS_FROM_ORIGIN[x][y] = _compute_n_paths(0, 0, x, y);
            ++ y;
        }
        ++ x;
    }
}

int main()
{
    Uint n_paths;
    Uint size;

    _table_init();

    size = 20;
    n_paths = _compute_n_paths_long(0, 0, size, size);
    PrintUintN(&n_paths);

    return EXIT_SUCCESS;
}