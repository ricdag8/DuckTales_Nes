#include "Gizmoduck.h"

#include "Sprites.h"

#include "Scrooge.h"

#include "GameConfig.h"

#include "Spawnable.h"

using namespace DT;

Gizmoduck::Gizmoduck(QPointF pos, double width, double height): Entity(pos, width, height) {
   _firing = false;
   _activated = false;
   _sprite = Sprites::instance() -> getSprite("gizmoduck");
   Sprites::instance() -> get("gizmoduck-0", & _texture_gizmoduck[0]);
   Sprites::instance() -> get("gizmoduck-1", & _texture_gizmoduck[1]);

}

bool Gizmoduck::animate() {
   if (!_activated) {
      _animRect = & _texture_gizmoduck[Qt::transparent];
   } else {
      _animRect = & _texture_gizmoduck[(FRAME_COUNT / 9) % 2];;
   }
   return 1;
}

bool Gizmoduck::activate() {
   _activated = true;
   _x_dir = Direction::RIGHT;
   schedule("stop", 50, [this] {
      _x_dir = Direction::NONE;
   });
   schedule("fire", 80, [this] {
      firing();
   });
   schedule("backoff", 120, [this] {
      _x_dir = Direction::LEFT;
   });
   schedule("disappear", 200, [this] {
      setVisible(false);
   });

   return 0;
}

void Gizmoduck::firing() {
   Spawnable * projectile = new Spawnable(QPointF(x() + TILE, y() + TILE), TILE / 2, TILE / 2, Spawnable::Type::PROJECTILE);
   projectile -> _y_gravity = 0;
   projectile -> _x_dir = Direction::RIGHT;
}