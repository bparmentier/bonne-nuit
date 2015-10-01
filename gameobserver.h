#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "o_sdo/observateur.h"
#include "game.h"

class Game;

class GameObserver : public QGraphicsScene, public Observateur
{
private:
    Game *_game;
    std::vector<QGraphicsEllipseItem *> redPawns;
    std::vector<QGraphicsEllipseItem *> starPawns;


    void drawPawns(float xcenter, float ycenter, float radius, int pawnNumber);
    void drawStarPawns(float xcenter, float ycenter, float radius, int pawnNumber, int redPawnIndex);
    void updateRedPawns();
    void updateStarPawns();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    GameObserver(Game *game, QWidget *parent = 0);
    ~GameObserver();
    void rafraichir(SujetDObservation *sdo);
    void rollDice();
};

#endif // GAMEOBSERVER_H
