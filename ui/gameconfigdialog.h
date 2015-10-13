/*!
 * \file gameconfigdialog.h
 * \brief GameConfigDialog class definition
 */

#ifndef GAMECONFIGDIALOG_H
#define GAMECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class GameConfigDialog;
}

/*!
 * \brief Configuration dialog displayed before creating a new game
 */
class GameConfigDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a GameConfigDialog. *parent* is passed to QDialog's
     * constructor.
     * \param parent
     */
    explicit GameConfigDialog(QWidget *parent = 0);

    /*!
     * \brief Destroys the GameConfigDialog.
     */
    ~GameConfigDialog();

    /*!
     * \brief Returns the number of players
     * \return the number of players
     */
    int players();

private:
    Ui::GameConfigDialog *ui;
    int _players;

private slots:
    void setPlayers(int);
};

#endif // GAMECONFIGDIALOG_H
