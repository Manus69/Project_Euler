module main;

import std.stdio;
import std.parallelism;
import std.conv;
import std.parallelism;
import std.range;

import euler_lib;

// enum N = 9;
enum N = 1000_000;
enum START = N / 2;
enum TOP = 428_571;
enum BOT = 1000_000;

Rational!long find_fraction(long bot, double limit)
{
    long top;
    double value;

    top = (bot * TOP) / BOT;

    while (true)
    {
        value = to!double(top + 1) / bot;

        if (value >= limit)
            return new Rational!long(top, bot);
        
        ++ top;
    }
}

Rational!long find_max()
{
    Rational!long   max;
    Rational!long   current;
    double          limit;

    max = new Rational!long(0, 1);
    limit = new Rational!long(3, 7).value;

    foreach (bot; START .. N)
    // foreach (bot; parallel(iota(3, N)))
    {
        current = find_fraction(bot, limit);
        if (current > max)
            max = current;
    }

    return max;
}

void main()
{
    auto max = find_max();

    writeln(max);
}