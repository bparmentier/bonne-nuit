/*!
 * \file game.h
 * \brief Game class definition
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ostream>

#include "o_sdo/sujetdobservation.h"
#include "piece.h"
#include "color.h"
#include "gamestate.h"
#include "gameaction.h"

/*!
 * \brief A "Bonne nuit !" game
 */
class Game : public SujetDObservation
{
private:
    std::vector<std::vector<Piece>> _board;
    std::vector<Color> _players;
    unsigned _dropPosition;
    bool _isLightOn;
    Color _winner;
    std::pair<int, int> _lastPawnCoordinates;
    GameState _gameState;
    unsigned _playCount;
    GameAction _actionToPerform;
    unsigned _numberOfStarsLeft;
    unsigned _currentPlayer;

    void placeAbsentPlayersPieces(std::vector<Color> absentPlayers);
    void findLastStar();

public:
    /*!
     * \brief The minimum number of players
     */
    static const unsigned MIN_PLAYERS = 3;

    /*!
     * \brief The maximum number of players
     */
    static const unsigned MAX_PLAYERS = 5;

    /*!
     * \brief The minimum number on the dice
     */
    static const unsigned MIN_DICE = 1;

    /*!
     * \brief The maximum number on the dice
     */
    static const unsigned MAX_DICE = 3;

    /*!
     * \brief Constructs a Game with the default number of players
     */
    Game();

    /*!
     * \brief Constructs a Game with *playersNumber* players
     * \param playersNumber the number of players
     */
    Game(unsigned playersNumber);

    /*!
     * \brief Destroys the Game
     */
    ~Game();

    /*!
     * \brief Roll the dice
     * \return the number given by the dice
     */
    unsigned rollDice();

    /*!
     * \brief Place a Piece of the current player color in the given *column*.
     * The line is automatically determined when the dice is launched.
     * \param column the column where to place the Piece
     */
    void placePiece(unsigned column);

    /*!
     * \brief Turn the light off
     */
    void turnLightOff();

    /*!
     * \brief Turn the light on
     */
    void turnLightOn();

    /*!
     * \brief Reverse the Piece at the given *line* and *column*
     * \param line the line indice of the Piece
     * \param column the column indice of the Piece
     */
    void reversePiece(unsigned line, unsigned column);

    /*!
     * \brief Returns a vector of players Color
     * \return a vector of players Color
     */
    const std::vector<Color> players() const;

    /*!
     * \brief Returns a copy of the game board
     * \return a copy of the game board
     */
    const std::vector<std::vector<Piece>> &board() const;

    /*!
     * \brief Returns the position of the drop
     * \return the position of the drop
     */
    unsigned dropPosition() const;

    /*!
     * \brief Returns the current player's Color
     * \return the current player's Color
     */
    Color currentPlayer() const;

    /*!
     * \brief Returns the state of the game
     * \return the state of the game
     */
    GameState gameState() const;

    /*!
     * \brief Returns the action to perform
     * \return the action to perform
     */
    GameAction actionToPerform() const;

    /*!
     * \brief Returns the winner Color
     * \return the winner Color
     */
    Color winner() const;

    /*!
     * \brief Returns if the light is turned on
     * \return `true` if the light is turned on, `false` otherwise
     */
    bool isLightOn() const;

    /*!
     * \brief Returns last pawn coordinates. The *first* member is the line and
     * the *second* member is the column.
     * \return last pawn coordinates
     */
    const std::pair<int, int> lastPawnCoordinates() const;
};

/*!
 * \brief operator <<
 * \param out the output stream
 * \param in the game
 * \return a textual representation of the Game *in*
 */
std::ostream & operator<<(std::ostream & out, const Game & in);

#endif // GAME_H
