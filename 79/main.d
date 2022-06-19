module main;

import std.stdio;
import std.algorithm;
import std.conv;
import std.container;
import std.file;
import std.array;
import std.string;

enum string FILE_NAME = "p079_keylog.txt";

string[] get_lines(const string file_name)
{
    string content;

    content = readText(file_name);

    return content.split();
}

bool check_condition(const string pass_phrase, const string condition)
{
    long left;
    long mid;
    long right;

    left = indexOf(pass_phrase, condition[0]);
    mid = indexOf(pass_phrase, condition[1]);
    right = indexOf(pass_phrase, condition[2]);

    return (left < mid) && (mid < right);
}

void main()
{
    auto x = get_lines(FILE_NAME);
    sort(x);
    writefln("%-(%s\n%)", x);

    writeln(check_condition("12345", "132"));
}