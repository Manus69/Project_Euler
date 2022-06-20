module main;

import std.stdio;
import std.algorithm;
import std.conv;
import std.container;
import std.file;
import std.array;
import std.string;
import std.format;

enum string FILE_NAME = "p079_keylog.txt";

class PassDigit
{
    int              digit;
    RedBlackTree!int before;
    RedBlackTree!int after;

    this(int digit, RedBlackTree!int before, RedBlackTree!int after)
    {
        this.digit = digit;
        this.before = before;
        this.after = after;
    }

    override string toString() const
    {
        return format("%s before: %(%c %) after: %(%c %)", cast(char)digit,
                    cast(char [])before.array, cast(char [])after.array);
    }
}

private char[] _get_before(char[] str, ulong index)
{
    if (index == 0)
        return null;
    
    return str[0 .. index];
}

private char[] _get_after(char[] str, ulong index)
{
    if (index == (str.length - 1))
        return null;
    
    return str[index + 1 .. $];
}

PassDigit get_digit_info(char digit, const string[] lines)
{
    RedBlackTree!int    before;
    RedBlackTree!int    after;
    char[]              array;
    long                index;

    before = new RedBlackTree!int();
    after = new RedBlackTree!int();

    foreach (line; lines)
    {
        index = indexOf(line, digit);
        if (index < 0)
            continue ;
        
        array = _get_before(line.dup, index);
        if (array)
            before.insert(array);
        
        array = _get_after(line.dup, index);
        if (array)
            after.insert(array);
        
    }

    return new PassDigit(digit, before, after);
}

PassDigit[] get_all_digit_info(const string[] lines)
{
    PassDigit[] digits;

    foreach (c; "0123456789")
    {
        digits ~= get_digit_info(c, lines);
    }

    return digits;
}

string[] get_lines(const string file_name)
{
    string content;

    content = readText(file_name);

    return content.split();
}

void main()
{
    string[]    lines;
    PassDigit[] digits;

    lines = get_lines(FILE_NAME);
    digits = get_all_digit_info(lines);

    digits = filter!((d) => (!d.before.empty || !d.after.empty))(digits).array;
    sort!((d0, d1) => d0.before.length < d1.before.length)(digits);
    
    foreach (d; digits)
    {
        writef("%c", cast(char)d.digit);
    }
    writeln();
}