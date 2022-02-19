#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define LIMIT (28123)
#define TRUE (1)
#define FALSE (-1)
#define SMALLEST (12)

static int IS_ABUNDANT[LIMIT + 1];

static int _is_abundant(Uint n)
{
    Deck* divisors;
    Uint sum;

    if (IS_ABUNDANT[n])
        return IS_ABUNDANT[n];

    divisors = MathComputeDivisors(n);
    // PrintDeck(divisors, PrintUintN);
    sum = 0;
    DeckFold(&sum, divisors, UintAddWRAP);
    sum -= n;

    DeckDestroy(divisors);

    IS_ABUNDANT[n] = sum > n ? TRUE : FALSE;

    return IS_ABUNDANT[n];
}

static bool _is_representable(Uint n)
{
    Uint lhs;
    Uint rhs;

    if (n < SMALLEST)
        return false;
    
    lhs = SMALLEST;

    while (lhs <= n / 2)
    {
        rhs = n - lhs;
        if ((_is_abundant(lhs) == TRUE) && (_is_abundant(rhs) == TRUE))
        {
            // printf("%zu = %zu + %zu\n", n, lhs, rhs);
            return true;
        }

        ++ lhs;
    }

    return false;
}

static Uint _sum()
{
    Uint n;
    Uint sum;

    n = 1;
    sum = 0;

    while (n <= LIMIT)
    {
        if (!_is_representable(n))
        {
            sum += n;
        }

        ++ n;
    }

    return sum;
}

int main()
{
    WhyStart();
    MathUnitInit(LIMIT);

    Uint sum = _sum();
    PrintUintN(&sum);

    MathUnitTerminate();
    WhyEnd();

    return EXIT_SUCCESS;
}