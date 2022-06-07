module main;

import std.stdio;
import std.bigint;
import std.conv;
import std.math;
import std.exception;
import std.algorithm;
import std.array;

import number;

enum N_DIGITS = 9;
enum N_PERMUTATIONS = 5;

ulong get_starting_value(uint n)
{
    return to!ulong(pow(n, 1.0 / 3)) + 1;
}

Number[] get_all_cubes(uint n_digits)
{
    Number[]    numbers;
    Number      number;
    ulong       current;

    enforce(n_digits > 0);
    current = get_starting_value(pow(10, n_digits - 1));
    while (true)
    {
        number = new Number(current * current * current);
        if (number.n_digits > n_digits)
            return numbers;
        
        numbers ~= number;
        ++ current;
    }
}

Number[] get_permutations(Number[] numbers, const Number number)
{
    return filter!(a => a == number)(numbers).array;
}

ulong count_permutations(Number[] numbers, const Number number)
{
    return get_permutations(numbers, number).length;
}

void main()
{
    Number[]    cubes;
    Number[]    perms;
    uint        n_digits;

    n_digits = N_DIGITS;
    while (true)
    {
        cubes = get_all_cubes(n_digits);
        foreach (cube; cubes)
        {
            perms = get_permutations(cubes, cube);
            if (perms.length == N_PERMUTATIONS)
                return writeln(perms);
        }

        ++ n_digits;
    }

}