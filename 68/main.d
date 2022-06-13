module main;

import std.container;
import std.stdio;
import std.algorithm;
import std.range;
import std.format;
import std.array;
import std.conv;
import std.parallelism;
import std.exception;

import euler_lib;
import magic_ngon;

enum LOW = 1;
enum HIGH = 10;
enum TARGET_LOW = 13;
enum TARGET_HIGH = 2 * HIGH;
enum N = 5;

int[][] filter_out_cycles(int[][] permutations)
{
    int[][]                 no_cycle_array;
    RedBlackTree!(int[])    set;
    int[]                   current;
    int[]                   cycle;
    ulong                   n;

    set = new RedBlackTree!(int[])(permutations);
    while (!set.empty)
    {
        current = set.removeAny();
        no_cycle_array ~= current;
        n = 1;

        while (n < current.length)
        {
            cycle = rotate_array(current, n);
            set.removeKey(cycle);
            ++ n;
        }
    }

    return no_cycle_array;
}

MagicNGon2!N[] get_solutions()
{
    int[][]         permutations;
    MagicNGon2!N    n_gon;
    MagicNGon2!N[]  solutions;

    permutations = get_all_choices(iota(LOW, HIGH + 1).array, N);
    permutations = filter_out_cycles(permutations);

    foreach (perm; permutations)
    {
        foreach (target; iota(TARGET_LOW, TARGET_HIGH))
        {
            n_gon = new MagicNGon2!5(perm);
            if (n_gon.solve(target))
            {
                n_gon.rotate();
                solutions ~= n_gon;   
            }
        }
    }

    return solutions;
}

void main()
{
    auto solutions = get_solutions();
    sort(solutions);
    writeln(solutions[$ - 1]);
}
