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
    _players{Color::PURPLE, Color::BLACK, Color::RED, Color::GREEN, Color::BLUE},
    _dropPosition(0),
    _isLightOn(true),
    _winner(Color::EMPTY),
    _lastPawnCoordinates(-1, -1),
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

    _currentPlayer = 0;

    handleAbsentPlayers(playersNumber);
}

void Game::handleAbsentPlayers(unsigned playersNumber)
{
    std::vector<Color> absentPlayers;
    if (playersNumber < 4) {
        absentPlayers.push_back(Color::GREEN);
        _players.pop_back();
    }
    if (playersNumber < 5) {
        absentPlayers.push_back(Color::BLUE);
        _players.pop_back();
    }

    if (!absentPlayers.empty()) {
        placeAbsentPlayersPieces(absentPlayers);
    }
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
                    _board.at(line).at(column) = Piece(absentPlayer, true);
                    placed = true;
                }
            } while (!placed);
        }
    }
}

unsigned Game::rollDice()
{
    if (_gameState == GameState::SECOND_STAGE) {
        throw std::runtime_error("Launching the dice is only possible "
                                     "during the first stage of the game");
    }
    if (_actionToPerform != GameAction::WAITING_FOR_DICE) {
        throw std::runtime_error("Not waiting for dice roll");
    }
    unsigned dice = rand() % 3 + 1;
    _dropPosition = (_dropPosition + dice) % 9;
    _actionToPerform = GameAction::WAITING_FOR_PIECE;
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
    if (_actionToPerform != GameAction::WAITING_FOR_PIECE) {
        throw std::runtime_error("Cannot place piece");
    }
    _board.at(_dropPosition).at(column) = Piece(currentPlayer(), true);
    _currentPlayer = (_currentPlayer + 1) % _players.size();
    _playCount++;
    _actionToPerform = GameAction::WAITING_FOR_DICE;
    if (_playCount == (_players.size() * 3)) { // each player plays 3 times
        _gameState = GameState::SECOND_STAGE;
        _actionToPerform = GameAction::WAITING_FOR_REVERSE;
    }

    notifierChangement();
}

void Game::turnLightOff()
{
    if (_gameState != GameState::SECOND_STAGE) {
        throw std::runtime_error("Turning light off is only possible during the"
                                 " second stage");
    }
    for (auto line = 0; line < 9; ++line) {
        for (auto column = 0; column < 5; ++column) {
            Piece &piece = _board.at(line).at(column);
            if (piece.color() != Color::EMPTY){
                piece.setGlowingInTheDark(true);
            }
        }
    }
    _isLightOn = false;

    notifierChangement();
}

void Game::turnLightOn()
{
    if (_gameState != GameState::OVER) {
        throw std::runtime_error("Game is not over");
    }
    _isLightOn = true;

    notifierChangement();
}

void Game::reversePiece(unsigned line, unsigned column)
{
    if (_gameState == GameState::FIRST_STAGE) {
        throw std::runtime_error("Cannot reverse piece during first stage");
    }
    if (_gameState == GameState::OVER) {
        throw std::runtime_error("Game is over");
    }
    Piece &piece = _board.at(line).at(column);
    if (piece.color() == Color::EMPTY) {
        throw std::invalid_argument("No piece here");
    }
    if (piece.isGlowingInTheDark()) {
        piece.setGlowingInTheDark(false);
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
    while (!lastStarFound && line < 9) {
        unsigned column = 0;
        while (!lastStarFound && column < 5) {
            Piece piece = _board.at(line).at(column);
            if ((piece.color() != Color::EMPTY) && piece.isGlowingInTheDark()) {
                _lastPawnCoordinates = {line, column};
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

const std::pair<int, int> Game::lastPawnCoordinates() const
{
    return _lastPawnCoordinates;
}


std::ostream & operator<<(std::ostream & out, const Game & in)
{
    std::vector<std::vector<Piece>> board = in.board();

    out << "Drop position: " << in.dropPosition() << std::endl;
    out << "  01234" << std::endl;
    for (unsigned line = 0; line < 9; line++) {
        out << line << " ";
        for (unsigned column = 0; column < 5; column++) {
            bool isGlowing = board.at(line).at(column).isGlowingInTheDark();
            switch (board.at(line).at(column).color()) {
            case Color::EMPTY:
                out << '_';
                break;
            case Color::BLACK:
                out << (isGlowing ? 'A' : 'a');
                break;
            case Color::BLUE:
                out << (isGlowing ? 'B' : 'b');
                break;
            case Color::GREEN:
                out << (isGlowing ? 'C' : 'c');
                break;
            case Color::PURPLE:
                out << (isGlowing ? 'D' : 'd');
                break;
            case Color::RED:
                out << (isGlowing ? 'E' : 'e');
                break;
            default:
                out << '?';
            }
        }
        out << std::endl;
    }

    return out;
}
