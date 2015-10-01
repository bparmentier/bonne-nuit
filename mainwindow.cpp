#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdexcept>
#include <QMessageBox>

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
    delete gameObserver;
    gameObserver = nullptr;
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
    connect(ui->rollDiceButton, &QPushButton::released,
            this, &MainWindow::rollDice);
}

void MainWindow::setObserver()
{
    gameObserver = new GameObserver(game, this);
    ui->graphicsView->setScene(gameObserver);
}

void MainWindow::newGame()
{
    if (game != nullptr) {
        if (game->gameState() == GameState::OVER) {
            closeGame();
        } else {
            QMessageBox::StandardButton newGameRetVal = QMessageBox::question(
                        this,
                        "Nouvelle partie",
                        "Êtes-vous sûr de vouloir commencer une nouvelle partie ?",
                        QMessageBox::Yes | QMessageBox::No);
            if (newGameRetVal == QMessageBox::Yes) {
                closeGame();
            } else {
                return;
            }
        }
    }
    if (game == nullptr) {
        game = new Game();
    } else {
        return;
    }

    setObserver();

    unsigned line;
    unsigned column;

    std::cout << *game << std::endl;

//    while (game->gameState() == GameState::FIRST_STAGE) {
//        std::cout << game->currentPlayer() << " is playing" << std::endl;
//        std::cout << "Rolling dice: ";
//        std::cout << game->rollDice() << std::endl;
//        std::cout << "Drop position: " << game->dropPosition() << std::endl;
//        std::cout << "Enter column: ";
//        std::cin >> column;
//        //do {
//        try {
//            game->placePiece(column);
//        } catch (std::invalid_argument const &e) {
//            std::cerr << e.what() << std::endl;
//        } catch (std::out_of_range const &e) {
//            std::cerr << e.what() << std::endl;
//        }
//        //} while (/*column is valid*/);

//        std::cout << *game << std::endl;
//    }

//    std::cout << "Turning light off" << std::endl;
//    game->turnLightOff();
//    std::cout << *game << std::endl;

//    while (game->gameState() == GameState::SECOND_STAGE) {
//        std::cout << "Reverse piece (line): ";
//        std::cin >> line;
//        std::cout << "Reverse piece (column): ";
//        std::cin >> column;
//        try {
//            game->reversePiece(line, column);
//        } catch (std::runtime_error const &e) {
//            std::cerr << e.what() << std::endl;
//        }

//        std::cout << *game << std::endl;
//    }
//    if (game->gameState() == GameState::OVER) {
//        std::cout << "And the winner is: " << game->winner() << "!" << std::endl;
//    }
}

void MainWindow::closeGame()
{
    delete gameObserver;
    gameObserver = nullptr;
    delete game;
    game = nullptr;
}

void MainWindow::help()
{

}

void MainWindow::rollDice()
{
    if (gameObserver != nullptr) {
        try {
            gameObserver->rollDice();
        } catch (std::runtime_error const &e) {
            setStatusTip(QString::fromStdString(e.what()));
        }
    }
}
