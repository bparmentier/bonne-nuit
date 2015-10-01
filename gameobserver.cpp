#include "gameobserver.h"
#include "mainwindow.h"

GameObserver::GameObserver(Game *game, QWidget *parent) :
    QGraphicsScene{parent},
    _game{game}
{
    _game->attacher(this);
    drawPawns(0, 0, 200, 9);
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

void GameObserver::drawPawns(float xcenter, float ycenter, float radius, int pawnNumber)
{
    int x, y;
    float angle;
    int pawnDiameter = 20;

    QPen pen{QPen(Qt::black)};
    QBrush redBrush{QBrush(QColor(Qt::red))};
    QBrush blueBrush{QBrush(QColor(Qt::blue))};
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius - (pawnDiameter / 2);
        y = ycenter + sinf(angle) * radius - (pawnDiameter / 2);
        QGraphicsEllipseItem *pawn;
        if (_game->dropPosition() == i) {
            pawn = addEllipse(x, y, pawnDiameter, pawnDiameter, pen, blueBrush);
        } else {
            pawn = addEllipse(x, y, pawnDiameter, pawnDiameter, pen, redBrush);
        }

        pawn->setCursor(pointingHandCursor);
        redPawns.push_back(pawn);

        drawStarPawns(x + (pawnDiameter / 2), y + (pawnDiameter / 2), 30, 5, i);
    }

    addEllipse(0, 0, 2, 2);
}

void GameObserver::drawStarPawns(float xcenter, float ycenter,
                                 float radius, int pawnNumber, int redPawnIndex)
{
    int x, y;
    float angle;
    int pawnDiameter = 10;

    QPen pen{QPen(Qt::black)};
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius - pawnDiameter / 2;
        y = ycenter + sinf(angle) * radius - pawnDiameter / 2;
        QGraphicsEllipseItem *pawn;
        pawn = addEllipse(x, y, pawnDiameter, pawnDiameter, pen);

        pawn->setCursor(pointingHandCursor);
        starPawns.push_back(pawn);
    }
}

void GameObserver::updateRedPawns()
{

}

void GameObserver::updateStarPawns()
{

}

void GameObserver::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    QGraphicsItem *element = itemAt(event->lastScenePos().x(),
                                    event->lastScenePos().y(),
                                    QTransform());

}

void GameObserver::keyPressEvent(QKeyEvent *event)
{

}
