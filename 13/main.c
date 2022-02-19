#include "why.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define _FILE ("file.txt")
#define N_DIGITS (10)

static Deck* _get_numbers(const Deck* strings)
{
    Uint        n;
    Natural*    number;
    const char* current;
    Deck*       numbers;

    numbers = DeckCreatePtr(NULL, NaturalDestroyWRAP);
    n = 0;

    while (n < DeckNItems(strings))
    {
        current = *(const char **)DeckPointAt(strings, n);
        number = NaturalCreate(current);

        DeckPushBack(numbers, number);
        ++ n;
    }

    return numbers;
}

static Natural* _sum_numbers(const Deck* numbers)
{
    Natural*    sum;
    Natural*    current;
    Uint        n;

    sum = NaturalCreate("0");
    n = 0;

    while (n < DeckNItems(numbers))
    {
        current = *(Natural **)DeckPointAt(numbers, n);
        NaturalAdd(sum, sum, current);

        ++ n;
    }

    return sum;
}

int main()
{
    Deck*       strings;
    Deck*       numbers;
    Natural*    sum;
    char*       string;

    WhyStart();

    if (!(strings = ReadFileAllLines2(_FILE)))
        return EXIT_FAILURE;

    numbers = _get_numbers(strings);

    sum = _sum_numbers(numbers);
    string = NaturalToString(sum);

    printf("%.10s\n", string);

    free(string);
    NaturalDestroy(sum);
    DeckDestroy(numbers);
    DeckDestroy(strings);
    
    WhyEnd();

    return EXIT_SUCCESS;
}
