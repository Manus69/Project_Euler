#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define _MAX (300000)

static Uint _weighted_digit_sum(Uint n, Uint power)
{
    Uint sum;
    Uint digit;

    sum = 0;

    while (n)
    {
        digit = n % 10;
        sum += MathPower(digit, power);
        n = n / 10;
    }

    return sum;
}

int main()
{
    Uint n;
    Uint sum;

    sum = 0;
    n = 2;
    while (n < _MAX)
    {
        if (n == _weighted_digit_sum(n, 5))
            sum += n;
        
        ++ n;
    }

    PrintUintN(&sum);

    return EXIT_SUCCESS;
}