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

    ui->centralWidget->hide();
    this->connection();
}

MainWindow::~MainWindow()
{
    if (game != nullptr) {
        game->detacher(this);
    }
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
    GameAction gameAction = game->actionToPerform();
    if (gameAction == GameAction::WAITING_FOR_DICE) {
        ui->rollDiceButton->setEnabled(true);
    } else {
        ui->rollDiceButton->setDisabled(true);
    }
    if (gameAction == GameAction::WAITING_FOR_LIGHT_OFF
            || gameAction == GameAction::WAITING_FOR_LIGHT_ON) {
        ui->switchLightButton->setEnabled(true);
    } else {
        ui->switchLightButton->setDisabled(true);
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
    connect(ui->action_About, &QAction::triggered,
            this, &MainWindow::about);
    connect(ui->rollDiceButton, &QPushButton::released,
            this, &MainWindow::rollDice);
    connect(ui->switchLightButton, &QPushButton::released,
            this, &MainWindow::switchLight);
}

void MainWindow::setObservers()
{
    gameObserver = new GameObserver(game, this);
    ui->graphicsView->setScene(gameObserver);
    ui->centralWidget->setVisible(true);
    ui->centralWidget->setEnabled(true);

    game->attacher(this);
    ui->rollDiceButton->setEnabled(true);

    connect(gameObserver, &GameObserver::statusEvent,
            this, &MainWindow::setStatusBarMessage);
}

void MainWindow::newGame()
{
    if (game != nullptr) {
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
    if (game != nullptr) {
        game->detacher(this);
    }
    ui->centralWidget->setDisabled(true);
    ui->centralWidget->hide();
    delete gameObserver;
    gameObserver = nullptr;
    delete game;
    game = nullptr;
}

void MainWindow::help()
{
    QMessageBox::information(this, "Help",
        "<h2>How to play</h2>"
        "<p>Each player has three pawns of the same color.</p>"
        "<p>The game takes place in two stages:</p>"
        "<ol>"
        "<li>Each player successively rolls the dice and moves the drop of the "
        "given number along the red pawns, then place one of his pawns with "
        "the star up around the red pawn.</li>"
        "<li>When all the pawns have been set, turn the light off and, in the "
        "same order, each player reverses a pawn of his choice.<br />"
        "When there is one pawn left, turn the light on. The winner is the "
        "player of this color.</li>"
        "</ol>"
        "<p>Players order:</p>"
        "<ul>"
        "<li>5 players"
        "<ol>"
        "<li>PURPLE</li>"
        "<li>BLACK</li>"
        "<li>RED</li>"
        "<li>GREEN</li>"
        "<li>BLUE</li>"
        "</ol></li>"
        "<li>4 players"
        "<ol>"
        "<li>PURPLE</li>"
        "<li>BLACK</li>"
        "<li>RED</li>"
        "<li>GREEN</li>"
        "</ol></li>"
        "<li>3 players"
        "<li><ol>"
        "<li>PURPLE</li>"
        "<li>BLACK</li>"
        "<li>RED</li>"
        "</ol></li>"
        "</ul>");
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Bonne nuit !",
        "<p>Game created for ALG3IR class by Bruno Parmentier "
        "at École Supérieure d'Informatique, Brussels.</p>");
}

void MainWindow::rollDice()
{
    if (game != nullptr
            && game->actionToPerform() == GameAction::WAITING_FOR_DICE) {
        try {
            game->rollDice();
        } catch (std::runtime_error const &e) {
            setStatusBarMessage(e.what());
        } catch (std::invalid_argument const &e) {
            setStatusBarMessage(e.what());
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
                ui->switchLightButton->setDisabled(true);
            }
        } catch (std::runtime_error const &e) {
            setStatusBarMessage(e.what());
        } catch (std::invalid_argument const &e) {
            setStatusBarMessage(e.what());
        } catch (std::out_of_range const &e) {
            setStatusBarMessage(e.what());
        }
    }
}

void MainWindow::setStatusBarMessage(const QString &message)
{
    statusBar()->showMessage(message, 3000);
}
