#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameconfigdialog.h"

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
    connect(ui->switchLightButton, &QPushButton::released,
            this, &MainWindow::switchLight);
}

void MainWindow::setObserver()
{
    gameObserver = new GameObserver(game, this);
    ui->graphicsView->setScene(gameObserver);
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

    GameConfigDialog configDialog{this};
    auto configRetVal = configDialog.exec();

    if (configRetVal == QDialog::Rejected) return;

    if (game == nullptr) {
        game = new Game(configDialog.players());
        setObserver();
    } else {
        return;
    }
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
    if (game != nullptr) {
        try {
            game->rollDice();
        } catch (std::runtime_error const &e) {
            setStatusTip(QString::fromStdString(e.what()));
        } catch (std::invalid_argument const &e) {
            setStatusTip(QString::fromStdString(e.what()));
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
            setStatusTip(QString::fromStdString(e.what()));
        } catch (std::invalid_argument const &e) {
            setStatusTip(QString::fromStdString(e.what()));
        } catch (std::out_of_range const &e) {
            setStatusTip(QString::fromStdString(e.what()));
        }
    }
}
