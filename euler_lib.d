module euler_lib;

import std.conv;
import std.bigint;
import std.exception;
import std.math;
import std.stdio;
import std.format;
import std.container;
import std.parallelism;
import std.array;

import rational;

T abs(T)(T value)
{
    return value < 0 ? -value : value;
}

void swap(T)(T[] array, ulong left, ulong right)
{
    T temp;

    temp = array[left];
    array[left] = array[right];
    array[right] = temp;
}

//a = kb + r -> gcd(a, b) = gcd(b, r)
ulong gcd(ulong a, ulong b)
{
    if (b > a)
        return gcd(b, a);
    
    if (b == 0)
        return a;
    
    return gcd(b, a % b);
}

T gcdT(T)(T a, T b)
{
    if (b > a)
        return gcdT(b, a);
    
    if (b == 0)
        return a;
    
    return gcdT(b, a % b);
}

//a * b = gcd(a, b) * lcm(a, b)
ulong lcm(ulong a, ulong b)
{
    return (a * b) / gcd(a, b);
}

T lcmT(T)(T a, T b)
{
    return (a * b) / gcdT(a, b);
}

Rational!T sequence_to_rational(T)(const ulong[] sequence, ulong R)
{
    Rational!T                  lhs;
    Rational!T                  rhs;
    Rational!T                  result;
    static Rational!T[string]   table;
    string                      key;

    enforce(sequence.length);

    if (sequence.length == 1)
        return new Rational!T(T(sequence[0]), T(1));
    
    key = format("%s", sequence);
    if (key in table)
        return table[key];
    
    lhs = new Rational!T(T(sequence[0]), T(1));
    rhs = sequence_to_rational!T(sequence[1 .. $], R).invert();
    result = lhs + rhs.scale(T(R));
    table[key] = result;

    return result;
}

ulong[] decimal_to_sequence(real x, ulong n_terms)
{
    ulong[] sequence;
    ulong   term;

    enforce(x > 0);
    
    while (n_terms)
    {
        term = to!ulong(x);
        sequence ~= term;
        x -= term;

        if (isClose(x, 0, 0.0, 1e-10))
            return sequence;
        
        x = 1 / x;
        -- n_terms;
    }

    return sequence;
}

ulong[] number_to_canonical_sequence(ulong n, ulong n_terms)
{
    ulong   m;
    ulong   d;
    ulong   member;
    ulong[] sequence;

    m = 0;
    d = 1;
    member = to!ulong(sqrt(to!real(n)));
    sequence ~= member;

    while (n_terms)
    {
        m = d * member - m;
        d = (n - m * m) / d;
        member = (sequence[0] + m) / d;
        sequence ~= member;

        -- n_terms;
    }

    return sequence;
}

Rational!T rational_approx(T)(double x, ulong n_terms)
{
    ulong[] sequence;

    sequence = decimal_to_sequence(x, n_terms);

    return sequence_to_rational!T(sequence, 1);
}

Rational!T root_to_fraction(T)(ulong x, ulong n_terms)
{
    ulong[] sequence;

    sequence = number_to_canonical_sequence(x, n_terms);

    return sequence_to_rational!T(sequence, 1);
}

private T[][] _combine(T)(T[][] array, T value)
{
    foreach (ref subarray; array)
    {
        subarray = value ~ subarray;
    }

    return array;
}

T[][] get_all_choices(T)(RedBlackTree!T set, ulong n_items)
{
    T[][]           result;
    T[][]           subresult;
    RedBlackTree!T  copy;

    if (n_items == 1)
    {
        foreach (item; set)
        {
            result ~= [item];
        }

        return result;
    }

    foreach (item; set)
    {
        copy = set.dup;
        copy.removeKey(item);
        subresult = get_all_choices!T(copy, n_items - 1);
        subresult = _combine(subresult, item);
        result ~= subresult;
    }

    return result;
}

T[][] get_all_choices(T)(const T[] array, ulong n_items)
{
    RedBlackTree!T set;

    set = new RedBlackTree!T(array);

    return get_all_choices!T(set, n_items);
}

void rotate_array(T)(T[] array, ulong amount)
{
    ulong n;
    ulong next_index;

    if (array.length == 1)
        return ;
    
    amount = amount % array.length;
    while (n < array.length)
    {
        next_index = (n + amount) % array.length;
        swap(array, n, next_index);

        ++ n;
    }
}
