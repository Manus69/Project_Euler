#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define _FILE ("words.txt")
#define MAX_INDEX (99)

static void _strip(void* string)
{
    char* new;

    new = StringStrip(*(char **)string, '"', '"');
    WhySavePtr(&new);
    *(void **)string = new;
}

static Uint _compute_score(const char* string)
{
    Uint score;

    score = 0;
    while (*string)
    {
        score += (*string - 'A' + 1);
        ++ string;
    }

    return score;
}

static Block* _triangular_init()
{
    Block* numbers;
    Uint n, result;

    numbers = BlockCreateUint(MAX_INDEX + 1);
    n = 0;
    while (n <= MAX_INDEX)
    {
        result = (n * (n + 1)) / 2;
        BlockSet(numbers, n, &result);
        ++ n;
    }

    return numbers;
}

static void* _is_triangular(Uint score, const Block* numbers)
{
    return BlockBinSearch(numbers, &score, CompareUint);
}

static Uint _count_words(const Deck* words)
{
    Block* numbers;
    char* string;
    Uint n, sum, score;

    numbers = _triangular_init();
    n = 0;
    sum = 0;

    while (n < DeckNItems(words))
    {
        string = *(char **)DeckPointAt(words, n);
        score = _compute_score(string);

        if (_is_triangular(score, numbers))
        {
            // PrintCstrS(&string);
            // PrintUintN(&score);
            ++ sum;
        } 
        
        ++ n;
    }

    BlockDestroy(numbers);

    return sum;
}

int main()
{
    WhyStart();

    char* string;
    Deck* strings;
    Uint result;

    string = (char *)ReadFile(_FILE);
    strings = StringSplitDestructive(string, ',');
    DeckMap(strings, _strip);

    result = _count_words(strings);
    PrintUintN(&result);

    DeckDestroy(strings);
    free(string);

    WhyEnd();

    return 0;
}