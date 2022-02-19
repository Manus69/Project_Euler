#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define _FILE ("p022_names.txt")

static void _strip_quotes(void* string)
{
    char* new_string;

    new_string = StringStrip(*(char **)string, '"', '"');
    WhySavePtr(new_string);
    *(char **)string = new_string;
}

static Uint _hash(const char* string)
{
    Uint hash;

    hash = 0;
    while (*string)
    {
        hash += *string - 'A' + 1;
        ++ string;
    }

    return hash;
}

static Uint _compute_score(const Deck* strings)
{
    Uint n;
    Uint sum;
    char* string;

    sum = 0;
    n = 0;

    while (n < DeckNItems(strings))
    {
        string = *(char **)DeckPointAt(strings, n);
        sum += _hash(string) * (n + 1);
        ++ n;
    }

    return sum;
}

int main()
{
    Byte*   bytes;
    Deck*   strings;
    Uint    sum;

    WhyStart();

    bytes = ReadFile(_FILE);
    strings = StringSplitDestructive((char *)bytes, ',');
    SortDeck(strings, CompareCstr);
    DeckMap(strings, _strip_quotes);
    // PrintDeck(strings, PrintCstrN);

    sum = _compute_score(strings);
    PrintUintN(&sum);

    DeckDestroy(strings);
    free(bytes);
    WhyEnd();

    return EXIT_SUCCESS;
}