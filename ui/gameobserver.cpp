#include "gameobserver.h"
#include "mainwindow.h"
#include "qstarpawn.h"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

GameObserver::GameObserver(Game *game, QWidget *parent) :
    QGraphicsScene{parent},
    _game{game},
    background{QBrush(QPixmap(":/resources/background_texture.png"))}
{
    _game->attacher(this);
    setBackgroundBrush(background);
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
    if (_game->gameState() == GameState::SECOND_STAGE
            || _game->gameState() == GameState::OVER) {
        updateBackground();
    }
    updateRedPawns();
    updateStarPawns();
}

void GameObserver::drawPawns(float xcenter, float ycenter, float radius,
                             unsigned pawnNumber)
{
    int x, y;
    float angle;
    int pawnDiameter = 40;

    QPen pen{QPen(Qt::black)};
    QBrush redBrush{QBrush(QColor(Qt::red))};
    drop = new QGraphicsSvgItem(":/resources/drop.svg");
    drop->setScale(0.155);

    for (unsigned i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius - (pawnDiameter / 2);
        y = ycenter + sinf(angle) * radius - (pawnDiameter / 2);
        QGraphicsEllipseItem *pawn;
        pawn->setData(123, i);
        pawn = addEllipse(0, 0, pawnDiameter, pawnDiameter, pen, redBrush);
        pawn->setPos(x, y);
        if (_game->dropPosition() == i) {
            drop->setPos(x, y);
        }

        redPawns.push_back(pawn);

        drawStarPawns(x + (pawnDiameter / 2), y + (pawnDiameter / 2), 40, 5, i);
    }
    addItem(drop);
}

void GameObserver::drawStarPawns(float xcenter, float ycenter,
                                 float radius, unsigned pawnNumber,
                                 unsigned redPawnIndex)
{
    int x, y;
    float angle;
    int pawnDiameter = 30;

    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};
    std::vector<QStarPawn *> pawnGroup;

    for (unsigned i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius - pawnDiameter / 2;
        y = ycenter + sinf(angle) * radius - pawnDiameter / 2;
        Piece piece = _game->board().at(redPawnIndex).at(i);
        QStarPawn *pawn = new QStarPawn(0, 0, pawnDiameter, pawnDiameter);
        pawn->setPos(x, y);

        switch (piece.color()) {
        case Color::BLACK:
            pawn->setBrush(QBrush(QColor(Qt::black)));
            break;
        case Color::BLUE:
            pawn->setBrush(QBrush(QColor(Qt::blue)));
            break;
        case Color::GREEN:
            pawn->setBrush(QBrush(QColor(Qt::green)));
            break;
        case Color::PURPLE:
            pawn->setBrush(QBrush(QColor(Qt::darkMagenta)));
            break;
        case Color::RED:
            pawn->setBrush(QBrush(QColor(Qt::red)));
            break;
        default:
            pawn->setStarOn(false);
            pawn->setBrush(Qt::NoBrush);
        }

        pawn->setData(KEY_RED_PAWN_INDICE, redPawnIndex);
        pawn->setData(KEY_STAR_PAWN_INDICE, i);
        pawn->setCursor(pointingHandCursor);
        addItem(pawn);
        pawnGroup.push_back(pawn);
    }
    starPawns.push_back(pawnGroup);
}

void GameObserver::updateRedPawns()
{
    unsigned dropPosition = _game->dropPosition();

    for (unsigned i = 0; i < 9; ++i) {
        QGraphicsEllipseItem *pawn = redPawns.at(i);
        if (dropPosition == i) {
            drop->setPos(pawn->pos());
        }
    }
}

void GameObserver::updateStarPawns()
{
    for (unsigned redPawnIndice = 0; redPawnIndice < 9; ++redPawnIndice) {
        for (unsigned starPawnIndice = 0; starPawnIndice < 5; ++starPawnIndice) {
            Piece piece = _game->board().at(redPawnIndice).at(starPawnIndice);
            QStarPawn *pawn = starPawns.at(redPawnIndice).at(starPawnIndice);

            if (_game->isLightOn()) {
                if (_game->gameState() == GameState::OVER) {
                    int line = _game->lastPawnCoordinates().first;
                    int column = _game->lastPawnCoordinates().second;

                    if (static_cast<int>(redPawnIndice) == line
                            && static_cast<int>(starPawnIndice) == column) {
                        pawn->setStarOn(true);
                    }
                } else {
                    if (piece.color() != Color::EMPTY) {
                        pawn->setStarOn(true);
                    }
                }
                switch (piece.color()) {
                case Color::BLACK:
                    pawn->setBrush(QBrush(QColor(Qt::black)));
                    break;
                case Color::BLUE:
                    pawn->setBrush(QBrush(QColor(Qt::blue)));
                    break;
                case Color::GREEN:
                    pawn->setBrush(QBrush(QColor(Qt::green)));
                    break;
                case Color::PURPLE:
                    pawn->setBrush(QBrush(QColor(Qt::darkMagenta)));
                    break;
                case Color::RED:
                    pawn->setBrush(QBrush(QColor(Qt::red)));
                    break;
                default:
                    pawn->setBrush(Qt::NoBrush);
                }
                pawn->setPen(QPen(Qt::black));
            } else {
                if (piece.isGlowingInTheDark()) {
                    pawn->setStarOn(true);
                    pawn->setBrush(QBrush(QColor(Qt::black)));
                    pawn->setPen(QPen(Qt::white));
                } else {
                    pawn->setStarOn(false);
                }
            }
        }
    }

}

void GameObserver::updateBackground()
{
    if (!_game->isLightOn()) {
        setBackgroundBrush(QBrush(QColor(Qt::black)));
    } else {
        setBackgroundBrush(background);
    }
}

void GameObserver::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    QGraphicsItem *item = itemAt(event->lastScenePos().x(),
                                 event->lastScenePos().y(),
                                 QTransform());

    bool isRedPawnIndiceEmpty = item->data(KEY_RED_PAWN_INDICE).toString().isEmpty();
    bool isStarPawnIndiceEmpty = item->data(KEY_STAR_PAWN_INDICE).toString().isEmpty();

    if (_game->gameState() == GameState::FIRST_STAGE) {
        if (!isRedPawnIndiceEmpty && !isStarPawnIndiceEmpty) {
            unsigned redPawnIndice = item->data(KEY_RED_PAWN_INDICE).toInt();
            if (redPawnIndice == _game->dropPosition()) {
                try {
                    _game->placePiece(item->data(KEY_STAR_PAWN_INDICE).toInt());
                } catch (std::runtime_error const &e) {
                    statusEvent(e.what());
                } catch (std::invalid_argument const &e) {
                    statusEvent(e.what());
                }
            }
        }
    }
    if (_game->gameState() == GameState::SECOND_STAGE) {
        if (!isRedPawnIndiceEmpty && !isStarPawnIndiceEmpty) {
            int redPawnIndice = item->data(KEY_RED_PAWN_INDICE).toInt();
            int starPawnIndice = item->data(KEY_STAR_PAWN_INDICE).toInt();

            try {
                _game->reversePiece(redPawnIndice, starPawnIndice);
            } catch (std::runtime_error const &e) {
                statusEvent(e.what());
            } catch (std::invalid_argument const &e) {
                statusEvent(e.what());
            }

        }
    }
}
