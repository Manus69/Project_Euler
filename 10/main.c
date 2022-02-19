#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define SIZE (2000000)

static Uint _sum(const Block* block)
{
    Uint    n;
    Uint    n_items;
    Uint    sum;
    Byte*   item;

    n = 0;
    n_items = BlockNItems(block);
    sum = 0;

    while (n < n_items)
    {
        item = BlockPointAt(block, n);

        if (*item)
            sum += n;
        
        ++ n;
    }

    return sum;
}

int main()
{
    Block*  sieve;
    Uint    sum;

    if (!(sieve = MathSieve(SIZE + 1)))
        return EXIT_FAILURE;
    
    sum = _sum(sieve);
    PrintUintN(&sum);
    
    BlockDestroy(sieve);

    return EXIT_SUCCESS;
}