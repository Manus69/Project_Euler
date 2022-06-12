module main;

import std.container;
import std.stdio;
import std.algorithm;
import std.range;
import std.format;
import std.array;

import euler_lib;


void main()
{
    string[] array = ["ass", "cock", "fag"];
    string[][] perms = get_all_choices!string(array, 2);
    writeln(perms);
}
