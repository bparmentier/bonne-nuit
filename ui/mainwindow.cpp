#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameconfigdialog.h"

#include <iostream>
#include <stdexcept>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(nullptr),
    gameObserver(nullptr)
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

void MainWindow::rafraichir(SujetDObservation *sdo)
{
    if (sdo != game) {
        return;
    }
    GameState gameState = game->gameState();
    GameAction gameAction = game->actionToPerform();
    if (gameState == GameState::FIRST_STAGE) {
        if (gameAction == GameAction::WAITING_FOR_DICE) {
            ui->rollDiceButton->setEnabled(true);
        } else {
            ui->rollDiceButton->setDisabled(true);
        }
    } else if (gameState == GameState::SECOND_STAGE) {
    }
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
    connect(ui->switchLightButton, &QPushButton::released,
            this, &MainWindow::switchLight);
}

void MainWindow::setObservers()
{
    gameObserver = new GameObserver(game, this);
    ui->graphicsView->setScene(gameObserver);

    game->attacher(this);
    ui->rollDiceButton->setEnabled(true);
}

void MainWindow::newGame()
{
    if (game != nullptr) {
        if (game->gameState() == GameState::OVER) {
            closeGame();
        } else {
            QMessageBox::StandardButton newGameRetVal = QMessageBox::question(
                        this,
                        "New game",
                        "Are you sure you want to start a new game?",
                        QMessageBox::Yes | QMessageBox::No);
            if (newGameRetVal == QMessageBox::Yes) {
                closeGame();
            } else {
                return;
            }
        }
    }

    GameConfigDialog configDialog{this};
    auto configRetVal = configDialog.exec();

    if (configRetVal == QDialog::Rejected) return;

    if (game == nullptr) {
        game = new Game(configDialog.players());
        setObservers();
    } else {
        return;
    }
}

void MainWindow::closeGame()
{
    game->detacher(this);
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
    if (game != nullptr) {
        try {
            game->rollDice();
        } catch (std::runtime_error const &e) {
            statusBar()->showMessage(e.what(), 3000);
        } catch (std::invalid_argument const &e) {
            statusBar()->showMessage(e.what(), 3000);
        }
    }
}

void MainWindow::switchLight()
{
    if (game != nullptr) {
        try {
            if (game->isLightOn()) {
                game->turnLightOff();
            } else {
                game->turnLightOn();
            }
        } catch (std::runtime_error const &e) {
            statusBar()->showMessage(e.what(), 3000);
        } catch (std::invalid_argument const &e) {
            statusBar()->showMessage(e.what(), 3000);
        } catch (std::out_of_range const &e) {
            statusBar()->showMessage(e.what(), 3000);
        }
    }
}
