#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "o_sdo/observateur.h"
#include "game.h"

class Game;

class GameObserver : public QGraphicsScene, public Observateur
{
private:
    Game *_game;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    GameObserver(Game *game, QWidget *parent = 0);
    ~GameObserver();
    void rafraichir(SujetDObservation *sdo);
};

#endif // GAMEOBSERVER_H
