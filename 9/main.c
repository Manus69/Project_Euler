#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define K (1000)
#define KK (K * K)

static bool _is_int(Uint top, Uint bot)
{
    return (top >= bot) && (top % bot == 0);
}

static bool _find_ab(Uint* a, Uint* b)
{
    Uint top_rhs;
    Uint top;
    Uint bot;
    Uint n;

    n = 1;
    while (true)
    {
        if (n >= K)
            return false;
        
        top_rhs = 2 * K * n;
        if (KK < top_rhs)
            return false;
        
        top = KK - top_rhs;
        bot = 2 * (K - n);

        if (_is_int(top, bot))
        {
            *a = top / bot;
            *b = n;

            return true;
        }

        ++ n;
    }
}

int main()
{
    Uint b;
    Uint a;
    Uint result;

    _find_ab(&a, &b);

    result = a * b * (K - a - b);
    PrintUintN(&result);

    return EXIT_SUCCESS;
}