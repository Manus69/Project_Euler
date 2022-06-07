module number;

import std.exception;
import std.conv;

class Number
{
    char[10]    _digit_count;
    ulong       _value;
    uint        _n_digits;

    this(ulong n)
    {
        enforce(n > 0);

        _value = n;
        while (n)
        {
            ++ _digit_count[n % 10];
            n /= 10;
            ++ _n_digits;
        }
    }

    uint n_digits() const @property
    {
        return _n_digits;
    }

    bool opEquals(const Number number) const
    {
        return this._digit_count == number._digit_count;
    }

    override string toString() const
    {
        return to!string(_value);
    }
}