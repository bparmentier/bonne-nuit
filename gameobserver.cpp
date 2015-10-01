#include "gameobserver.h"
#include "mainwindow.h"

GameObserver::GameObserver(Game *game, QWidget *parent) :
    QGraphicsScene{parent},
    _game{game}
{
    _game->attacher(this);
    drawRedPawns(0, 0, 200, 9);
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

void GameObserver::drawRedPawns(float xcenter, float ycenter, float radius, int pawnNumber)
{
    int x, y;
    float angle;

    QPen pen{QPen(Qt::black)};
    QBrush redBrush{QBrush(QColor(Qt::red))};
    QBrush blueBrush{QBrush(QColor(Qt::blue))};
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius;
        y = ycenter + sinf(angle) * radius;
        QGraphicsEllipseItem *pawn;
        if (_game->dropPosition() == i) {
            pawn = addEllipse(x + radius, y, 30, 30, pen, blueBrush);
        } else {
            pawn = addEllipse(x + radius, y, 30, 30, pen, redBrush);
        }

        pawn->setCursor(pointingHandCursor);
        redPawns.push_back(pawn);
    }
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
