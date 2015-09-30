#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(nullptr)
{
    ui->setupUi(this);

    this->connection();
}

MainWindow::~MainWindow()
{
    delete game;
    game = nullptr;
    delete ui;
    ui = nullptr;
}

void MainWindow::connection()
{
    connect(ui->action_Quit, &QAction::triggered,
            &QCoreApplication::quit);
    connect(ui->action_New, &QAction::triggered,
            this, &MainWindow::newGame);
    connect(ui->action_Close, &QAction::triggered,
            this, &MainWindow::closeGame);
    connect(ui->action_Help, &QAction::triggered,
            this, &MainWindow::help);
}

void MainWindow::newGame()
{
    if (game == nullptr) {
        game = new Game();
    } else {
        return;
    }

    unsigned line;
    unsigned column;

    std::cout << *game << std::endl;

    while (game->gameState() == GameState::FIRST_STAGE) {
        std::cout << game->currentPlayer() << " is playing" << std::endl;
        std::cout << "Rolling dice: ";
        std::cout << game->rollDice() << std::endl;
        std::cout << "Drop position: " << game->dropPosition() << std::endl;
        std::cout << "Enter column: ";
        std::cin >> column;
        //do {
        try {
            game->placePiece(column);
        } catch (std::invalid_argument const &e) {
            std::cerr << e.what() << std::endl;
        } catch (std::out_of_range const &e) {
            std::cerr << e.what() << std::endl;
        }
        //} while (/*column is valid*/);

        std::cout << *game << std::endl;
    }

    std::cout << "Turning light off" << std::endl;
    game->turnLightOff();
    std::cout << *game << std::endl;

    while (game->gameState() == GameState::SECOND_STAGE) {
        std::cout << "Reverse piece (line): ";
        std::cin >> line;
        std::cout << "Reverse piece (column): ";
        std::cin >> column;
        try {
            game->reversePiece(line, column);
        } catch (std::runtime_error const &e) {
            std::cerr << e.what() << std::endl;
        }

        std::cout << *game << std::endl;
    }
    if (game->gameState() == GameState::OVER) {
        std::cout << "And the winner is: " << game->winner() << "!" << std::endl;
    }
}

void MainWindow::closeGame()
{

}

void MainWindow::help()
{

}

