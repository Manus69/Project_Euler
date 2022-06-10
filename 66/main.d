module main;

import std.stdio;
import std.math;
import std.conv;
import std.bigint;
import std.format;
import std.range;
import std.parallelism;
import std.array;

import euler_lib;
import rational;

enum LIMIT = 100;

bool is_square(long n)
{
    real _sqrt;

    _sqrt = sqrt(to!real(n));

    return isClose(_sqrt, floor(_sqrt));
}

Rational!BigInt solve(ulong D)
{
    ulong[]         sequence;
    Rational!BigInt r;
    ulong           n;

    sequence = number_to_canonical_sequence(D, LIMIT);
    n = 1;
    while (n < LIMIT)
    {
        r = sequence_to_rational!BigInt(sequence[0 .. n], 1);

        if (r._top * r._top == 1 + D * r._bot * r._bot)
            return r;
        
        ++ n;
    }

    return null;
}

Rational!BigInt[] solve_all(ulong limit)
{
    Rational!BigInt[]   solutions;
    ulong[] values;

    values = iota(2, limit).array;
    foreach (D; values)
    {
        if (!is_square(D))
        {
            solutions ~= solve(D);
        }
        else
        {
            solutions ~= null;
        }
    }

    return solutions;
}

ulong find_max_index(Rational!BigInt[] values)
{
    Rational!BigInt max;
    ulong index_max;
    ulong n;

    max = values[0];
    index_max = 0;

    while (n < values.length)
    {
        if (values[n] && values[n]._top > max._top)
        {
            max = values[n];
            index_max = n;
        }

        ++ n;
    }

    return index_max;
}

void main()
{
    Rational!BigInt[] solutions;
    ulong index;

    solutions = solve_all(1000);

    index = find_max_index(solutions);
    writeln(index + 2);
}