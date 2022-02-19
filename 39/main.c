#include "why.h"

#include <stdio.h>

static Uint _count_solutions(Uint p)
{
    Uint a, b;
    Uint sum;
    Uint result;

    sum = 0;
    a = 1;
    while (a < p - 1)
    {
        b = a;
        while (b < p - a - 1)
        {
            result = 2 * (p * (a + b) - a * b);
            if ((p * p) == result)
            {
                // PrintUintN(&a);
                // PrintUintN(&b);
                ++ sum;
            }
            ++ b;
        }
        ++ a;
    }

    return sum;
}

#define _MAX (1000)

int main()
{
    Uint p;
    Uint max, max_p, current;

    max = 0;
    max_p = 0;
    p = 3;
    while (p < _MAX)
    {
        current = _count_solutions(p);

        if (current > max)
        {
            max = current;
            max_p = p;
        }

        ++ p;
    }

    PrintUintN(&max_p);

    return 0;
}