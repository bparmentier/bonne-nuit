#ifndef GAMECONFIGDIALOG_H
#define GAMECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class GameConfigDialog;
}

class GameConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameConfigDialog(QWidget *parent = 0);
    ~GameConfigDialog();
    int players();

private:
    Ui::GameConfigDialog *ui;
    int _players;

private slots:
    void setPlayers(int);
};

#endif // GAMECONFIGDIALOG_H
