#ifndef QSTARPAWN_H
#define QSTARPAWN_H

#include <QGraphicsEllipseItem>
#include <QPainter>

class QStarPawn : public QGraphicsEllipseItem
{
private:
    bool _isStarOn;

public:
    QStarPawn(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
    QStarPawn(qreal x, qreal y, qreal width, qreal height, bool _isStarOn, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setStarOn(bool isStarOn);
};

#endif // QSTARPAWN_H
