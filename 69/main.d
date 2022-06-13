module main;

import std.stdio;
import std.array;
import std.algorithm;

import euler_lib;

void main()
{
    auto s = get_sieve(1_000);
    auto p = get_primes(1_000);
    writeln(p);

    auto d = get_divisors(1000000);
    writeln(d);
}
