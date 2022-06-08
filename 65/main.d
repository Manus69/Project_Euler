module main;

import std.stdio;
import std.exception;
import std.bigint;
import std.conv;
import std.algorithm;

import euler_lib;
import rational;

ulong[] generate_sequence(ulong length)
{
    ulong[] sequence;
    ulong   current;

    current = 1;
    sequence = [2, 1, 2];
    while (sequence.length < length)
    {
        if (current % 3 == 0)
            sequence ~= ((current / 3) + 1) * 2;
        else
            sequence ~= 1;
        ++ current;
    }

    return sequence;
}

Rational!BigInt sequence_to_rational(const ulong[] sequence)
{
    Rational!BigInt lhs;
    Rational!BigInt rhs;

    enforce(sequence.length);

    if (sequence.length == 1)
        return new Rational!BigInt(BigInt(sequence[0]), BigInt(1));
    
    lhs = new Rational!BigInt(BigInt(sequence[0]), BigInt(1));
    rhs = sequence_to_rational(sequence[1 .. $]).invert();

    return lhs + rhs;
}

ulong sum_digits(const string number_string)
{
    return number_string.fold!((a, b) => a + b)(0) - number_string.length * '0';
}

void main()
{
    ulong[]         sequence;    
    Rational!BigInt result;
    string          str;
    
    sequence = generate_sequence(100);
    // writeln(seq);

    result = sequence_to_rational(sequence);
    str = result._top.toDecimalString();
    writeln(str);
    writeln(sum_digits(str));
}

