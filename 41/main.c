#include "why.h"

#include <stdio.h>

static Uint _generate_pandigital(Uint n_digits)
{
    char buffer[10];
    char digit;
    uint32_t result;
    Uint max;

    UintToStringBuffer(buffer, 123456789, 10);
    while (StringPermuteLexicalSlice(buffer, n_digits))
    {
        // printf("%s\n", buffer);
        digit = (buffer[n_digits - 1] - '0');
        if (digit % 2 == 0 || digit % 5 == 0)
            continue ;
        
        ParseUint32(&result, buffer, n_digits);
        // printf("%u\n", result);

        if (MathIsPrime(result))
        {
            // printf("%u\n", result);
            max = result;
        }
    }
    
    return max;
}

int main()
{
    WhyStart();
    MathUnitInit(1000000);

    Uint n_digits;
    Uint max;

    n_digits = 3;

    while (n_digits < 10)
    {
        max = _generate_pandigital(n_digits);
        ++ n_digits;
    }

    PrintUintN(&max);

    MathUnitTerminate();
    WhyEnd();

    return 0;
}