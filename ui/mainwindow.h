/*!
 * \file mainwindow.h
 * \brief MainWindow class definition
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "business/game.h"
#include "gameobserver.h"

namespace Ui {
class MainWindow;
}

/*!
 * \brief Main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a MainWindow with the given *parent*.
     * \param parent the parent widget
     */
    explicit MainWindow(QWidget *parent = 0);

    /*!
     * \brief Destroys the main window.
     */
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
