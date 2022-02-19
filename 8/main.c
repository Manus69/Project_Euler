#include "why.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "file.txt"

static Uint _evaluate_substring(const Byte* string, Uint index, Int size)
{
    const Byte*   current;
    Uint          value;
    
    value = 1;
    current = string + index;

    while (*current && size)
    {
        value = value * (*current - '0');
        ++ current;
        -- size;
    }

    return value;
}

static Uint _roll(const Byte* string, Uint value, Uint start, Uint frame_size)
{
    Byte left;

    left = string[start];

    if (left == '0')
        return _evaluate_substring(string, start + 1, frame_size);

    if (value == 0)
        return 0;

    value /= (string[start] - '0');
    value *= (string[start + frame_size] - '0');

    return value;
}

static Uint _find_max_roll(const Byte* string, Uint frame_size)
{
    Uint    length;
    Uint    index;
    Uint    value;
    Uint    max;

    if ((length = strlen((const char *)string)) == 0)
        return 0;
    
    value = _evaluate_substring(string, 0, frame_size);
    max = value;
    index = 0;

    while (index + frame_size < length)
    {
        value = _roll(string, value, index, frame_size);

        if (value > max)
            max = value;
        
        ++ index;
    }

    return max;
}

int main()
{
    Byte*   string;
    Deck*   lines;
    Int     value;

    WhyStart();

    if (!(lines = ReadFileAllLines(FILE_NAME)))
        return EXIT_FAILURE;

    if (!(string = StringConcatDeck(lines)))
    {
        DeckDestroy(lines);
        return EXIT_FAILURE;
    }

    PrintCstrN(&string);

    value = _find_max_roll(string, 13);
    PrintUintN(&value);

    DeckDestroy(lines);
    free(string);
    WhyEnd();

    return EXIT_SUCCESS;
}