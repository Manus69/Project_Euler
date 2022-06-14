module main;

import std.stdio;
import std.algorithm;
import std.array;
import std.format;
import std.conv;
import std.parallelism;
import std.range;

import euler_lib;

enum N = 10_000_000;
// enum N = 100;

char[] count_digits(ulong n, char[] digits)
{
    if (n == 0)
    {
        digits[0] = 1;

        return digits;
    }

    while (n)
    {
        ++ digits[n % 10];
        n /= 10;
    }

    return digits;
}

bool is_permutation(ulong lhs, ulong rhs)
{
    char[10] lhs_digits;
    char[10] rhs_digits;

    return count_digits(lhs, lhs_digits) == count_digits(rhs, rhs_digits);
}

ulong find_n(const ulong[] phi)
{
    ulong   min_index;
    double  min;
    double  current;

    min = double.max;
    min_index = 1;

    foreach (n; parallel(iota(2, phi.length)))
    {
        if (is_permutation(n, phi[n]))
        {
            current = to!double(n) / phi[n];
            if (current < min)
            {
                min = current;
                min_index = n;
            }
        }
    }

    return min_index;
}

void main()
{
    ulong[] phi;
    ulong   index;
    
    phi = get_phi_values(N);
    index = find_n(phi);

    writeln(index);
}
