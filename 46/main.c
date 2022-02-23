#include "why.h"

#include <stdio.h>

#define SIZE (1000000)

static Byte SQUARES[SIZE + 1];

void _init_squares()
{
    Uint n;
    Uint square;

    n = 0;
    while (true)
    {
        square = n * n;
        if (square > SIZE)
            return ;
        
        SQUARES[square] = 1;
        ++ n;
    }
}

//n is odd and composite
//n == p + 2 * square ?
static bool _check_odd_composite_number(Uint n, const Block* primes)
{
    Uint p;
    Uint diff;
    Uint index;
    Uint n_items;

    n_items = BlockNItems(primes);
    index = 0;
    while (index < n_items)
    {
        p = *(Byte *)BlockPointAt(primes, index);
        if (!p)
        {
            ++ index;
            continue ;
        }

        if (index >= n)
            return false;
        
        diff = n - index;
        if (diff % 2)
        {
            ++ index;
            continue ;
        }

        if (SQUARES[diff / 2])
            return true;

        ++ index;    
    }

    return false;
}

static Uint _find_number()
{
    Uint n;
    Block* sieve;

    sieve = MathGetSieve();

    n = 9;
    while (n < SIZE)
    {
        if (MathIsPrime(n) || n % 2 == 0)
        {
            ++ n;
            continue ;
        }

        if (!_check_odd_composite_number(n, sieve))
            return n;

        ++ n;
    }

    return 0;
}

int main()
{
    WhyStart();
    MathUnitInit(SIZE);

    _init_squares();

    Uint n = _find_number();
    PrintUintN(&n);

    MathUnitTerminate();
    WhyEnd();

    return 0;
}