#include "why.h"

#include <stdio.h>

static Uint _spiral_positive(Int x, Int y)
{
    if (x == y)
        return (2 * x + 1) * (2 * x + 1);

    if (y > x)
        return _spiral_positive(x + 1, y) - 1;
    
    if (x == y + 1)
        return _spiral_positive(x - 1, y) + 1;
    
    if (x > y)
        return _spiral_positive(x, y + 1) + 1;

    return 0;
}

static Uint _spiral(Int x, Int y)
{
    if (x >= 0 && y >= 0)
        return _spiral_positive(x, y);
    
    if (x == 0 && y < 0)
        return _spiral_positive(0, -y) + 4 * y;
     
    if (x < 0 && y == 0)
        return -x * 4 + _spiral_positive(-x, 0);

    if (x > 0 && y < 0)
    {
        if (x >= -y)
            return _spiral(x, y + 1) + 1;
        
        return _spiral(x - 1, y) - 1;
    }
    
    if (x < 0 && y > 0)
    {
        if (-x >= y)
            return _spiral(x, y - 1) + 1;
        
        return _spiral(x - 1, y) + 1;
    }
    
    if (x < 0 && y < 0)
    {
        if (-x < -y)
            return _spiral(x + 1, y) + 1;
        
        return _spiral(x, y + 1) - 1;
    }
    
    return 0;
}

static void _print_spiral(Uint radius)
{
    Int x, y;
    Uint value;

    x = -radius;
    while (x <= (Int)radius)
    {
        y = -radius;
        while (y <= (Int)radius)
        {
            value = _spiral(y, x);
            PrintUintS(&value);

            ++ y;
        }
        printf("\n");

        ++ x;
    }
}

static Uint _radius_to_side(Uint radius)
{
    return radius * 2 + 1;
}

static Uint _find_side(Float target_ratio)
{
    Uint radius;
    Uint n_primes;
    Uint number;
    Float ratio;

    radius = 1;
    n_primes = 0;

    while (true)
    {   
        number = _spiral(radius, -radius);
        if (MathIsPrime(number))
            ++ n_primes;
        
        number = _spiral(-radius, -radius);
        if (MathIsPrime(number))
            ++ n_primes;
        
        number = _spiral(-radius, radius);
        if (MathIsPrime(number))
            ++ n_primes;

        ratio = ((Float)n_primes) / (4 * radius + 1);

        if (ratio <= target_ratio)
            break ;

        ++ radius;
    }

    return _radius_to_side(radius);
}

int main()
{
    // WhyStart();
    MathUnitInit(1000000);

    Uint side = _find_side(0.10);
    PrintUintN(&side);

    MathUnitTerminate();
    // WhyEnd();

    return 0;
}