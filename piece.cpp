#include "piece.h"

Piece::Piece(Color color, bool isStarOn) :
    _isGlowingInTheDark(false)
{
    if (color == Color::EMPTY && isStarOn == true) {
        throw std::invalid_argument("An empty piece cannot have its star on");
    }
    _color = color;
    _isStarOn = isStarOn;
}

Color Piece::color() const
{
    return _color;
}

bool Piece::isGlowingInTheDark() const
{
    return _isGlowingInTheDark;
}

void Piece::setGlowingInTheDark(bool isGlowingInTheDark)
{
    _isGlowingInTheDark = isGlowingInTheDark;
}
