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

    if (_game->gameState() == GameState::SECOND_STAGE) {

    }
    updateRedPawns();
    updateStarPawns();
    if (!_game->isLightOn()) {

    }
}

void GameObserver::drawPawns(float xcenter, float ycenter, float radius, int pawnNumber)
{
    int x, y;
    float angle;
    int pawnDiameter = 40;

    QPen pen{QPen(Qt::black)};
    QBrush redBrush{QBrush(QColor(Qt::red))};
    QBrush blueBrush{QBrush(QColor(Qt::blue))};
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius - (pawnDiameter / 2);
        y = ycenter + sinf(angle) * radius - (pawnDiameter / 2);
        QGraphicsEllipseItem *pawn;
        pawn->setData(123, i);
        if (_game->dropPosition() == i) {
            pawn = addEllipse(x, y, pawnDiameter, pawnDiameter, pen, blueBrush);
        } else {
            pawn = addEllipse(x, y, pawnDiameter, pawnDiameter, pen, redBrush);
        }

        redPawns.push_back(pawn);

        drawStarPawns(x + (pawnDiameter / 2), y + (pawnDiameter / 2), 40, 5, i);
    }

    addEllipse(0, 0, 2, 2);
}

void GameObserver::drawStarPawns(float xcenter, float ycenter,
                                 float radius, int pawnNumber, int redPawnIndex)
{
    int x, y;
    float angle;
    int pawnDiameter = 30;

    QPen pen{QPen(Qt::black)};
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};
    std::vector<QGraphicsEllipseItem *> pawnGroup;

    for (auto i = 0; i < pawnNumber; i++) {
        angle = i * (2.0f * M_PI / pawnNumber);
        x = xcenter + cosf(angle) * radius - pawnDiameter / 2;
        y = ycenter + sinf(angle) * radius - pawnDiameter / 2;
        Piece piece = _game->board().at(redPawnIndex).at(i);
        QGraphicsEllipseItem *pawn = addEllipse(x, y, pawnDiameter, pawnDiameter);
        pawn->setData(KEY_RED_PAWN_INDICE, redPawnIndex);
        pawn->setData(KEY_STAR_PAWN_INDICE, i);

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

        pawn->setCursor(pointingHandCursor);
        pawnGroup.push_back(pawn);
    }
    starPawns.push_back(pawnGroup);
}

void GameObserver::updateRedPawns()
{
    QBrush redBrush{QBrush(QColor(Qt::red))};
    QBrush blueBrush{QBrush(QColor(Qt::blue))};
    unsigned dropPosition = _game->dropPosition();

    for (auto i = 0; i < 9; ++i) {
        QGraphicsEllipseItem *pawn = redPawns.at(i);
        pawn->setBrush((i == dropPosition) ? blueBrush : redBrush);
    }
}

void GameObserver::updateStarPawns()
{
    for (auto redPawnIndice = 0; redPawnIndice < 9; ++redPawnIndice) {
        for (auto starPawnIndice = 0; starPawnIndice < 5; ++starPawnIndice) {

            Piece piece = _game->board().at(redPawnIndice).at(starPawnIndice);
            QGraphicsEllipseItem *pawn = starPawns.at(redPawnIndice).at(starPawnIndice);

            if (piece.isStarOn()) {
                pawn->setBrush(QBrush(QColor(Qt::black)));
                pawn->setPen(QPen(Qt::white));
            } else {
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
            }
        }
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
            int redPawnIndice = item->data(KEY_RED_PAWN_INDICE).toInt();
            if (redPawnIndice == _game->dropPosition()) {
                try {
                    _game->placePiece(item->data(KEY_STAR_PAWN_INDICE).toInt());
                } catch (std::runtime_error const &e) {
                    throw e;
                } catch (std::invalid_argument const &e) {
                    throw e;
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
                throw e;
            } catch (std::invalid_argument const &e) {
                throw e;
            }

        }
    }
}
