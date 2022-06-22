module main;

import std.stdio;
import std.conv;
import std.format;
import std.array;
import std.string;
import std.algorithm;

import euler_lib;

enum string FILE = "p081_matrix.txt";
enum string[] TEST =   ["131, 673, 234, 103, 18",
                        "201, 96, 342, 965, 150",
                        "630, 803, 746, 422, 111",
                        "537, 699, 497, 121, 956",
                        "805, 732, 524, 37, 331"];

class Matrix(ulong N)
{
    ulong[N][N] values;
    ulong[][N][N] paths;

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

    private bool _last_row_col(ulong row_col) const pure nothrow @property
    {
        return row_col == N - 1;
    }

    private ulong _path_sum(const ulong[] path) const 
    {
        return sum(path);
    }

    private ulong[] _find_path(ulong row, ulong col)
    {
        ulong[] down_path;
        ulong[] right_path;
        ulong[] path;

        if (_last_row_col(row) && _last_row_col(col))
            return [values[row][col]];
        
        if (paths[row][col] !is null)
            return paths[row][col];

        if (_last_row_col(row))
        {
            return values[row][col] ~ _find_path(row, col + 1);
        }

        if (_last_row_col(col))
        {
            return values[row][col] ~ _find_path(row + 1, col);
        }

        down_path = _find_path(row + 1, col);
        right_path = _find_path(row, col + 1);

        path = _path_sum(down_path) < _path_sum(right_path) ?
                values[row][col] ~ down_path : values[row][col] ~ right_path;

        paths[row][col] = path;

        return path;

    }

    ulong[] find_path()
    {
        return _find_path(0, 0);
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
}

void main()
{
    string[] lines;

    lines = read_file_by_line(FILE);
    Matrix!80 m = new Matrix!80(lines);
    writeln(sum(m.find_path()));


}