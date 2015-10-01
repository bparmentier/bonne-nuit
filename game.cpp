#include "game.h"

#include <cstdlib>
#include <stdexcept>
#include <iostream>

Game::Game() :
    Game(3)
{
}

Game::~Game()
{
}

Game::Game(unsigned playersNumber) :
    _dropPosition(0),
    _isLightOn(true),
    _winner(Color::EMPTY),
    _gameState(GameState::FIRST_STAGE),
    _playCount(0),
    _actionToPerform(GameAction::WAITING_FOR_DICE),
    _numberOfStarsLeft(15)
{
    if (playersNumber < MIN_PLAYERS || playersNumber > MAX_PLAYERS) {
        throw std::invalid_argument(
                    "Number of players must be between "
                    + std::to_string(MIN_PLAYERS) + " and "
                    + std::to_string(MAX_PLAYERS));
    }

    for (unsigned line = 0; line < 9; ++line) {
        std::vector<Piece> colorsLine;
        _board.push_back(colorsLine);
        for (unsigned column = 0; column < 5; ++column) {
            _board.at(line).push_back(Piece{Color::EMPTY, false});
        }
    }
    _players = {Color::PURPLE, Color::BLACK, Color::RED};
    _currentPlayer = 0;

    std::vector<Color> _absentPlayers;
    if (playersNumber <= 4) {
        _absentPlayers.push_back(Color::GREEN);
    }
    if (playersNumber <= 5) {
        _absentPlayers.push_back(Color::BLUE);
    }

    placeAbsentPlayersPieces(_absentPlayers);
}

void Game::placeAbsentPlayersPieces(std::vector<Color> absentPlayers)
{
    bool placed;
    for (auto i = 0; i < 3; ++i) {
        for (auto absentPlayer : absentPlayers) {
            placed = false;
            do {
                unsigned line = rand() % 9;
                unsigned column = rand() % 5;
                if (_board.at(line).at(column).color() == Color::EMPTY) {
                    _board.at(line).at(column) = Piece(absentPlayer, false);
                    placed = true;
                }
            } while (placed == false);
        }
    }
}

unsigned Game::rollDice()
{
    if (_gameState == GameState::SECOND_STAGE) {
        throw std::runtime_error("Launching the dice is only possible "
                                     "during the first stage of the game");
    }
    unsigned dice = rand() % 3 + 1;
    _dropPosition = (_dropPosition + dice) % 9;
    notifierChangement();
    return dice;
}

void Game::placePiece(unsigned column)
{
    if (_gameState == GameState::OVER) {
        throw std::runtime_error("Game is over");
    }
    if (_gameState == GameState::SECOND_STAGE) {
        throw std::runtime_error("Cannot place piece during the second "
                                     "stage of the game");
    }
    if (column > 4) {
        throw std::out_of_range("Column must be between 0 and 4");
    }
    if (_board.at(_dropPosition).at(column).color() != Color::EMPTY) {
        throw std::invalid_argument("Not empty");
    }
    _board.at(_dropPosition).at(column) = Piece(currentPlayer(), false);
    _currentPlayer = (_currentPlayer + 1) % _players.size();
    _playCount++;
    if (_playCount == (_players.size() * 3)) { // each player plays 3 times
        _gameState = GameState::SECOND_STAGE;
    }

    notifierChangement();
}

void Game::turnLightOff()
{
    if (_gameState == GameState::FIRST_STAGE) {
        throw std::runtime_error("Cannot turn light off during first stage");
    }
    for (auto line = 0; line < 9; ++line) {
        for (auto column = 0; column < 5; ++column) {
            Piece &piece = _board.at(line).at(column);
            if (piece.color() != Color::EMPTY){
                piece.lightUpStar();
            }
        }
    }
    _isLightOn = false;

    notifierChangement();
}

void Game::turnLightOn()
{
    if (_gameState == GameState::FIRST_STAGE) {
        throw std::runtime_error("Game is over");
    }
    _isLightOn = true;

    notifierChangement();
}

void Game::reversePiece(unsigned line, unsigned column)
{
    Piece &piece = _board.at(line).at(column);
    if (piece.color() == Color::EMPTY) {
        throw std::invalid_argument("No piece here");
    }
    if (piece.isStarOn()) {
        piece.darkenStar();
        _numberOfStarsLeft -= 1;
    } else {
        throw std::runtime_error("Star is already off");
    }

    if (_numberOfStarsLeft == 1) {
        _gameState = GameState::OVER;
        findLastStar();
    }

    notifierChangement();
}

void Game::findLastStar()
{
    bool lastStarFound = false;
    unsigned line = 0;
    unsigned column = 0;
    while (!lastStarFound && line < 9) {
        while (!lastStarFound && column < 5) {
            Piece piece = _board.at(line).at(column);
            if ((piece.color() != Color::EMPTY) && piece.isStarOn()) {
                _winner = piece.color();
                lastStarFound = true;
            }
            column++;
        }
        line++;
    }
}

const std::vector<Color> Game::players() const
{
    return _players;
}

const std::vector<std::vector<Piece>> &Game::board() const
{
    return _board;
}

unsigned Game::dropPosition() const
{
    return _dropPosition;
}

Color Game::currentPlayer() const
{
    return _players.at(_currentPlayer);
}

GameState Game::gameState() const
{
    return _gameState;
}

GameAction Game::actionToPerform() const
{
    return _actionToPerform;
}

Color Game::winner() const
{
    return _winner;
}

bool Game::isLightOn() const
{
    return _isLightOn;
}

std::ostream & operator<<(std::ostream & out, const Game & in)
{
    std::vector<std::vector<Piece>> board = in.board();

    out << "Drop position: " << in.dropPosition() << std::endl;
    out << "  01234" << std::endl;
    for (unsigned line = 0; line < 9; line++) {
        out << line << " ";
        for (unsigned column = 0; column < 5; column++) {
            bool isStarOn = board.at(line).at(column).isStarOn();
            switch (board.at(line).at(column).color()) {
            case Color::EMPTY:
                out << '_';
                break;
            case Color::BLACK:
                out << (isStarOn ? 'A' : 'a');
                break;
            case Color::BLUE:
                out << (isStarOn ? 'B' : 'b');
                break;
            case Color::GREEN:
                out << (isStarOn ? 'C' : 'c');
                break;
            case Color::PURPLE:
                out << (isStarOn ? 'D' : 'd');
                break;
            case Color::RED:
                out << (isStarOn ? 'E' : 'e');
                break;
            default:
                out << '?';
            }
        }
        out << std::endl;
    }

    return out;
}
