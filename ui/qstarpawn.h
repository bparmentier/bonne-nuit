/*!
 * \file qstarpawn.h
 * \brief QStarPawn class definition
 */

#ifndef QSTARPAWN_H
#define QSTARPAWN_H

#include <QGraphicsEllipseItem>
#include <QPainter>

/*!
 * \brief A graphical star pawn.
 */
class QStarPawn : public QGraphicsEllipseItem
{
private:
    bool _isStarOn;

public:
    /*!
     * \brief Constructs a QStarPawn with a star using the rectangle defined by
     * (*x*, *y*) and the given *width* and *height*, as the default rectangle.
     * *parent* is passed to QGraphicsEllipseItem's constructor.
     * \param x abscissa of the top-left corner
     * \param y ordinate of the top-left corner
     * \param width width of the bounding rectangle
     * \param height height of the bounding rectangle
     * \param parent parent item
     */
    QStarPawn(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);

    /*!
     * \brief Constructs a QStarPawn with a star if *isStarOn* is `true`, using
     * the rectangle defined by (*x*, *y*) and the given *width* and *height*,
     * as the default rectangle. *parent* is passed to QGraphicsEllipseItem's
     * constructor.
     * \param x abscissa of the top-left corner
     * \param y ordinate of the top-left corner
     * \param width width of the bounding rectangle
     * \param height height of the bounding rectangle
     * \param isStarOn add a star to the QStarPawn if true
     * \param parent parent item
     */
    QStarPawn(qreal x, qreal y, qreal width, qreal height, bool isStarOn, QGraphicsItem *parent = 0);

    /*!
     * \brief Reimplemented from QGraphicsEllipseItem::paint().
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    /*!
     * \brief Set or unset the star of the QStarPawn
     * \param isStarOn set the star if `true`
     */
    void setStarOn(bool isStarOn);
};

#endif // QSTARPAWN_H
