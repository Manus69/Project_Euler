#include "why.h"

#include <stdio.h>
#include <string.h>

#define MAX_DIGITS (100)
#define _MAX (1000000)

static bool _is_palindrome(const char* string)
{
    Uint length;
    Uint n;

    n = 0;
    length = strlen(string);

    if (length < 2)
        return true;

    -- length;
    while (n < length)
    {
        if (string[n] != string[length])
            return false;
        
        ++ n;
        -- length;
    }

    return true;
}

static bool _check_number(Uint n)
{
    char decimal[MAX_DIGITS];
    char binary[MAX_DIGITS];

    UintToStringBuffer(decimal, n, 10);
    UintToStringBuffer(binary, n, 2);

    if (_is_palindrome(decimal) && _is_palindrome(binary))
        return true;

    return false;
}

int main()
{
    Uint n;
    Uint sum;
    
    n = 1;
    sum = 0;
    while (n < _MAX)
    {
        if (_check_number(n))
        {
            // PrintUintN(&n);
            sum += n;
        }

        ++ n;
    }

    PrintUintN(&sum);

    return 0;
}