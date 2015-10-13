#include "qstarpawn.h"
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

QStarPawn::QStarPawn(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
    QStarPawn(x, y, width, height, true, parent)
{
}

QStarPawn::QStarPawn(qreal x, qreal y, qreal width, qreal height, bool isStarOn, QGraphicsItem *parent) :
    QGraphicsEllipseItem(x, y, width, height, parent),
    _isStarOn(isStarOn)
{
}

void QStarPawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);

    if (_isStarOn) {
        QSvgRenderer *renderer = new QSvgRenderer(QString(":/resources/star.svg"));
        QGraphicsSvgItem *star = new QGraphicsSvgItem();
        star->setSharedRenderer(renderer);
        renderer->render(painter, boundingRect());
    }
}

void QStarPawn::setStarOn(bool isStarOn)
{
    _isStarOn = isStarOn;
    update(boundingRect());
}
