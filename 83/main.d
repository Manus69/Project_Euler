module main;

import priority_queue;

import std.algorithm;
import std.stdio;
import std.datetime;

enum string FILE = "p082_matrix.txt";
enum string[] TEST =   ["131, 673, 234, 103, 18",
                        "201, 96, 342, 965, 150",
                        "630, 803, 746, 422, 111",
                        "537, 699, 497, 121, 956",
                        "805, 732, 524, 37, 331"];


void main()
{
    // auto q = new Heap!(string, ">")();
    // auto s = Clock.currTime();
    // foreach (line; File("test.txt").byLineCopy())
    //     q.Insert(line);
    // auto e = Clock.currTime();

    // auto a = q.Sort();
    // writeln(a[$ - 1]);
    // writeln(e - s);

    string[] lines;

    auto s = Clock.currTime();
    foreach (line; File("test.txt").byLineCopy())
        lines ~= line;
    auto e = Clock.currTime();

    sort(lines);
    writeln(lines[$ - 1]);
    writeln(e - s);
}