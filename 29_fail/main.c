#include "why.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N (100)
#define LENGTH (100)

static void _print_byte_string(const Byte* string)
{
    Uint n;

    n = 0;
    while (n < LENGTH)
    {
        printf("%u ", string[n]);
        ++ n;
    }
    printf("\n");
}

static Uint _hash_byte_string(const Byte* string)
{
    Uint value;
    Uint n;

    value = 0;
    n = 0;

    while (n < LENGTH)
    {
        if (string[n])
            value += ((Uint)string[n] << n);

        ++ n;
    }

    return value;
    // return StringHashLength((const char *)string, LENGTH);
}

static Uint _hash_wrap(const void* string)
{
    return _hash_byte_string(*(Byte **)string);
}

static Int _compare_byte_string(const Byte* lhs, const Byte* rhs)
{
    Uint n;

    n = 0;
    while (n < LENGTH)
    {
        if (lhs[n] > rhs[n])
            return -1;
        else if (rhs[n] > lhs[n])
            return 1;
        
        ++ n;
    }

    return 0;
}

static Int _compare_wrap(const void* lhs, const void* rhs)
{
    return _compare_byte_string(*(const Byte **)lhs, *(const Byte **)rhs);
}

static Byte* _prime_string_create(Uint n)
{
    Byte* string;
    Deck* divisors;
    Uint index;

    divisors = MathFactor(n);
    index = 0;
    string = MemZero(LENGTH);

    // printf("n = %zu; divisors: ", n);
    // PrintDeck(divisors, PrintUintS);

    while (index < DeckNItems(divisors))
    {
        n = *(Uint *)DeckPointAt(divisors, index);
        ++ string[n];
        ++ index;
    }

    // _print_byte_string(string);

    DeckDestroy(divisors);

    return string;
}

static void _string_power(Byte* string, Uint n)
{
    Uint index;

    if (n == 1)
        return ;

    index = 0;
    while (index < LENGTH)
    {
        string[index] = string[index] ? string[index] * n : 0;
        ++ index;
    }
}

static void _generate_strings(HashTable* table)
{
    Uint base;
    Uint exp;
    Byte* string;

    base = 2;
    while (base <= N)
    {
        exp = 2;
        while (exp <= N)
        {
            string = _prime_string_create(base);
            WhySavePtr(&string);
            // _print_byte_string(string);
            _string_power(string, exp);
            // _print_byte_string(string);

            if (HashTableInsert(table, &string, _compare_wrap) == WHY_OK)
            {
                // printf("Adding %f ", pow(base, exp));
                // printf("Adding ");
                // _print_byte_string(string);
            }
            // else if (base < 10 && exp < 10)
            // {
            //     printf("%f \n", pow(base, exp));
            // }

            ++ exp;
        }
        ++ base;
    }
}

static void _power(Uint base)
{
    Uint _limit = 10;
    Uint power;
    Uint current;

    current = base;
    power = 1;
    while (power <= _limit)
    {
        PrintUintS(&current);
        current *= base;
        ++ power;
    }
    printf("\n");
}

void test()
{
    Uint base;

    base = 2;
    _power(base);
    base = 3;
    _power(base);
    base = 4;
    _power(base);
    base = 6;
    _power(base);
    base = 8;
    _power(base);
}

void file_test()
{
    Deck* lines;

    lines = ReadFileAllLines2("file.txt");
    printf("%zu\n", DeckNItems(lines));

    SortDeck(lines, _compare_wrap);
    Deck* unique = DeckUnique(lines, _compare_wrap);

    printf("%zu\n", DeckNItems(unique));

    DeckDestroy(lines);
    DeckDestroy(unique);
}

void string_test()
{
    Uint base, exp;
    Deck* strings;
    Deck* unique;
    Byte* string;

    strings = DeckCreatePtr(NULL, NULL);

    base = 2;
    while (base <= N)
    {
        exp = 2;
        while (exp <= N)
        {
            string = _prime_string_create(base);
            _string_power(string, exp);
            DeckPushBack(strings, &string);
            WhySavePtr(&string);

            ++ exp;
        }
        ++ base;
    }

    printf("%zu\n", DeckNItems(strings));

    unique = DeckUnique(strings, _compare_wrap);
    printf("%zu\n", DeckNItems(unique));

    DeckDestroy(strings);
    DeckDestroy(unique);
}

int main()
{
    HashTable*  strings;
    Uint        n_items;

    WhyStart();
    test();
    // file_test();
    // string_test();
    // _natural_test();

    // strings = HashTableCreate(LENGTH, NULL, NULL, _hash_wrap);
    // _generate_strings(strings);
    // n_items = HashTableNItems(strings);

    // PrintUintN(&n_items);
    // HashTableDestroy(strings);

    WhyEnd();

    return EXIT_SUCCESS;
}