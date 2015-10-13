/*!
 * \file color.h
 * \brief Color enum class definition
 */

#ifndef COLOR_H
#define COLOR_H

#include <ostream>

/*!
 * \brief Define a color
 */
enum class Color
{
    EMPTY, /*!< "Empty" color, usually for an empty pawn */
    BLACK, /*!< Black color */
    BLUE, /*!< Blue color */
    GREEN, /*!< Green color */
    PURPLE, /*!< Purple color */
    RED /*!< Red color */
};

/*!
 * \brief operator <<
 * \param out the output stream
 * \param in the color
 * \return a textual representation of the color *in*
 */
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
