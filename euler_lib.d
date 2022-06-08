module euler_lib;

import std.conv;

T abs(T)(T value)
{
    return value < 0 ? -value : value;
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