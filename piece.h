#ifndef PIECE_H
#define PIECE_H

#include "color.h"

class Piece
{
public:
    Piece(Color color, bool isStarOn);
    Color color() const;
    bool isStarOn() const;
    void lightUpStar();
    void darkenStar();

private:
    Color _color;
    bool _isStarOn;
};

#endif // PIECE_H
