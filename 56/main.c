#include "why.h"

#include <stdio.h>

static Uint _digit_sum(const Natural* n)
{
    Uint sum;
    char* digits;

    digits = NaturalGetDigits(n);
    sum = 0;

    while (*digits)
    {
        sum += *digits - '0';
        ++ digits;
    }

    return sum;
}

static Uint _find_max_sum(Uint limit)
{
    Uint base, power;
    Natural* n;
    Uint current, max;

    max = 0;
    base = 2;
    n = NaturalCreateZero(300);

    while (base < limit)
    {
        if (base % 10 == 0)
        {
            ++ base;
            continue ;
        }

        power = 2;
        while (power < limit)
        {
            NaturalInit(n, base);
            NaturalPower(n, n, power);

            current = _digit_sum(n);

            if (current > max)
                max = current;

            ++ power;
        }
        ++ base;
    }

    NaturalDestroy(n);

    return max;
}

int main()
{
    Uint result;

    result = _find_max_sum(100);
    PrintUintN(&result);

    return 0;
}