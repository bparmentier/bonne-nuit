#ifndef COLOR_H
#define COLOR_H

#include <ostream>

enum class Color
{
    EMPTY,
    BLACK,
    BLUE,
    GREEN,
    PURPLE,
    RED
};

inline std::ostream & operator<<(std::ostream & out, const Color & in)
{
    switch (in) {
    case Color::EMPTY:
        out << "EMPTY";
        break;
    case Color::BLACK:
        out << "BLACK";
        break;
    case Color::BLUE:
        out << "BLUE";
        break;
    case Color::GREEN:
        out << "GREEN";
        break;
    case Color::PURPLE:
        out << "PURPLE";
        break;
    case Color::RED:
        out << "RED";
        break;
    }

    return out;
}

#endif // COLOR_H
