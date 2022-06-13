module magic_ngon;

import std.array;
import std.format;
import std.container;
import std.range;
import std.conv;
import std.algorithm;

import euler_lib;

ulong count_nodes(ulong n_sides)
{
    return 2 * n_sides;
}

class MagicNGon2(ulong N)
{
    int[] _values;
    ulong _n;

    this(int[] values...)
    {
        _values.length = 2 * N;
        _values[0 .. values.length] = values;
        _n = N;
    }

    private ulong _get_external_index(ulong index) const pure
    {
        return index + _n;
    }

    private ulong _get_right_index(ulong index) const pure
    {
        return (index + 1) % _n;
    }

    private int[] _get_row(ulong index) const pure
    {
        return [_values[_get_external_index(index)],
                _values[index], _values[_get_right_index(index)]];
    }

    private bool _solve(int target, ulong index, RedBlackTree!int used_values)
    {
        int value;

        if (index == _n)
            return true;
        
        value = target - _values[index] - _values[_get_right_index(index)];
        if (value < 1 || value > 2 * _n)
            return false;
        
        if (value in used_values)
            return false;
        
        _values[_get_external_index(index)] = value;
        used_values.insert(value);

        return _solve(target, index + 1, used_values);
    }

    bool solve(int target)
    {
        RedBlackTree!int used_values;

        used_values = new RedBlackTree!int(_values[0 .. _n]);

        return _solve(target, 0, used_values);
    }

    private long _min() const pure
    {
        return minIndex(_values[_n .. $]);
    }

    void rotate()
    {
        long min_index;

        min_index = _min() % _n;
        if (min_index == 0)
            return ;
        
        _values[0 .. _n] = rotate_array(_values[0 .. _n], _n - min_index);
        _values[_n .. $] = rotate_array(_values[_n .. $], _n - min_index);
    }

    int opCmp(const MagicNGon2 rhs) const
    {
        string left;
        string right;

        left = this.toString();
        right = rhs.toString();

        if (left.length < right.length)
            return 1;
        
        return left < right ? -1 : left > right;
    }

    override string toString() const
    {
        string  str;
        ulong   n;

        while (n < _n)
        {
            str ~= format("%(%s%)", _get_row(n));
            ++ n;
        }

        return str;
    }
}