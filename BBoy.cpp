#include "BBoy.h"

#include "Sprites.h"

#include "Game.h"

#include "GameConfig.h"

#include "StaticObject.h"

#include "Scrooge.h"

using namespace DT;

BBoy::BBoy(QPointF pos): Enemy(pos, 25, 32) {
   _jumping = false;
   _sprite = Sprites::instance() -> getSprite("beagleBoy");
   _x_dir = Direction::RIGHT;
   _y_vel_max = 3;
   _x_vel_max = 0.7;
   _y_gravity = 0.09;
   Sprites::instance() -> get("beagleBoy-0", & _texture_walk[0]);
   Sprites::instance() -> get("beagleBoy-1", & _texture_walk[1]);
   Sprites::instance() -> get("beagleBoy-1", & _texture_walk[2]);
}

void BBoy::advance() {

   Scrooge * player = Game::instance() -> player();
   if (abs(player -> x() - x()) >= (Game::instance() -> width()) / 2 && player -> y() >= 75 * TILE) {
      setVisible(false);
      Game::instance() -> setBeagleStatus(false);
   }

   if (x() == _prev_x_val && !midair()) { 
      jump();
   }

   if ((FRAME_COUNT % 9 == 0)) { 
      _prev_x_val = x();
   }

   Entity::advance();
}

bool BBoy::animate() {
   _animRect = & _texture_walk[(FRAME_COUNT / 9) % 3];
   return 1;
}

bool BBoy::hit(Object * what, Direction fromDir) {

   if (Enemy::hit(what, fromDir))
      return true;

   if (what -> to < StaticObject * > () && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT)) {
      fromDirBackup = fromDir;
      jump();

      return true;
   }

   return false;
}

void BBoy::jump(bool on) {

   if (on) {
      velAdd(Vec2Df(0, -2.5));
      _jumping = true;
   };
}

void BBoy::die() {
   Enemy::die();
   Game::instance() -> setBeagleStatus(false);
}