#include "why.h"

#include <stdio.h>
#include <stdlib.h>

#define N_DAYS (365 * 200)

typedef enum    MONTH
{
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, LAST,
}               MONTH;

static Uint DAYS_IN_MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static Uint YEARS[N_DAYS];

static bool _is_leap(Uint year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100));
}

static Uint _compute_days_in_month(Uint month, bool leap)
{
    if ((month == FEB) && leap)
        return DAYS_IN_MONTH[FEB] + 1;
    
    return DAYS_IN_MONTH[month];
}

static void _month_set(Uint* years, Uint value, Uint n_values)
{
    while (n_values)
    {
        *years = value;
        ++ years;
        -- n_values;
    }
}

static Uint _compute_months_for_year(Uint* years, Uint year)
{
    Uint*   start;
    Uint    current_month;
    Uint    days_in_month;
    bool    is_leap;

    start = years;
    is_leap = _is_leap(year);
    current_month = JAN;

    while (current_month < LAST)
    {
        days_in_month = _compute_days_in_month(current_month, is_leap);
        _month_set(years, current_month, days_in_month);
        ++ current_month;
        years += days_in_month;
    }

    return years - start;
}

static void _compute_all_months(Uint* years, Uint start_year, Uint end_year)
{
    while (start_year <= end_year)
    {
        years += _compute_months_for_year(years, start_year);
        ++ start_year;
    }
}

static Uint _count_sundays(Uint* years)
{
    Uint sunday;
    Uint sum;
    Uint month;

    sunday = 5;
    sum = 0;

    while (true)
    {
        sunday += 7;
        
        if (years[sunday] == 0)
            return sum;

        month = years[sunday];
        if (month != years[sunday - 1])
        {
            ++ sum;
            // printf("day: %zu, month: %zu\n", sunday, years[sunday]);
        }
    }
}

int main()
{
    Uint sum;

    _compute_all_months(YEARS, 1901, 2000);
    sum = _count_sundays(YEARS);
    PrintUintN(&sum);

    return EXIT_SUCCESS;
}