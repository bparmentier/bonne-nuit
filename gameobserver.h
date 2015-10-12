#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSvgItem>

#include "o_sdo/observateur.h"
#include "game.h"
#include "qstarpawn.h"

class Game;

class GameObserver : public QGraphicsScene, public Observateur
{
private:
    static const int KEY_RED_PAWN_INDICE = 0x0;
    static const int KEY_STAR_PAWN_INDICE = 0x1;
    static const int KEY_TYPE_RED_PAWN = 0x2;
    static const int KEY_TYPE_STAR_PAWN = 0x3;

    Game *_game;
    std::vector<QGraphicsEllipseItem *> redPawns;
    std::vector<std::vector<QStarPawn *>> starPawns;
    QGraphicsSvgItem *drop;

    void drawPawns(float xcenter, float ycenter, float radius, unsigned pawnNumber);
    void drawStarPawns(float xcenter, float ycenter, float radius, unsigned pawnNumber, unsigned redPawnIndex);
    void updateRedPawns();
    void updateStarPawns();
    void updateBackground();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    GameObserver(Game *game, QWidget *parent = 0);
    ~GameObserver();
    void rafraichir(SujetDObservation *sdo);
};

#endif // GAMEOBSERVER_H
