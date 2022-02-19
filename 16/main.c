#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define N_DIGITS (2000)

static Uint DIGITS[N_DIGITS];

static void _print_digits(const Uint* digits, Uint n_digits)
{
    if (n_digits > 1)
        _print_digits(digits + 1, -- n_digits);
    
    printf("%zu", *digits);
}

static Uint _sum_digits(Uint n_digits)
{
    Uint n;
    Uint sum;

    sum = 0;
    n = 0;

    while (n < n_digits)
    {
        sum += DIGITS[n];
        ++ n;
    }

    return sum;
}

static Uint _double(Uint n, Uint carry, Uint last_index)
{
    Uint digit;

    if (n > last_index)
    {
        DIGITS[n] = carry;
        return carry ? n : last_index;
    }

    digit = DIGITS[n] * 2 + carry;
    if (digit < 10)
    {
        DIGITS[n] = digit;

        return _double(n + 1, 0, last_index);
    }
    else
    {
        DIGITS[n] = digit % 10;

        return _double(n + 1, 1, last_index);
    }
}

static Uint _double_n_times(Uint n)
{
    Uint index;

    index = 0;
    while (n)
    {
        index = _double(0, 0, index);
        -- n;
    }

    return index + 1;
}

int main()
{
    Uint n_digits;
    Uint sum;

    DIGITS[0] = 1;

    n_digits = _double_n_times(1000);
    sum = _sum_digits(n_digits);
    PrintUintN(&sum);

    return EXIT_SUCCESS;
}