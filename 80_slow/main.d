module main;

import std.stdio;
import std.bigint;
import std.range;
import std.conv;
import std.algorithm;
import std.parallelism;
import std.range;

import euler_lib;

enum N = 100;

// Rational!BigInt get_epsilon()
// {
//     char[N] bot;

//     bot[] = '0';
//     bot[0] = '1';

//     return new Rational!BigInt(BigInt(1), BigInt(bot.idup));
// }

ulong sum_digits(const string digit_string)
{
    return sum(digit_string) - digit_string.length * '0';
}

void main()
{
    Rational!BigInt fraction;
    string          current;
    ulong           total;

    foreach (n; 1 .. N)
    {
        if (is_perfect_square(n))
            continue ;

        fraction = root_to_fraction!BigInt(n, 180);
        current = divide!BigInt(fraction._top, fraction._bot, 100);
    
        total += sum_digits(current);
    }

    writeln(total);
}