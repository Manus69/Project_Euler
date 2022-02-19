#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define SIZE (1 << 14)
#define LIMIT (10000)

static Uint DIVISOR_SUM[SIZE];

static Uint _sum_divisors(const Deck* divisors, Uint n)
{
    Uint sum;

    sum = 0;
    DeckFold(&sum, divisors, UintAddWRAP);

    return sum - n;
}

static void _compute_divisor_sums()
{
    Uint    n;
    Uint    sum;
    Deck*   divisors;

    n = 1;
    while (n <= LIMIT)
    {
        if (!MathIsPrime(n))
        {
            divisors = MathComputeDivisors(n);
            sum = _sum_divisors(divisors, n);
            DIVISOR_SUM[n] = sum;
            DeckDestroy(divisors);
        }

        ++ n;
    }
}

static bool _is_amicable(Uint n)
{
    Uint sum;

    sum = DIVISOR_SUM[n];

    return sum <= LIMIT ? (DIVISOR_SUM[sum] == n && n != sum) : false;
}

static Uint _sum_amicable_numbers()
{
    Uint n;
    Uint sum;

    n = 1;
    sum = 0;
    while (n <= LIMIT)
    {
        if (_is_amicable(n))
        {
            sum += n;
        }
        ++ n;
    }

    return sum;
}

int main()
{
    Uint sum;

    WhyStart();
    MathUnitInit(SIZE);

    _compute_divisor_sums();

    sum = _sum_amicable_numbers();
    PrintUintN(&sum);

    WhyEnd();

    return EXIT_SUCCESS;
}