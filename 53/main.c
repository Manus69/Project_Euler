#include "why.h"

#include <stdio.h>

#define _MAX (101)
#define THRESHOLD (1000000)

static Uint TRIANGLE[_MAX + 1][_MAX + 1];

static void _fill(Uint n, Uint triangle[n][n])
{
    Uint j, k;
    Uint lhs, rhs;

    j = 0;
    while (j < n)
    {
        k = 0;
        while (k < n)
        {
            if (k > j)
                triangle[j][k] = 0;
            else if (j == k)
                triangle[j][k] = 1;
            else if (k == 0)
                triangle[j][k] = 1;
            else
            {
                lhs = triangle[j - 1][k - 1];
                rhs = triangle[j - 1][k];

                if (lhs > THRESHOLD || rhs > THRESHOLD)
                    triangle[j][k] = THRESHOLD + 1;
                else   
                    triangle[j][k] = triangle[j - 1][k - 1] + triangle[j - 1][k];
            }
            // PrintUintS(&triangle[j][k]);
            ++ k;
        }
        // printf("\n");
        ++ j;
    }
}

static Uint _count_elements()
{
    Uint j, k;
    Uint count;

    count = 0;
    j = 0;
    while (j <= _MAX)
    {
        k = 0;
        while (k <= _MAX)
        {
            if (TRIANGLE[j][k] > THRESHOLD)
                ++ count;
            
            ++ k;
        }
        ++ j;
    }

    return count;
}

int main()
{
    WhyStart();

    _fill(_MAX, TRIANGLE);

    Uint n = _count_elements();
    PrintUintN(&n);

    WhyEnd();
    return 0;
}