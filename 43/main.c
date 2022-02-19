#include "why.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Uint PRIMES[] = {2, 3, 5, 7, 11, 13, 17};

static Int _parse(uint32_t* target, const char* str, Uint length)
{
    if (*str == '0')
        return ParseUint32(target, str + 1, length - 1);
    
    return ParseUint32(target, str, length);
}

static bool _check_substring(const char* string, Uint offset)
{
    uint32_t result;

    _parse(&result, string + offset, 3);

    return (result % PRIMES[offset - 1]) == 0;
}

static bool _check_number_string(const char* string)
{
    Uint offset;

    offset = 1;
    while (offset <= 7)
    {
        if (!_check_substring(string, offset))
            return false;
        
        ++ offset;
    }

    return true;
}

int main()
{
    char* number_string;
    Uint sum;
    uint32_t number;

    sum = 0;
    number_string = strdup("0123456789");
    while (true)
    {
        if (_check_number_string(number_string))
        {
            // printf("%s\n", number_string);
            ParseUint32(&number, number_string, 10);
            sum += number;
        }

        if (StringPermuteLexicalSlice(number_string, 10) == false)
            break ;
    }

    free(number_string);
    PrintUintN(&sum);

    return 0;
}