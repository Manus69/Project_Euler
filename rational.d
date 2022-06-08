module rational;

import std.conv;
import std.exception;
import std.format;

import euler_lib;

class Rational(T)
{
    T _top;
    T _bot;

    this(T top, T bot)
    {
        T d;

        enforce(bot != 0);
        if (bot < 0)
        {
            top = -top;
            bot = -bot;
        }

        d = gcdT!T(top, bot);
        _top = top / d;
        _bot = bot / d;
    }

    private Rational _add(const Rational rhs)
    {
        T _lcm;

        _lcm = lcmT(_bot, rhs._bot);

        return new Rational((_lcm / _bot) * _top + (_lcm / rhs._bot) * rhs._top, _lcm); 
    }

    private Rational _mult(const Rational rhs)
    {
        return new Rational(_top * rhs._top, _bot * rhs._bot);
    }

    private Rational _div(const Rational rhs)
    {
        return new Rational(_top * rhs._bot, _bot * rhs._top);
    }

    Rational opBinary(string op)(const Rational rhs)
    {
        static if (op == "+")
            return this._add(rhs);
        else static if (op == "*")
            return this._mult(rhs);
        else static if (op == "/")
            return this._div(rhs);
        else static assert (0);
    }

    Rational invert()
    {   
        T t;

        t = _top;
        _top = _bot;
        _bot = t;

        return this;
    }

    double value() const @property
    {
        return to!double(_top) / to!double(_bot);
    }

    override string toString() const
    {
        return format("%s / %s", _top, _bot);
    }
}
