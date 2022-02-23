#include "why.h"

#include <stdio.h>

static Deck* _generate_pentagonal_numbers(Uint n_items)
{
    Uint n;
    Uint p;
    Deck* numbers;

    numbers = DeckCreateUint();
    n = 1;
    while (n < n_items)
    {
        p = (n * (3 * n - 1)) / 2;
        DeckPushBack(numbers, &p);

        ++ n;
    }

    return numbers;
}

static bool _is_pentagonal(Uint n, const Deck* p_numbers)
{
    return DeckBinSearch(p_numbers, &n, CompareUint) != NULL;
}

static Uint _find_diff(const Deck* numbers)
{
    Uint j, k;
    Uint lhs, rhs;
    Uint diff, sum, min_diff;

    j = 0;
    min_diff = (1 << 31);
    while (j < DeckNItems(numbers))
    {
        lhs = *(Uint *)DeckPointAt(numbers, j);
        k = j + 1;
        while (k < DeckNItems(numbers))
        {
            rhs = *(Uint *)DeckPointAt(numbers, k);
            diff = rhs - lhs;
            sum = lhs + rhs;

            if (_is_pentagonal(diff, numbers) && _is_pentagonal(sum, numbers))
            {
                // if (diff < min_diff)
                //     min_diff = diff;
                return diff;
            }

            ++ k;
        }
        ++ j;
    }

    return min_diff;
}

int main()
{
    Deck* numbers;
    Uint n;

    numbers = _generate_pentagonal_numbers(5000);
    // PrintDeck(numbers, PrintUintN);
    n = _find_diff(numbers);
    PrintUintN(&n);

    DeckDestroy(numbers);

    return 0;
}