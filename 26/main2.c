#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define SIZE (1000)

static Uint ENCOUNTERED[SIZE];

static void _reset_table()
{
    Uint n;

    n = 0;
    while (n < SIZE)
    {
        ENCOUNTERED[n] = 0;
        ++ n;
    }
}

static Uint _find_cycle(Uint top, Uint bot)
{
    static Uint count;
    Uint        remainder;

    ++ count;
    top *= 10;

    while (top < bot)
    {
        ++ count;
        top *= 10;
    }

    remainder = top % bot;
    
    if (remainder == 0)
        return 0;
    
    if (ENCOUNTERED[remainder])
        return count - ENCOUNTERED[remainder];
    
    ENCOUNTERED[remainder] = count;

    return _find_cycle(remainder, bot);
}

static Uint _find_max_cycle()
{
    Uint current;
    Uint max;
    Uint n_max;
    Uint bot;

    bot = 2;
    max = 0;
    n_max = bot;

    while (bot < SIZE)
    {
        _reset_table();
        current = _find_cycle(1, bot);
        
        if (current > max)
        {
            max = current;
            n_max = bot;
        }

        ++ bot;
    }

    return n_max;
}

int main()
{
    Uint result;

    result = _find_max_cycle();

    PrintUintN(&result);

    return EXIT_SUCCESS;
}