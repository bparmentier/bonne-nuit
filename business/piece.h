#ifndef PIECE_H
#define PIECE_H

#include "color.h"

class Piece
{
public:
    Piece(Color color, bool isStarOn);
    Color color() const;
    bool isGlowingInTheDark() const;
    void setGlowingInTheDark(bool isGlowingInTheDark);

private:
    Color _color;
    bool _isStarOn;
    bool _isGlowingInTheDark;
};

#endif // PIECE_H
