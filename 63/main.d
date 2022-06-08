import std.stdio;
import std.math;
import std.conv;
import std.range;
import std.array;

enum MAX_BASE = 10;
enum MAX_POWER = 30;

const ulong[] BASES = iota(1, MAX_BASE, 1).array;
const ulong[] POWERS = iota(1, MAX_POWER, 1).array;

ulong n_digits(ulong base, ulong power)
{
    return to!ulong(log10(base) * power) + 1;
}

void main()
{
    ulong count;

    foreach (base; BASES)
    {
        foreach (power; POWERS)
        {
            if (n_digits(base, power) == power)
                ++ count;
        }
    }

    writeln(count);
}