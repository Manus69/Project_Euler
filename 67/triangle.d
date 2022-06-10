module triangle;

import std.exception;
import std.format;
import std.algorithm;
import std.stdio;

int[][] TEST_TRIANGLE = [[3], [7, 4], [2, 4, 6], [8, 5, 9, 3]];

Triangle test_triangle()
{
    return new Triangle(TEST_TRIANGLE);
}

class Path
{
    int[]   path;
    int     value;

    this(int[] path)
    {
        this.path = path;
        this.value = sum(path);
    }

    this(int[] path, int value)
    {
        this.path = path;
        this.value = value;
    }

    Path extend(int value)
    {
        this.path = value ~ this.path; 
        this.value += value;

        return this;
    }

    Path copy()
    {
        return new Path(this.path, this.value);
    }

    int opCmp(const Path rhs) const
    {
        return this.value < rhs.value ? -1 : this.value > rhs.value;
    }

    override string toString() const
    {
        return format("%s value = %s", this.path, this.value);
    }
}

class Triangle
{
    int[][]     values;
    Path[][]    path_table;

    this(int[][] array)
    {
        values = array;
        path_table.length = array.length;

        foreach (ref row; path_table)
        {
            row.length = array.length;
        }

        // writeln(path_table);
    }

    ulong n_rows() const @property
    {
        return values.length;
    }

    int at(ulong row, ulong col) const 
    {
        enforce(row >= col);

        return values[row][col];
    }

    Path get_path(ulong row, ulong col)
    {
        return path_table[row][col];
    }

    void set_path(Path path, ulong row, ulong col)
    {
        path_table[row][col] = path.copy();
    }

    override string toString() const
    {
        return format("%s", values);
    }
}

Path find_best_path(Triangle triangle, ulong row, ulong col)
{
    Path left;
    Path right;

    if (row + 1 == triangle.n_rows)
        return new Path([triangle.at(row, col)]);
    
    if ((left = triangle.get_path(row, col)) !is null)
        return left;

    left = find_best_path(triangle, row + 1, col);
    right = find_best_path(triangle, row + 1, col + 1);

    if (left > right)
    {
        left.extend(triangle.at(row, col));
        triangle.set_path(left, row, col);

        return left;
    }
    else
    {
        right.extend(triangle.at(row, col));
        triangle.set_path(right, row, col);

        return right;
    }

}