/*!
 * \file gameaction.h
 * \brief GameAction enum class definition
 */

#ifndef GAMEACTION
#define GAMEACTION

/*!
 * \brief Define a pending game action
 */
enum class GameAction
{
    WAITING_FOR_DICE, /*!< Waiting for a dice roll */
    WAITING_FOR_PIECE, /*!< Waiting for a pawn to be placed */
    WAITING_FOR_REVERSE, /*!< Waiting for a pawn to be reversed */
    WAITING_FOR_LIGHT_OFF, /*!< Waiting for the light to be turned off */
    WAITING_FOR_LIGHT_ON /*!< Waiting for the light to be turned on */
};

#endif // GAMEACTION
