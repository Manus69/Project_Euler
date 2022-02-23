#include "why.h"

#include <stdio.h>
#define SIZE (100000)

static Uint _triangular(Uint n)
{
    return (n * (n + 1)) / 2; 
}

static Uint _pentagonal(Uint n)
{
    return (n * (3 * n - 1)) / 2;
}

static Uint _hexagonal(Uint n)
{
    return (n *(2 * n - 1));
}

static Block* _get_numbers(Uint size, Uint (*function)(Uint))
{
    Block* block;
    Uint n, number;

    block = BlockCreateUint(size);
    n = 0;

    while (n < size)
    {
        number = function(n);
        BlockSet(block, n, &number);

        ++ n;
    }

    return block;
}

static Uint _find_next(Uint start, const Block* t, const Block* p, const Block* h)
{
    Uint* number;

    while (start < SIZE)
    {
        number = BlockPointAt(t, start);

        if (BlockBinSearch(p, number, CompareUint) && BlockBinSearch(h, number, CompareUint))
            return *number;

        ++ start;
    }

    return 0;
}

int main()
{
    Block* triangular;
    Block* pentagonal;
    Block* hexagonal;

    triangular = _get_numbers(SIZE, _triangular);
    pentagonal = _get_numbers(SIZE, _pentagonal);
    hexagonal = _get_numbers(SIZE, _hexagonal);

    Uint result;
    result = _find_next(286, triangular, pentagonal, hexagonal);
    PrintUintN(&result);

    BlockDestroy(triangular);
    BlockDestroy(pentagonal);
    BlockDestroy(hexagonal);
}