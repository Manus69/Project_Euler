#include "why.h"

#include <stdio.h>

#define SIZE (1000000)

int main()
{
    static char buffer[SIZE + 10];
    Uint n;
    Uint product;
    Uint index;

    index = 0;
    n = 1;

    while (true)
    {
        index += UintToStringBuffer(buffer + index, n, 10);

        if (index > SIZE)
            break ;
        
        ++ n;
    }

    // printf("%*s\n", 10, buffer);

    n = 1;
    product = 1;
    while (n <= SIZE)
    {
        product *= (buffer[n - 1] - '0');
        n *= 10;
    }

    PrintUintN(&product);

    return 0;
}