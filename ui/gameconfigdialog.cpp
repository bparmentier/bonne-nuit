#include "gameconfigdialog.h"
#include "ui_gameconfigdialog.h"

GameConfigDialog::GameConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameConfigDialog),
    _players(3)
{
    ui->setupUi(this);
    setWindowTitle("Players");
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this,
            SLOT(setPlayers(int)));
}

GameConfigDialog::~GameConfigDialog()
{
    delete ui;
}

int GameConfigDialog::players()
{
    return _players;
}

void GameConfigDialog::setPlayers(int players)
{
    _players = players + 3;
}
