#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define N_ITERATIONS (1000000)
#define N_ITEMS (10)

int main()
{
    Block*  block;
    Uint    count;
    Byte    letters[] = "0123456789";

    block = BlockCreate(N_ITEMS, Byte);
    BlockInitFromArray(block, letters);
    count = 1;
    // PrintBlockN(block, PrintCharS);

    while (count < N_ITERATIONS)
    {
        BlockPermuteLexical(block, CompareByte);
        ++ count;
    }

    PrintBlockN(block, PrintCharS);

    BlockDestroy(block);

    return EXIT_SUCCESS;
}