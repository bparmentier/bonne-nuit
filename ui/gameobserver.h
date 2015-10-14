/*!
 * \file gameobserver.h
 * \brief GameObserver class definition
 */

#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSvgItem>

#include "o_sdo/observateur.h"
#include "business/game.h"
#include "qstarpawn.h"

class Game;

/*!
 * \brief A graphical representation of the game
 */
class GameObserver : public QGraphicsScene, public Observateur
{
    Q_OBJECT

private:
    static const int KEY_RED_PAWN_INDICE = 0x0;
    static const int KEY_STAR_PAWN_INDICE = 0x1;
    static const int KEY_TYPE_RED_PAWN = 0x2;
    static const int KEY_TYPE_STAR_PAWN = 0x3;

    Game *_game;
    std::vector<QGraphicsEllipseItem *> redPawns;
    std::vector<std::vector<QStarPawn *>> starPawns;
    QGraphicsSvgItem *drop;
    QGraphicsTextItem *currentPlayerInfo;
    QBrush background;

    void drawPawns(float xcenter, float ycenter, float radius, unsigned pawnNumber);
    void drawStarPawns(float xcenter, float ycenter, float radius, unsigned pawnNumber, unsigned redPawnIndex);
    void updateRedPawns();
    void updateStarPawns();
    void updateBackground();
    void setupCurrentPlayerInfo();
    void setCurrentPlayerInfoText();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    /*!
     * \brief Constructs a game observer with the given *game*. *parent* is
     * passed to QGraphicsScene's constructor.
     * \param game the game
     * \param parent the parent widget
     */
    GameObserver(Game *game, QWidget *parent = 0);

    /*!
     * \brief Destroys the game observer
     */
    ~GameObserver();

    /*!
     * \brief Refresh the observer when the game state changes
     * \param sdo the subject
     */
    void rafraichir(SujetDObservation *sdo);

signals:
    void statusEvent(const QString &);
};

#endif // GAMEOBSERVER_H
