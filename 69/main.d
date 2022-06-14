module main;

import std.stdio;
import std.array;
import std.algorithm;
import std.container;
import std.range;
import std.array;
import std.typecons;
import std.math;
import std.parallelism;
import std.conv;

import euler_lib;

enum long N = 1000_000;
ulong[N + 1] TOTIENT_VALUES;

ulong get_divisor(ulong n)
{
    ulong p;

    p = 2;
    while (p <= n)
    {
        if (n % p == 0)
            return p;
        ++ p;
    }

    return p;
}

ulong compute_value(ulong n, const bool[] sieve)
{
    ulong divisor;
    ulong gcd_value;
    ulong result;

    if (TOTIENT_VALUES[n])
        return TOTIENT_VALUES[n];
    
    if (sieve[n])
    {
        TOTIENT_VALUES[n] = n - 1;

        return TOTIENT_VALUES[n];
    }

    divisor = get_divisor(n);
    gcd_value = gcd(divisor, n / divisor);

    result = (compute_value(divisor, sieve) * compute_value(n / divisor, sieve)) * gcd_value;
    result /= compute_value(gcd_value, sieve);

    TOTIENT_VALUES[n] = result;

    return result;
}

void compute_totient_values2(const bool[] sieve)
{
    foreach (n; 2 .. N + 1)
    {
        compute_value(n, sieve);
    }
}

ulong find_index()
{
    double current;
    double max;
    ulong max_index;
    
    max = 1;
    foreach (index; 2 .. N)
    {
        current = to!double(index) / TOTIENT_VALUES[index];
        if (current > max)
        {
            max = current;
            max_index = index;
        }
    }

    return max_index;
}

void main()
{
    bool[]  sieve;
    ulong   index;
    
    TOTIENT_VALUES[1] = 1;
    sieve = get_sieve(N);
    compute_totient_values2(sieve);

    // writeln(TOTIENT_VALUES[0 .. $]);

    index = find_index();
    writeln(index);
}
