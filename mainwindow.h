#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "business/game.h"
#include "gameobserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Game *game;
    GameObserver *gameObserver;

    void printBoard();
    void connection();
    void setObserver();

private slots:
    void newGame();
    void closeGame();
    void help();
    void rollDice();
    void switchLight();
};

#endif // MAINWINDOW_H
