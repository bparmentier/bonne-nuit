#include "piece.h"

Piece::Piece(Color color, bool isStarOn) :
    _color(color),
    _isStarOn(isStarOn)
{
}

Color Piece::color() const
{
    return _color;
}

bool Piece::isStarOn() const
{
    return _isStarOn;
}

void Piece::lightUpStar()
{
    _isStarOn = true;
}

void Piece::darkenStar()
{
    _isStarOn = false;
}
