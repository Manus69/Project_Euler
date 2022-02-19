#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define N_DIGITS (1000)

static Byte DIGITS[N_DIGITS];
static Uint _last_index = 0;

static void _display_digits()
{
    Int     n;
    Byte    digit;

    n = _last_index;

    while (n >= 0)
    {
        digit = DIGITS[n];
        printf("%d", digit);
        -- n;
    }
    printf("\n");
}

static Uint _add(Uint value, Uint n, Uint carry)
{
    Uint result;

    result = DIGITS[n] + value + carry;

    if (result >= 10)
    {
        DIGITS[n] = result % 10;

        return _add(0, n + 1, result / 10);
    }

    DIGITS[n] = result;

    return n;
}

static Uint _multiply(Uint value, Uint n, Uint carry)
{
    Uint result;
    
    result = DIGITS[n] * value + carry;

    if (result >= 10)
    {
        DIGITS[n] = result % 10;

        return _multiply(value, n + 1, result / 10);
    }

    DIGITS[n] = result;
    if (n < _last_index)
        return _multiply(value, n + 1, 0);

    return n;
}

static Uint _factorial(Uint n)
{
    while (n)
    {
        _last_index = _multiply(n, 0, 0);
        // _display_digits();
        -- n;
    }

    return _last_index;
}

static Uint _add_digits()
{
    Uint n;
    Uint sum;

    n = 0;
    sum = 0;
    while (n <= _last_index)
    {
        sum += DIGITS[n];
        ++ n;
    }

    return sum;
}

int main()
{
    Uint sum;

    _last_index = _add(1, 0, 0);
    _last_index = _factorial(100);
    // _display_digits();

    sum = _add_digits();
    PrintUintN(&sum);

    return EXIT_SUCCESS;
}