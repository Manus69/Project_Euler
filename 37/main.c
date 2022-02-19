#include "why.h"

#include <stdio.h>
#define SIZE (1000000)

static Uint POWERS[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

static Uint _remove_right(Uint n)
{
    return n / 10;
}

static Uint _remove_left(Uint n)
{
    Uint n_digits;
    Uint result;

    n_digits = MathCountDigits(n);
    if (n_digits == 1)
        return 0;

    result = n / POWERS[n_digits - 1];
    
    return n - result * POWERS[n_digits - 1];
}

static bool _is_special(Uint n)
{
    Uint left;
    Uint right;

    if (!MathIsPrime(n))
        return false;

    if (n < 10)
        return false;
    
    left = n;
    while (true)
    {
        left = _remove_left(left);

        if (!MathIsPrime(left))
            return false;
        
        if (left < 10)
            break ;
    }

    right = n;
    while (true)
    {
        right = _remove_right(right);

        if (!MathIsPrime(right))
            return false;
        
        if (right < 10)
            break ;
    }

    return true;
}

int main()
{
    WhyStart();
    MathUnitInit(SIZE);

    Uint n;
    Uint sum;

    sum = 0;
    n = 11;
    while (n < SIZE)
    {
        if (_is_special(n))
        {
            // PrintUintN(&n);
            sum += n;
        }

        ++ n;
    }

    PrintUintN(&sum);

    MathUnitTerminate();
    WhyEnd();

    return 0;
}