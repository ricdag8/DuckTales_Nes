#include "PinkAlien.h"

#include "Sprites.h"

#include "Game.h"

#include "GameConfig.h"

#include "StaticObject.h"

#include "Scrooge.h"

using namespace DT;

PinkAlien::PinkAlien(QPointF pos): Enemy(pos, 32, 35) {
    _sprite = Sprites::instance() -> getSprite("pinkAlien");
    _x_dir = Direction::RIGHT;
    _mirror_x_dir = Direction::LEFT;

    Sprites::instance() -> get("pink-alien-0", & _texture_walk[0]);
    Sprites::instance() -> get("pink-alien-1", & _texture_walk[1]);
}

void PinkAlien::advance() { // Does nothing?
    Enemy::advance();
}

bool PinkAlien::hit(Object * what, Direction fromDir) {

    if (Enemy::hit(what, fromDir))
        return true;

    if (what -> to < StaticObject * > () && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT)) {
        move(inverse(_x_dir));

        return true;
    }

    return false;
}
