#include "why.h"

#include <stdio.h>

#define _MAX (1000000)
static int DIGITS[_MAX];

static Uint _digits(Uint n)
{
    Uint digits;
    Uint digit;

    if (DIGITS[n])
        return DIGITS[n];

    if (n == 0)
    {
        return (DIGITS[0] = 1);
    }
    
    digits = 0;
    while (n)
    {
        digit = n % 10;
        digits = digits | (1 << digit);
        n /= 10;
    }

    return (DIGITS[n] = digits);
}

static bool _same_digits(Uint lhs, Uint rhs)
{
    return _digits(lhs) == _digits(rhs);
}

int main()
{
    Uint n;

    n = 1;
    while (true)
    {
        if (_digits(n) == _digits(2 * n) && 
            _digits(n) == _digits(3 * n) &&
            _digits(n) == _digits(4 * n) &&
            _digits(n) == _digits(5 * n) &&
            _digits(n) == _digits(6 * n))
        {
            break ;
        }

        ++ n;
    }

    PrintUintN(&n);

    return 0;
}