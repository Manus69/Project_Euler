#include "why.h"

#include <stdio.h>
#include <stdlib.h>

static Uint _sum_multiples(Uint number, Uint cap)
{
    Uint sum;
    Uint current;

    sum = 0;
    current = number;
    while (current < cap)
    {
        sum += current;
        current += number;
    }

    return sum;
}

static Uint _sum_multiples_exclude(Uint number, Uint cap, Uint excluded)
{
    Uint sum;
    Uint current;

    sum = 0;
    current = number;

    while (current < cap)
    {
        if (current % excluded)
            sum += current;
        
        current += number;
    }

    return sum;
}

int main()
{
    Uint sum;
    Uint cap;

    cap = 1000;
    sum = _sum_multiples(3, cap) + _sum_multiples_exclude(5, cap, 3);
    PrintUintN(&sum);

    return EXIT_SUCCESS;
}