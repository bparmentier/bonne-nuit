/*!
 * \file piece.h
 * \brief Piece class definition
 */

#ifndef PIECE_H
#define PIECE_H

#include "color.h"

/*!
 * \brief A piece of the game
 */
class Piece
{
public:
    /*!
     * \brief Constructs a Piece with the given *color* and draw a star on it if
     * *isStarOn* is `true`
     * \param color the color of the Piece
     * \param isStarOn draw a star if `true`
     */
    Piece(Color color, bool isStarOn);

    /*!
     * \brief Returns the color of the Piece
     * \return the color of the Piece
     */
    Color color() const;

    /*!
     * \brief Returns if the star is glowing in the dark. It happens when the
     * light is turned off.
     * \return `true` if the star is glowing in the dark, `false` otherwise
     */
    bool isGlowingInTheDark() const;

    /*!
     * \brief Set the star glowing or not in the dark
     * \param isGlowingInTheDark if the star should be glowing in the dark
     */
    void setGlowingInTheDark(bool isGlowingInTheDark);

private:
    Color _color;
    bool _isStarOn;
    bool _isGlowingInTheDark;
};

#endif // PIECE_H
