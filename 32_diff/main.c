#include "why.h"

#include <stdio.h>

#define VALUE (((1 << 9) - 1) << 1)

static bool _all_used(Uint digits)
{
    return digits == VALUE;
}

static void _mark_digit_as_used(Uint* digits, Uint digit)
{
    *digits = *digits | (1 << digit);
}

static void _mark_all_digits_as_used(Uint* digits, Uint number)
{
    while (number)
    {
        _mark_digit_as_used(digits, number % 10);
        number /= 10;
    }
}

static bool _check_digits(Uint* digits, Uint lhs, Uint rhs, Uint result)
{
    _mark_all_digits_as_used(digits, lhs);
    _mark_all_digits_as_used(digits, rhs);
    _mark_all_digits_as_used(digits, result);

    return _all_used(*digits);
}

static Deck* _numbers(Uint lhs_start, Uint lhs_end, Uint rhs_start, Uint rhs_end, Uint max)
{
    Uint result;
    Uint digits;
    Uint lhs, rhs;
    Deck* numbers;

    numbers = DeckCreateUint();
    lhs = lhs_start;
    while (lhs < lhs_end)
    {
        rhs = rhs_start;
        while (rhs < rhs_end)
        {
            digits = 0;
            result = lhs * rhs;

            if (result > max)
                break ;
            
            if (_check_digits(&digits, lhs, rhs, result))
            {
                // printf("%zu * %zu == %zu\n", lhs, rhs, result);
                DeckPushBack(numbers, &result);
            }
            ++ rhs;
        }
        ++ lhs;
    }

    return numbers;
}


int main()
{
    Deck* lhs;
    Deck* rhs;
    // _numbers(39, 40, 186, 200, 9999);
    lhs = _numbers(11, 100, 111, 1000, 9999);
    rhs =_numbers(1, 10, 1111, 10000, 9999);

    DeckAppend(lhs, rhs);

    Deck* unique = DeckUnique(lhs, CompareUint);
    // PrintDeck(unique, PrintUintN);

    Uint result;
    DeckFold(&result, unique, UintAddWRAP);
    PrintUintN(&result);

    DeckDestroy(lhs);
    DeckDestroy(rhs);
    DeckDestroy(unique);

    return 0;
}