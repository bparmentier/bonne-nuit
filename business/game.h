#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ostream>

#include "o_sdo/sujetdobservation.h"
#include "piece.h"
#include "color.h"
#include "gamestate.h"
#include "gameaction.h"

class Game : public SujetDObservation
{
private:
    std::vector<std::vector<Piece>> _board;
    std::vector<Color> _players;
    unsigned _dropPosition;
    bool _isLightOn;
    Color _winner;
    GameState _gameState;
    unsigned _playCount;
    GameAction _actionToPerform;
    unsigned _numberOfStarsLeft;
    unsigned _currentPlayer;

    void placeAbsentPlayersPieces(std::vector<Color> absentPlayers);
    void findLastStar();

public:
    static const unsigned MIN_PLAYERS = 3;
    static const unsigned MAX_PLAYERS = 5;
    static const unsigned MIN_DICE = 1;
    static const unsigned MAX_DICE = 3;

    Game();
    Game(unsigned playersNumber);
    ~Game();

    unsigned rollDice();
    void placePiece(unsigned column);
    void turnLightOff();
    void turnLightOn();
    void reversePiece(unsigned line, unsigned column);

    const std::vector<Color> players() const;
    const std::vector<std::vector<Piece>> &board() const;
    unsigned dropPosition() const;
    Color currentPlayer() const;
    GameState gameState() const;
    GameAction actionToPerform() const;
    Color winner() const;
    bool isLightOn() const;
};

std::ostream & operator<<(std::ostream & out, const Game & in);

#endif // GAME_H
