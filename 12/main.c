#include "why.h"

#include <stdio.h>
#include <stdlib.h>

static Deck* _get_divisors_for_triag_number(Uint n)
{
    Deck* n_divisors;
    Deck* n1_divisors;

    if (n % 2 == 0)
    {
        n_divisors = MathFactor(n / 2);
        n1_divisors = MathFactor(n + 1);
    }
    else
    {
        n_divisors = MathFactor(n);
        n1_divisors = MathFactor((n + 1) / 2);
    }

    DeckAppend(n_divisors, n1_divisors);
    DeckDestroy(n1_divisors);

    SortDeck(n_divisors, CompareUint);

    return n_divisors;
}

static Uint _count_divisors(const Deck* prime_divisors)
{
    Uint p_count;
    Uint n_subsets;
    Uint previous;
    Uint current;
    Uint n;
    Uint n_items;

    if ((n_items = DeckNItems(prime_divisors)) == 1)
        return 2;
    
    n_subsets = 1;
    DeckFirst(&previous, prime_divisors);
    p_count = 1;
    n = 1;

    while (n < n_items)
    {
        current = *(Uint *)DeckPointAt(prime_divisors, n);

        if (current != previous)
        {
            n_subsets = n_subsets * (p_count + 1);
            p_count = 1;
            previous = current;
        }
        else
            ++ p_count;

        ++ n;
    }
    
    return n_subsets * (p_count + 1);
}

static Uint _find_number_with_divisors(Uint n_divisors)
{
    Uint    n;
    Uint    count;
    Deck*   divisors;

    n = 7;

    while (true)
    {
        divisors = _get_divisors_for_triag_number(n);
        count = _count_divisors(divisors);

        DeckDestroy(divisors);
        if (count >= n_divisors)
            return (n * (n + 1)) / 2;

        ++ n;
    }
}

int main()
{   
    Uint number;
    
    WhyStart();
    number = _find_number_with_divisors(500);
    PrintUintN(&number);
    WhyEnd();

    return EXIT_SUCCESS;
}