module main;

import std.stdio;
import std.conv;
import std.range;
import std.parallelism;

import euler_lib;

enum N = 12_000;
// enum N = 8;

ulong count_fractions_in_range(const Rational!long left, const Rational!long right, long bot)
{
    long    top;
    real    limit;
    real    current;
    ulong   count;

    top = (left._top * bot) / left._bot;
    limit = right.value();

    while (to!real(top) / bot < left.value)
        ++ top;

    while (true)
    {
        current = to!real(top) / bot;

        if (current > limit)
        {
            // writeln(bot, " ", count);
            return count;
        }
        
        if (gcd(top, bot) == 1)
            ++ count;
        
        ++ top;
    }
}

ulong count_all_fractions()
{
    ulong           count;
    Rational!long   left;
    Rational!long   right;

    left = new Rational!long(1, 3);
    right = new Rational!long(1, 2);

    foreach (bot; 5 .. N + 1)
    {
        count += count_fractions_in_range(left, right, bot);
    }

    return count;
}

void main()
{
    writeln(count_all_fractions());
}