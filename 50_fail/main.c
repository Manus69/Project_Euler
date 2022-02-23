#include "why.h"

#include <stdio.h>
#include <limits.h>

#define N (1000000UL)
#define MIN_SEQUENCE_LENGTH (20)
#define MAX_TERM_VALUE (100000UL)

static Uint _roll_hash(const Deck* primes, Uint hash, Uint index, Uint length)
{
    Uint lhs, rhs;

    lhs = *(Uint *)DeckPointAt(primes, index);
    rhs = *(Uint *)DeckPointAt(primes, index + length + 1);

    hash = hash + rhs - lhs;

    return hash;
}

static Uint _reduce_hash(const Deck* primes, Uint hash, Uint length)
{
    Uint rhs;

    rhs = *(Uint *)DeckPointAt(primes, length - 1);

    return hash - rhs;
}

static Uint _compute_hash(const Deck* primes, Uint length)
{
    Uint n;
    Uint p;
    Uint hash;

    hash = 0;
    n = 0;
    while (n < length)
    {
        p = *(Uint *)DeckPointAt(primes, n);
        hash += p;

        ++ n;
    }

    return hash;
}

static Uint _check_all_frames(const Deck* primes, Uint length, Uint max_value)
{
    Uint hash;
    Uint index;

    hash = _compute_hash(primes, length);

    if (hash > N)
        return 0;
    
    index = 0;
    while (true)
    {
        if (MathIsPrime(hash))
            return hash;
        
        hash = _roll_hash(primes, hash, index, length);

        if (hash >= max_value)
            return 0;
    }
}

static Uint _get_starting_length(const Deck* primes, Uint max_value)
{
    Uint index;
    Uint value;

    index = DeckNItems(primes) / 2;

    while (true)
    {
        value = *(Uint *)DeckPointAt(primes, index);
        if (value < max_value)
            return index * 2;
        
        index /= 2;
    }
}

static Uint _find_sequence(const Deck* primes, Uint max_value)
{
    Uint length;
    Uint result;

    length = _get_starting_length(primes, max_value);

    while (length > MIN_SEQUENCE_LENGTH)
    {
        result = _check_all_frames(primes, length, max_value);

        if (result)
            return result;
        
        -- length;
    }

    return 0;
}

int main()
{
    WhyStart();
    MathUnitInit(N);

    Deck* primes;
    Uint result;

    primes = MathGetPrimesUpToN(N);
    result = _find_sequence(primes, 100);
    PrintUintN(&result);

    DeckDestroy(primes);
    MathUnitTerminate();
    WhyEnd();

    return 0;
}