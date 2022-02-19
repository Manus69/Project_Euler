#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define LIMIT (1000)
#define SIEVE_SIZE (LIMIT * 10)
#define COEFF_LIMIT (1000)

static Int _pol_eval(Int a0, Int a1, Int x)
{
    return x * x + a1 * x + a0;
}

static Uint _count_consecutive_primes(Int a0, Int a1)
{
    Int n;
    Int result;

    n = 0;
    while (n < LIMIT)
    {
        result = _pol_eval(a0, a1, n);

        if (result <= 0)
            break ;

        if (!MathIsPrime(result))
            break ;
        
        ++ n;
    }

    return n;
}

static void _find_max(Int* a0, Int* a1)
{
    Int a0_max;
    Int a1_max;
    Int max_result;
    Int result;

    max_result = 0;

    *a0 = -COEFF_LIMIT;
    while (*a0 < COEFF_LIMIT)
    {
        *a1 = -COEFF_LIMIT;
        while (*a1 < COEFF_LIMIT)
        {
            result = _count_consecutive_primes(*a0, *a1);

            if (result > max_result)
            {
                max_result = result;
                a0_max = *a0;
                a1_max = *a1;
            }

            *a1 = *a1 + 1;
        }
        *a0 = *a0 + 1;
    }

    *a0 = a0_max;
    *a1 = a1_max;
}

int main()
{
    WhyStart();
    MathUnitInit(SIEVE_SIZE);

    Int a0, a1;
    Int product;

    _find_max(&a0, &a1);
    product = a0 * a1;
    PrintIntN(&product);

    MathUnitTerminate();
    WhyEnd();

    return EXIT_SUCCESS;
}