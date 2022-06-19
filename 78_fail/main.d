module main;

import std.stdio;
import std.container;
import std.conv;
import std.range;
import std.typecons;
import std.format;
import std.algorithm;
import std.bigint;

enum BigInt MOD_B = BigInt(1_000_000);
enum MOD = 1_000_000;
// enum N = 6;
enum N = 1000;

// BigInt[Counter] COUNTERS;
int[Counter!int] COUNTERS;

class Counter(T)
{
    RedBlackTree!T  numbers;
    T               n;

    this(T n, RedBlackTree!T numbers)
    {
        T[] keys;

        this.n = n;
        this.numbers = numbers;

        foreach (number; this.numbers)
        {
            if (number > n)
                keys ~= number;
        }

        this.numbers.removeKey(keys);
    }

    override bool opEquals(Object obj) const
    {
        Counter c = cast(Counter)obj;
        return this.n == c.n && this.numbers == c.numbers;
    }

    override ulong toHash()
    {
        return n + numbers.toHash();
    }
    
    override string toString() const
    {
        return format("%s %s", n, numbers);
    }
}

private T _count_ways(T)(Counter!T counter)
{
    RedBlackTree!T    left_set;
    RedBlackTree!T    right_set;
    T                 current;
    T                 left;
    T                 right;

    if (counter.n < 0 || (counter.n > 0 && counter.numbers.empty))
        return T(0);
    
    if (counter.n == 0)
        return T(1);
    
    // writefln("Counter: %s", counter);

    if (counter in COUNTERS)
    {
        return COUNTERS[counter];
    }
    
    left_set = counter.numbers.dup;
    right_set = counter.numbers.dup;

    current = right_set.removeAny();
    left_set.removeKey!T(counter.n);

    left = _count_ways(new Counter!T(counter.n - current, left_set));
    right = 2 * current > counter.n ? T(0) :
                _count_ways(new Counter!T(counter.n, right_set));

    COUNTERS[counter] = (left + right) % MOD;

    return (left + right) % MOD;
}

T count_ways(T)(int n)
{
    Counter!T       counter;
    RedBlackTree!T  set;

    set = new RedBlackTree!T();
    foreach (number; 1 .. n)
    {
        set.insert(T(number));
    }

    counter = new Counter!T(T(n), set);

    return _count_ways!T(counter);
}

void main()
{
    int n_ways;

    foreach (n; 2 .. N)
    {
        n_ways = count_ways!int(n);
        writeln(n, " ", n_ways);
        writeln(COUNTERS.length);
        // if ((n_ways % MOD) == 0)
        // {
        //     writeln(n);
        //     break ;
        // }
    }
    
}