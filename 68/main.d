module main;

import std.container;
import std.stdio;
import std.algorithm;
import std.range;
import std.format;
import std.array;
import std.conv;
import std.parallelism;

import euler_lib;

ulong count_nodes(ulong n_sides)
{
    return 2 * n_sides;
}

class MagicNGon(ulong N)
{
    int[]               values;
    RedBlackTree!int    unused_values;
    ulong               n_sides;

    this(int[] pivot_values...)
    {
        ulong n_nodes;

        n_nodes = count_nodes(N);
        unused_values = new RedBlackTree!int(iota(1, to!int(n_nodes) + 1));
        unused_values.removeKey(pivot_values);
        values.length = n_nodes;
        values[0 .. pivot_values.length] = pivot_values;
        n_sides = N;
    }

    private ulong _right_index(ulong index) const pure
    {
        return (index + 1) % n_sides + n_sides;
    }

    private ulong _left_index(ulong index) const pure
    {
        return index - n_sides;
    }

    int[] get_row(ulong n) const pure
    {
        n += n_sides;

        return [values[_left_index(n)], values[n], values[_right_index(n)]];
    }

    private bool _check_condition(ulong index, int value, int target) const pure
    {
        int[] row;

        if (index == n_sides)
            return true;
        
        row = get_row((index - 1) % n_sides);
        row[2] = value;

        if (sum(row) != target)
            return false;
        
        row = get_row(index % n_sides);
        row[1] = value;

        if (index + 1 == n_sides * 2)
            return sum(row) == target;

        return sum(row) < target;
    }

    private bool _solve(ulong index, int target)
    {
        int[] to_consider;

        if (index == 2 * n_sides)
            return true;
        
        to_consider = unused_values.array;
        foreach (value; to_consider)
        {
            if (_check_condition(index, value, target))
            {
                unused_values.removeKey(value);
                values[index] = value;

                // writeln(this);
                // writeln(unused_values);

                if (_solve(index + 1, target))
                    return true;
                
                unused_values.insert(value);
                values[index] = 0;
            }
        }

        return false;
    }

    bool solve(int target)
    {
        return _solve(n_sides, target);
    }

    void clear()
    {
        foreach (index; iota(n_sides, 2 * n_sides))
        {
            unused_values.insert(values[index]);
            values[index] = 0;
        }
    }

    override string toString() const
    {
        ulong   index;
        string  result;
        int[]   row;

        index = 0;
        while (index < n_sides)
        {
            row = get_row(index);
            result ~= to!string(row);
            ++ index;
        }

        return result;
    }
}

void test3()
{
    auto permutations = get_all_choices!int(iota(1, 7).array, 3);
    foreach (perm; permutations)
    {
        foreach (target; iota(9, 13))
        {
            auto n_gon = new MagicNGon!(3)(to!(int[])(perm));
            if (n_gon.solve(target))
            {
                writeln(n_gon);
            }
        }
    }
}

void test5()
{
    MagicNGon!5 n_gon;
    auto permutations = get_all_choices!int(iota(1, 11).array, 5);
    foreach (perm; permutations)
    {
        foreach (target; iota(15, 21))
        {
            n_gon = new MagicNGon!5(perm);
            if (n_gon.solve(target))
            {
                writeln(n_gon);
            }
        }
    }
}

void main()
{
    // test3();
    test5();

}
