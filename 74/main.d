module main;

import std.stdio;
import std.range;
import std.container;
import std.math;
import std.algorithm;

enum LENGTH = 60;
enum LIMIT = 1000_000;

static ulong[]  FACTORIAL = [1, 1, 2, 6, 24, 120, 720, 5040, 40_320, 362_880];
ulong[LIMIT]    CHAINS;

ulong compute_factorial_sum(ulong n)
{
    ulong result;

    if (n == 0)
        return 1;
    
    while (n)
    {
        result += FACTORIAL[n % 10];
        n /= 10;
    }

    return result;
}

ulong compute_chain_length(ulong n)
{
    ulong               next;
    RedBlackTree!ulong  numbers;

    if (CHAINS[n])
        return CHAINS[n];

    numbers = new RedBlackTree!ulong(n);
    next = n;

    while (true)
    {
        next = compute_factorial_sum(next);
        if (next in numbers)
        {
            CHAINS[n] = numbers.length;

            return CHAINS[n];
        }

        if (next < LIMIT && CHAINS[next])
        {
            CHAINS[n] = numbers.length + CHAINS[next];

            return CHAINS[n];
        }
        
        numbers.insert(next);
    }
}

void main()
{
    auto x = count!((n, length) => compute_chain_length(n) == length)(iota(1, LIMIT), LENGTH);
    writeln(x);
}