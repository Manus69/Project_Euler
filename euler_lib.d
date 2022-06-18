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
import std.algorithm;
import std.math;
import std.typecons;

private bool[] SIEVE = null;
private ulong[] PRIMES = null;

class Rational(T)
{
    T _top;
    T _bot;

    this(T top, T bot)
    {
        T d;

        enforce(bot != 0);
        if (bot < 0)
        {
            top = -top;
            bot = -bot;
        }

        d = gcdT!T(top, bot);
        _top = top / d;
        _bot = bot / d;
    }

    private Rational _add(const Rational rhs) const
    {
        T _lcm;

        _lcm = lcmT(_bot, rhs._bot);

        return new Rational((_lcm / _bot) * _top + (_lcm / rhs._bot) * rhs._top, _lcm); 
    }

    private Rational _mult(const Rational rhs) const
    {
        return new Rational(_top * rhs._top, _bot * rhs._bot);
    }

    private Rational _div(const Rational rhs) const
    {
        return new Rational(_top * rhs._bot, _bot * rhs._top);
    }

    Rational opBinary(string op)(const Rational rhs) const
    {
        static if (op == "+")
            return this._add(rhs);
        else static if (op == "*")
            return this._mult(rhs);
        else static if (op == "/")
            return this._div(rhs);
        else static assert (0);
    }

    private T _common_denom(const Rational rhs) const pure
    {
        return lcmT!T(_bot, rhs._bot);   
    }

    int opCmp(const Rational rhs) const
    {
        T left;
        T right;
        T denom;

        denom = _common_denom(rhs);
        left = (denom / _bot) * _top;
        right = (denom / rhs._bot) * rhs._top;

        return left < right ? -1 : left > right;
    }

    Rational invert() const
    {   
        return new Rational(_bot, _top);
    }

    Rational scale(T value) const
    {
        return new Rational(_top * value, _bot);
    }

    double value() const pure @property
    {
        return to!double(_top) / to!double(_bot);
    }

    override string toString() const
    {
        return format("%s / %s", _top, _bot);
    }
}

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

ulong factorial(ulong n)
{
    ulong product;

    product = 1;
    foreach (v; 1 .. n + 1)
    {
        product *= v;
    }

    return product;
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

T[] rotate_array(T)(T[] array, ulong amount)
{
    T[] copy;

    amount = amount % array.length;

    if (!amount || array.length < 2)
        return array.dup;

    copy = array[$ - amount .. $] ~ array[0 .. $ - amount];

    return copy;  
}

long get_next_prime(const bool[] sieve, long n) pure
{
    ++ n;
    while (n < sieve.length && sieve[n] == false)
        ++ n;

    return n == sieve.length ? -1 : n;
}

bool[] get_sieve(ulong max)
{
    bool[]  sieve;
    long    n;
    long    index;

    if (SIEVE && SIEVE.length > max)
        return SIEVE;

    ++ max;
    sieve.length = max;
    sieve[] = true;
    sieve[0 .. 1] = false;
    n = 2;
    index = 4;

    while (n > 0)
    {
        while (index < max)
        {
            sieve[index] = false;
            index += n;
        }

        n = get_next_prime(sieve, n);
        index = n + n;
    }

    SIEVE = sieve;

    return sieve;
}

ulong[] get_primes(ulong limit)
{
    ulong   n;
    ulong[] primes;

    if (PRIMES && PRIMES[$ - 1] > limit)
    {
        return PRIMES[0 .. countUntil!"a >= b"(PRIMES, limit)];
    }

    if (!SIEVE || SIEVE.length <= limit)
        SIEVE = get_sieve(limit);

    n = 2;
    while (n <= limit)
    {
        if (SIEVE[n])
            primes ~= n;

        ++ n;
    }

    PRIMES = primes;

    return primes;
}

ulong[] get_divisors(ulong n)
{
    ulong[] primes;
    ulong[] divisors;

    primes = get_primes(n);
    if (SIEVE[n])
        return [];
    
    foreach (p; primes)
    {
        if (n == 0)
            return divisors;
        
        while (n % p == 0)
        {
            divisors ~= p;
            n /= p;
        }
    }

    return divisors;
}

Tuple!(ulong, ulong)[] get_divisors_powers(ulong n)
{
    ulong[]                 divisors;
    Tuple!(ulong, ulong)[]  result;
    Tuple!(ulong, ulong)    current;

    divisors = get_divisors(n);
    if (divisors.length == 0)
        return null;
    
    current = Tuple!(ulong, ulong)(divisors[0], 1);
    foreach (d; divisors[1 .. $])
    {
        if (d == current[0])
        {
            ++ current[1];
        }
        else
        {
            result ~= current;
            current = Tuple!(ulong, ulong)(d, 1);
        }
    }

    result ~= current;

    return result;
}

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

private ulong _compute_value(ulong n, ulong[] phi)
{
    ulong divisor;
    ulong gcd_value;
    ulong result;

    if (phi[n])
        return phi[n];
    
    if (SIEVE[n])
    {
        phi[n] = n - 1;

        return phi[n];
    }

    divisor = get_divisor(n);
    gcd_value = gcd(divisor, n / divisor);

    result = (_compute_value(divisor, phi) * _compute_value(n / divisor, phi)) * gcd_value;
    result /= _compute_value(gcd_value, phi);

    phi[n] = result;

    return result;
}

ulong[] get_phi_values(ulong limit)
{
    ulong[] phi_values;

    if (!SIEVE || SIEVE.length <= limit)
        SIEVE = get_sieve(limit);

    phi_values.length = limit;
    phi_values[1] = 1;

    foreach (n; 2 .. limit)
    {
        phi_values[n] = _compute_value(n, phi_values);
    }

    return phi_values;
}