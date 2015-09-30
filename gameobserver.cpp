#include "gameobserver.h"
#include "mainwindow.h"

GameObserver::GameObserver(Game *game, QWidget *parent) :
    QGraphicsScene{parent},
    _game{game}
{
    game->attacher(this);
}

GameObserver::~GameObserver()
{
    _game->detacher(this);
}

void GameObserver::rafraichir(SujetDObservation *sdo)
{
    if (sdo != _game) {
        return;
    }

}

void GameObserver::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void GameObserver::keyPressEvent(QKeyEvent *event)
{

}
