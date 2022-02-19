#include "why.h"

#include <stdio.h>
#include <stdlib.h>

static Uint _sum_fib(Uint cap)
{
    Uint sum;
    Uint current;
    Uint n;

    n = 0;
    sum = 0;

    while (true)
    {
        current = MathFib(n);

        if (current > cap)
            break ;

        if (current % 2)
            sum += current;
        
        ++ n;
    }

    return sum;
}

int main()
{
    Uint sum;

    sum = _sum_fib(4000000);
    PrintUintN(&sum);

    return EXIT_SUCCESS;
}