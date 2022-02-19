#include "why.h"
#include <stdlib.h>
#include <stdio.h>

#define _MAX (99)

static Int _common_digit(Uint a, Uint b)
{
    Uint buffer[4];

    buffer[0] = a / 10;
    buffer[1] = a % 10;
    buffer[2] = b / 10;
    buffer[3] = b % 10;

    return buffer[0] * (buffer[0] == buffer[2] || buffer[0] == buffer[3]) +
            buffer[1] * (buffer[1] == buffer[2] || buffer[1] == buffer[3]);
}

static Uint _remove_digit(Uint n, Uint digit)
{
    if (digit == n % 10)
        return n / 10;
    
    return n % 10;
}

static Int _is_special(Uint top, Uint bot)
{
    Int         digit;
    Int         result;
    Rational*   p;
    Rational*   q;

    digit = _common_digit(top, bot);
    if (digit == NOT_FOUND || digit == 0)
        return false;
    
    p = RationalCreate(top, bot);
    q = RationalCreate(_remove_digit(top, digit), _remove_digit(bot, digit));

    result = RationalEquals(p, q) ? top : 0;
    RationalDestroy(p);
    RationalDestroy(q);

    return result;
}

int main()
{
    WhyStart();

    Uint top, bot;
    Uint top_product, bot_product;
    Rational* p;

    p = RationalCreate(1, 1);
    top_product = 1;
    bot_product = 1;
    top = 11;
    while (top <= _MAX)
    {
        bot = top + 1;
        while (bot <= _MAX)
        {
            if (_is_special(top, bot))
            {
                top_product *= top;
                bot_product *= bot;
                // printf("%zu / %zu\n", top, bot);
            }
            ++ bot;
        }
        ++ top;
    }

    RationalInit(p, top_product, bot_product);
    PrintRationalN(&p);
    // PrintUintN(&product);

    WhyEnd();
    return EXIT_SUCCESS;
}