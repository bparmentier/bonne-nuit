/*!
 * \file gamestate.h
 * \brief GameState enum class definition
 */

#ifndef GAMESTATE
#define GAMESTATE

/*!
 * \brief Define the state of the game
 */
enum class GameState {
    FIRST_STAGE, /*!< the first stage of the game */
    SECOND_STAGE, /*!< the second stage of the game */
    OVER /*!< the game is over */
};

#endif // GAMESTATE

