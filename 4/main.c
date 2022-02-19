#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define BASE (10)
#define MAX_DIGITS (6)

static Uint powers_of_ten[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

static Byte _get_n_digits(Uint number)
{
    Byte n_digits;

    if (number == 0)
        return 1;

    n_digits = 0;
    while (number)
    {
        number = number / BASE;
        ++ n_digits;
    }

    return n_digits; 
}

static Byte _get_nth_digit(Uint number, Byte n)
{
    return (number % powers_of_ten[n + 1]) / powers_of_ten[n];
}

static bool _is_palindrome(Uint number)
{
    Byte left_digit;
    Byte right_digit;
    Uint left_index;
    Uint right_index;

    left_index = 0;
    right_index = _get_n_digits(number) - 1;

    while (left_index < right_index)
    {
        left_digit = _get_nth_digit(number, left_index);
        right_digit = _get_nth_digit(number, right_index);

        if (left_digit != right_digit)
            return false;
        
        ++ left_index;
        -- right_index;
    }

    return true;
}

static Uint _find_largest_palindrome(Uint low, Uint high)
{
    Uint a, b;
    Uint largest;
    Uint current;

    b = high;
    largest = 0;

    while (b >= low)
    {
        a = b;
        while (a >= low)
        {
            current = a * b;
            if (current < largest)
                break ;
            
            if (_is_palindrome(current))
            {
                if (current > largest)
                    largest = current;
            }

            -- a;
        }

        -- b;
    }

    return largest;
}

int main()
{
    Uint palindrome;

    palindrome = _find_largest_palindrome(100, 999);
    PrintUintN(&palindrome);

    return EXIT_SUCCESS;
}