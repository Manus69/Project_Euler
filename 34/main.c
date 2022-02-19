#include "why.h"

#include <stdio.h>

#define SIZE (10)
#define MAX_NUMBER (1000000)

static Uint FACTORIALS[SIZE];

static void _init_table()
{
    Uint n;

    n = 0;
    while (n < SIZE)
    {
        FACTORIALS[n] = MathFactorial(n);
        ++ n;
    }
}

static Uint _sum_digits(Uint n)
{
    Uint digit;
    Uint sum;

    if (n == 0)
        return 0;

    sum = 0;
    while (n)
    {
        digit = n % 10;
        digit = FACTORIALS[digit];
        sum += digit;
        n = n / 10;
    }

    return sum;
}

static Uint _sum_numbers()
{
    Uint n;
    Uint sum;

    sum = 0;
    n = 10;
    while (n < MAX_NUMBER)
    {
        if (n == _sum_digits(n))
            sum += n;

        ++ n;
    }

    return sum;
}

int main()
{
    _init_table();

    Uint sum = _sum_numbers();
    PrintUintN(&sum);

    return 0;
}