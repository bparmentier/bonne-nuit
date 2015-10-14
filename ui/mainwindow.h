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
class MainWindow : public QMainWindow, public Observateur
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

    /*!
     * \brief Refresh the observer when the game state changes
     * \param sdo the subject
     */
    void rafraichir(SujetDObservation *sdo);

private:
    Ui::MainWindow *ui;
    Game *game;
    GameObserver *gameObserver;

    void printBoard();
    void connection();
    void setObservers();

private slots:
    void newGame();
    void closeGame();
    void help();
    void about();
    void rollDice();
    void switchLight();

public slots:
    void setStatusBarMessage(const QString &);
};

#endif // MAINWINDOW_H
