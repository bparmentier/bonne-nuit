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

    game->attacher(this);
    ui->rollDiceButton->setEnabled(true);

    connect(gameObserver, &GameObserver::statusEvent,
            this, &MainWindow::setStatusBarMessage);
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
    if (game != nullptr) {
        game->detacher(this);
    }
    ui->centralWidget->setDisabled(true);
    delete gameObserver;
    gameObserver = nullptr;
    delete game;
    game = nullptr;
}

void MainWindow::help()
{
    QMessageBox::information(this, "Help",
                             "<h1>How to play</h1>"
                             "<p>Each player has three pawns of the same color."
                             "</p>");
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Bonne nuit !",
                       "<p>Game created for ALG3IR class by Bruno Parmentier "
                       "at École Supérieure d'Informatique, Brussels.");
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
