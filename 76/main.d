module main;

import std.stdio;
import std.container;
import std.conv;
import std.range;
import std.typecons;
import std.format;
import std.algorithm;

// enum N = 6;
enum N = 100;

int[Counter] COUNTERS;

class Counter
{
    RedBlackTree!int    numbers;
    int                 n;

    this(int n, RedBlackTree!int numbers)
    {
        int[] keys;

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

private int _count_ways(Counter counter)
{
    RedBlackTree!int    left_set;
    RedBlackTree!int    right_set;
    int                 current;
    int                 left;
    int                 right;

    if (counter.n < 0 || (counter.n > 0 && counter.numbers.empty))
        return 0;
    
    if (counter.n == 0)
        return 1;
    
    // writefln("Counter: %s", counter);

    if (counter in COUNTERS)
    {
        return COUNTERS[counter];
    }
    
    left_set = counter.numbers.dup;
    right_set = counter.numbers.dup;

    current = right_set.removeAny();
    left_set.removeKey(counter.n);

    left = _count_ways(new Counter(counter.n - current, left_set));
    right = _count_ways(new Counter(counter.n, right_set));

    COUNTERS[counter] = left + right;

    return left + right;
}

int count_ways(int n)
{
    Counter counter;

    counter = new Counter(n, new RedBlackTree!int(iota(1, n + 1)));

    return _count_ways(counter);
}

void main()
{
    int x = count_ways(100);

    writeln(x - 1);
}