module main;

import std.stdio;
import std.conv;
import std.range;
import std.algorithm;

import euler_lib;

enum N = 1000_000;

void main()
{
    ulong[] phi;

    phi = get_phi_values(N);
    writeln(sum(phi) - 1);
}