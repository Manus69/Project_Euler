#include "why.h"

#include <stdlib.h>
#include <stdio.h>

static Uint _count_numbers_in_sequence(Uint n)
{
    Uint count;

    count = 1;
    while (n > 1)
    {
        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;
        
        ++ count;
    }

    return count;
}

static Uint _find_longest_sequence(Uint cap)
{
    Uint n;
    Uint max_value;
    Uint max_n;
    Uint current;

    n = 2;
    max_value = 0;
    max_n = 1;

    while (n <= cap)
    {
        current = _count_numbers_in_sequence(n);

        if (current > max_value)
        {
            max_value = current;
            max_n = n;
        }

        ++ n;
    }

    return max_n;
} 

int main()
{
    Uint max;

    max = _find_longest_sequence(1000000);
    PrintUintN(&max);

    return EXIT_SUCCESS;
}