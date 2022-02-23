#include "why.h"

#include <stdio.h>
#include <limits.h>

#define MOD (10000000000)

static Uint _add_mod(Uint lhs, Uint rhs, Uint mod)
{
    return (lhs + rhs) % mod;
}

static Uint _power_mod(Uint base, Uint power, Uint mod)
{
    Uint result;

    result = 1;

    while (power)
    {
        result = (result * base) % mod;
        -- power;
    }
    
    return result;
}

static Uint _compute2(Uint n)
{
    Uint sum;
    Uint current;

    sum = 0;
    while (n)
    {
        current = _power_mod(n, n, MOD);
        sum = _add_mod(sum, current, MOD);
        -- n;
    }

    return sum;
}

int main()
{
    Uint n;
    n = _compute2(1000);
    PrintUintN(&n);

    return 0;
}