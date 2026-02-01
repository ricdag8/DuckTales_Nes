#include "Menu.h"

#include "Game.h"

#include "GameConfig.h"

#include "Sprites.h"

#include <QPainter>

using namespace DT;

Title::Title(): Object(QPoint(0, 0), TILE * 30, TILE * 30) {
    Game::instance() -> world() -> addPixmap(QPixmap(":/sprites/difficulty.png"));
    Game::instance() -> centerOn(0, 0);

    QPixmap fullPixmap = * Sprites::instance() -> getSprite("titleArrow");
    _scrooge_0 = new QGraphicsPixmapItem(fullPixmap.copy(260, 2, 34, 48));
    _scrooge_1 = new QGraphicsPixmapItem(fullPixmap.copy(260, 52, 34, 48));
    _scrooge_0 -> setPos(QPoint(4.5 * TILE - 2, 1.5 * TILE - 3));
    _scrooge_1 -> setPos(QPoint(4.5 * TILE - 2, 1.5 * TILE - 3));
    _scrooge_1 -> setVisible(false);
    Game::instance() -> world() -> addItem(_scrooge_0);
    Game::instance() -> world() -> addItem(_scrooge_1);
    _arrow = new Arrow(QPoint(32, 129), 5, 8, Arrow::Type::HORIZONTAL);
    setZValue(1);
}

void Title::advance() {
    return;
}

bool Title::animate() {
    if (((FRAME_COUNT / 9) % 9) == 0) {
        _scrooge_1 -> setVisible(true);
    } else {
        _scrooge_1 -> setVisible(false);

    }
    return true;
}

Level::Level(): Object(QPoint(0, 0), TILE * 30, TILE * 30) {
    QPixmap fullPixmap = * Sprites::instance() -> getSprite("level");
    QPixmap croppedPixmap = fullPixmap.copy(0, 0, 256, 224);

    QGraphicsPixmapItem * Louie = new QGraphicsPixmapItem(fullPixmap.copy(25, 226, 17, 22));
    QGraphicsPixmapItem * Hewey = new QGraphicsPixmapItem(fullPixmap.copy(45, 226, 17, 22));
    QGraphicsPixmapItem * Dewey = new QGraphicsPixmapItem(fullPixmap.copy(65, 226, 17, 22));
    iconLeft = new QGraphicsPixmapItem(fullPixmap.copy(262, 154, 14, 10));
    iconRight = new QGraphicsPixmapItem(fullPixmap.copy(262, 154, 14, 10));

    Louie -> setPos(QPoint(9 * TILE, 12.3 * TILE));
    Hewey -> setPos(QPoint(10 * TILE + 1, 12.3 * TILE));
    Dewey -> setPos(QPoint(12.5 * TILE, 11.3 * TILE)); // nel gioco originale questo non c'è, ci sono 2 Louie: non si può guardare dai

    iconLeft -> setPos(QPoint(42, 139));
    iconRight -> setPos(QPoint(202, 139));

    Game::instance() -> world() -> addPixmap(croppedPixmap);
    Game::instance() -> world() -> addItem(Louie);
    Game::instance() -> world() -> addItem(Hewey);
    Game::instance() -> world() -> addItem(Dewey);
    Game::instance() -> world() -> addItem(iconLeft);
    Game::instance() -> world() -> addItem(iconRight);

    _mapArrow = new Arrow(QPoint(10 * TILE + 1, 2.5 * TILE), 8, 8, Arrow::Type::VERTICAL);
    _arrow = new Arrow(QPoint(4.5 * TILE + 1, 8.5 * TILE + 1), 5, 8, Arrow::Type::HORIZONTAL);

}

void Level::advance() {
    if (_arrow -> _pos != 0) {
        iconLeft -> setVisible(false);
        iconRight -> setVisible(false);
        _mapArrow -> setVisible(false);
    } else {
        iconLeft -> setVisible(true);
        iconRight -> setVisible(true);
        _mapArrow -> setVisible(true);
    }
    return;
}

bool Level::animate() {
    return true;
}

//Arrow::Arrow() : Object(QPoint(32, 129), 5, 8)
Arrow::Arrow(QPointF pos, double width, double height, Type type): Object(pos, width, height) {
    _type = type;
    _pos = 0;
    prev_pos = 0;
    if (type == Type::HORIZONTAL) {
        _sprite = Sprites::instance() -> getSprite("titleArrow");
        Sprites::instance() -> get("title-arrow", & _anim[0]);
        _animRect = & _anim[0];
    } else if (type == Type::VERTICAL) {
        _sprite = Sprites::instance() -> getSprite("level");
        Sprites::instance() -> get("level-arrow-0", & _anim[0]);
        Sprites::instance() -> get("level-arrow-1", & _anim[1]);
    }
}

void Arrow::advance() {
    int newPos = Game::instance() -> arrowPos();
    if (_type == Type::HORIZONTAL) {
        if (Game::instance() -> state() == Game::GameState::TITLE_SCREEN) {
            if (prev_pos == newPos) {
                return;
            } else {
                if (newPos == 2 || _pos == 2) {
                    setPos((x() + (newPos - _pos) * TILE * 4), y());
                } else {
                    setPos((x() + (newPos - _pos) * TILE * 3), y());
                }
                prev_pos = _pos;
                _pos = newPos;
            }
        } else if (Game::instance() -> state() == Game::GameState::LEVEL_SELECTION) {
            if (prev_pos == newPos) {
                return;
            } else {
                setPos(x(), y() - (newPos - _pos) * TILE / 2);
                prev_pos = _pos;
                _pos = newPos;
            }
        }
    }
}

bool Arrow::animate() {
    if (_type == Type::VERTICAL) {
        _animRect = & _anim[(FRAME_COUNT / 9) % 2];
    }
    return true;
}
