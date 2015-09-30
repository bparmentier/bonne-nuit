#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "game.h"
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
};

#endif // MAINWINDOW_H
