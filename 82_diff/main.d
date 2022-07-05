module main;

import std.stdio;
import std.conv;
import std.format;
import std.array;
import std.string;
import std.algorithm;

import euler_lib;

enum N = 80;
enum string FILE = "p082_matrix.txt";
enum string[] TEST =   ["131, 673, 234, 103, 18",
                        "201, 96, 342, 965, 150",
                        "630, 803, 746, 422, 111",
                        "537, 699, 497, 121, 956",
                        "805, 732, 524, 37, 331"];

enum string[] MINI_TEST = ["121, 956",
                            "37, 331"];

class Matrix(ulong N)
{
    ulong[N][N]     values;
    ulong[][N][N]   paths;
    bool[N][N]      visited_from_above;
    bool[N][N]      visited_from_below;

    this(string[] lines)
    {
        string[] str_values;

        foreach (n; 0 .. N)
        {
            str_values = lines[n].split(',');
            foreach (m; 0 .. N)
            {
                values[n][m] = to!ulong(strip(str_values[m]));
            }
        }
    }

    private void _clear()
    {
        foreach (n; 0 .. N)
        {
            visited_from_above[n][] = false;
            visited_from_below[n][] = false;
            paths[n][] = null;
        }
    }

    private bool _last_row_col(ulong row_col) const pure nothrow
    {
        return row_col == N - 1;
    }

    private bool _first_row_col(ulong row_col) const pure nothrow
    {
        return row_col == 0;
    }

    private ulong _path_sum(const ulong[] path) const 
    {
        return sum(path);
    }

    override string toString() const
    {
        string result;

        foreach (row; values)
        {
            result ~= format("%4s\n", row);
        }

        return result;
    }

    private ulong[] _max_path(ulong[][] paths...) const pure
    {
        long index;

        index = maxIndex!((p, q) => _path_sum(p) < _path_sum(q))(paths);

        return paths[index];
    }

    private ulong[] _min_path(ulong[][] paths...) const pure
    {
        ulong   min;
        ulong   current;
        ulong[] min_path;

        min = ulong.max;
        foreach (path; paths)
        {
            current = sum(path);
            if (current > 0 && current < min)
            {
                min = current;
                min_path = path;
            }
        }

        return min_path;
    }

    private ulong[] _get_up_path(ulong row, ulong col)
    {
        if (_first_row_col(row))
            return [];
        
        if (_first_row_col(col))
            return [];

        if (visited_from_below[row - 1][col])
            return [];

        return values[row][col] ~ _find_path(row - 1, col, row);
    }

    private ulong[] _get_right_path(ulong row, ulong col)
    {
        return values[row][col] ~ _find_path(row, col + 1, row);
    }

    private ulong[] _get_down_path(ulong row, ulong col)
    {
        if (_last_row_col(row))
            return [];

        if (_first_row_col(col))
            return [];

        if (visited_from_above[row + 1][col])
            return [];

        return values[row][col] ~ _find_path(row + 1, col, row);
    }

    private ulong[] _find_path(ulong row, ulong col, ulong prev_row)
    {
        ulong[] up_path;
        ulong[] down_path;
        ulong[] right_path;
        ulong[] path;

        // writeln("cell: ", values[row][col], " ", row, " ", col);

        if (_last_row_col(col))
            return [values[row][col]];

        if (paths[row][col] !is null)
            return paths[row][col];
        
        if ((prev_row != ulong.max) && (prev_row < row))
            visited_from_above[row][col] = true;
        
        if ((prev_row != ulong.max) && (prev_row > row))
            visited_from_below[row][col] = true;
        
        up_path = _get_up_path(row, col);
        right_path = _get_right_path(row, col);
        down_path = _get_down_path(row, col);

        path = _min_path(up_path, right_path, down_path);   
        paths[row][col] = path;

        // writefln("cell: %s\nup: %s\nright: %s\ndown: %s\nmin: %s\n",
        //         values[row][col], up_path, right_path, down_path, path);

        return path;
    }

    ulong[] find_path()
    {
        ulong[][N] _paths;

        foreach (n; 0 .. N)
        {
            _paths[n] = _find_path(n, 0, ulong.max);
            // writeln(_paths[n]);
            // _clear();
        }

        return _min_path(_paths);
    }
}

void main()
{
    string[] lines;
    Matrix!N m;

    lines = read_file_by_line(FILE);
    m = new Matrix!N(lines);
    // Matrix!5 m = new Matrix!5(TEST);
    // Matrix!2 m = new Matrix!2(MINI_TEST);

    auto path = m.find_path();
    writeln(sum(path));
    // writeln(path);
}