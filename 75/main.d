module main;

import std.stdio;
import std.conv;
import std.format;
import std.container;
import std.algorithm;
import std.range;
import std.array;
import std.parallelism;
import std.exception;
import std.math;

import euler_lib;

enum N = 1500_001;
// enum N = 121;
uint[N] TRIPLE_COUNTS;
bool[Triple] TRIPLES_SEEN;

class Triple
{
    long a;
    long b;
    long c;

    this(long[] values...)
    {
        if (values[0] > values[1])
            swap(values[0], values[1]);
        
        a = values[0];
        b = values[1];
        c = values[2];
    }

    private ulong _perimeter() const pure @property
    {
        return a + b + c;
    }

    override bool opEquals(Object rhs) const pure
    {
        Triple _rhs = cast(Triple)rhs;

        return a == _rhs.a && b == _rhs.b;
    }

    override ulong toHash() const pure
    {
        return a + b + c;
    }

    ulong toHashClass() const pure
    {
        return a + b + c;
    }

    override int opCmp(Object rhs) const
    {
        Triple _rhs = cast(Triple)rhs;

        if (this == _rhs)
            return 0;
        
        return a < _rhs.a ? -1 : a > _rhs.a;
    }

    override string toString() const
    {
        return format("[%s %s %s]", a, b, c);
    }
}

void count_triples(ulong u, ulong v, ulong limit)
{
    Triple triple;
    ulong perimeter, p0;
    ulong a, a0;
    ulong b, b0;
    
    a0 = v * v - u * u;
    b0 = 2 * u * v;
    p0 = a0 + b0 + u * u + v * v;

    a = a0;
    b = b0;
    perimeter = p0;

    while (perimeter < limit)
    {
        triple = new Triple(a, b, perimeter - a - b);

        if (triple !in TRIPLES_SEEN)
        {            
            ++ TRIPLE_COUNTS[perimeter];
            TRIPLES_SEEN[triple] = true;
        }

        perimeter += p0;
        a += a0;
        b += b0;
    }
}

void count_all_triples(ulong limit)
{
    foreach (v; 2 .. to!ulong(sqrt(to!double(limit))))
    {
        foreach (u; 1 .. v)
        {
            // writeln(v * v - u * u + 2 * u * v + v * v + u * u);
            if (2 * (v * v + u * u) > limit)
                break ;

            if (gcd(v, u) == 1)
                count_triples(u, v, limit);
        }
    }
}

void main()
{
    count_all_triples(N);
    // writeln(TRIPLE_COUNTS[0 .. $]);
    writeln(count!("a == 1")(TRIPLE_COUNTS.array));
}
