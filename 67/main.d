module main;

import std.stdio;
import std.file;
import std.array;
import std.conv;
import std.ascii;
import std.string;

import triangle;

enum FILE_NAME = "p067_triangle.txt";

string[] read_file(const string file_name)
{
    string      content;
    string[]    lines;

    content = readText(file_name);
    lines = split(content, "\n");

    return lines;
}

int[] line_to_array(const string line)
{
    string[]    str_values;
    int[]       array;

    str_values = split(line);
    foreach (str_value; str_values)
    {
        array ~= to!int(str_value);
    }

    return array;
}

int[][] get_all_values(string[] lines)
{
    int[][] values;

    foreach (line; lines)
    {
        if (line.length)
            values ~= line_to_array(line);
    }

    return values;
}

int[][] get_all_values(const string file_name)
{
    string[] lines;

    lines = read_file(file_name);

    return get_all_values(lines);
}

void main()
{
    Triangle    triangle;
    Path        path;

    triangle = new Triangle(get_all_values(FILE_NAME));
    // writeln(triangle);
    path = find_best_path(triangle, 0, 0);
    writeln(path);
}