#include "why.h"

#include <stdio.h>

#define SIZE (1000000)
static Uint POWERS_OF_TEN[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
static int CIRCULAR_PRIMES[SIZE];

static bool _has_zero(Uint n)
{
    while (n)
    {
        if (n % 10 == 0)
            return true;
        n /= 10;
    }

    return false;
}

static Uint _rotate_digits(Uint n)
{
    Uint n_digits;
    Uint digit;

    n_digits = MathCountDigits(n);

    if (n_digits < 2)
        return n;
    
    digit = n % 10;
    n = n / 10;
    digit = digit * POWERS_OF_TEN[n_digits - 1];

    return digit + n;
}

static bool _compute_circular(Uint p)
{
    Uint n;

    if (_has_zero(p))
    {
        return (CIRCULAR_PRIMES[p] = 0);
    }

    n = p;
    while (true)
    {
        n = _rotate_digits(n);

        if (!MathIsPrime(n))
            return (CIRCULAR_PRIMES[p] = 0);

        if (CIRCULAR_PRIMES[n])
            return (CIRCULAR_PRIMES[p] = 1);
        
        if (n == p)
            return (CIRCULAR_PRIMES[p] = 1);
    }
}

int main()
{
    WhyStart();
    MathUnitInit(SIZE);

    Uint n;
    Uint sum;

    n = 2;
    sum = 0;

    while (n < SIZE)
    {
        if (MathIsPrime(n))
        {
            if (_compute_circular(n))
            {
                // PrintUintN(&n);
                sum += 1;
            }
        }
        ++ n;
    }

    PrintUintN(&sum);

    MathUnitTerminate();
    WhyEnd();

    return 0;
}