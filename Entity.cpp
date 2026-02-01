#include "Entity.h"

#include "StaticObject.h"

#include "Object.h"

#include "Game.h"

#include "Block.h"

#include "Spawnable.h"

#include "CollisionDetection.h"

using namespace DT;
Entity::Entity(QPointF pos, double width, double height):
   Object(pos, width, height) {
      // dynamic objects are compenetrable vs. each other by default
      // (e.g. collectibles vs. enemies)
      _compenetrable = true;
      defaultPhysics();

      // default movement (stand)
      _x_dir = _prev_x_dir = Direction::NONE;
      _vel = {
         0,
         0
      };
      _mirror_x_dir = Direction::NONE;

      _y_dir = _prev_y_dir = Direction::NONE;
      _mirror_x_dir = Direction::NONE;
   }

void Entity::defaultPhysics() {
   _y_gravity = 0.9;
   _y_acc_up = 4;

   _y_vel_max = 2;
   _y_vel_min = 0.01;

   _x_vel_max = 1.6;
   _x_vel_min = 0.01;

   // no accelerations / decelerations along x
   _x_acc = _x_vel_max;
   _x_dec_rel = _x_vel_max;
}

void Entity::velClip(double vx, double vy) {
   _vel.x = std::max(_vel.x, -vx);
   _vel.x = std::min(_vel.x, vx);
   _vel.y = std::max(_vel.y, -vy);
   _vel.y = std::min(_vel.y, vy);
}

void Entity::velClipX(double v) {
   velClip(v, std::numeric_limits < double > ::infinity());
}
void Entity::velClipY(double v) {
   velClip(std::numeric_limits < double > ::infinity(), v);
}
void Entity::velAdd(Vec2Df amount) {
   _vel += amount;

   // max velocity clipping
   velClip(_x_vel_max, _y_vel_max);

   // min velocity clipping
   if (_x_dir == Direction::NONE && std::abs(_vel.x) < _x_vel_min)
      _vel.x = 0;
   if (_y_dir == Direction::NONE && std::abs(_vel.y) < _y_vel_min)
      _vel.y = 0;
}

void Entity::move(Direction dir) {
   if (dir != _x_dir)
      _prev_x_dir = _x_dir;

   if (dir == Direction::RIGHT || dir == Direction::LEFT) {
      _x_dir = dir;
   } else if (dir == Direction::UP || dir == Direction::DOWN) {
      _y_dir = dir;
   } else {
      _x_dir = dir;
      _y_dir = dir;
   }
}

void Entity::jump(bool on) {
   if (on && !midair())
      velAdd(Vec2Df(0, -_y_acc_up));

}

bool Entity::grounded() const {
   return _vel.y == 0 && _prev_vel.y > 0;
}

bool Entity::falling() const {
   return _vel.y > 0 && _prev_vel.y <= 0;
}

bool Entity::midair() const {
   return _vel.y != 0 || (_vel.y == 0 && _prev_vel.y < 0);
}

void Entity::advance() {
   // velocity backup (useful to determine object state)
   _prev_vel = _vel;
   //apply gravity acceleration
   velAdd(Vec2Df(0, _y_gravity));

   // apply horizontal accelerations and decelerations
   if (_x_dir == Direction::RIGHT && _vel.x >= 0)
      velAdd(Vec2Df(_x_acc, 0));
   else if (_x_dir == Direction::LEFT && _vel.x <= 0)
      velAdd(Vec2Df(-_x_acc, 0));
   else if (_x_dir == Direction::NONE)
      velAdd(Vec2Df(-_vel.versX() * _x_dec_rel, 0));
   Scrooge * scrooge = dynamic_cast < Scrooge * > (this);
   if (scrooge && scrooge -> climbing()) {
      if (_y_dir == Direction::UP) {
         scrooge -> setClimbingStill(false);
         velAdd(Vec2Df(0, -_x_acc));
      } else if (_y_dir == Direction::DOWN) {
         scrooge -> setClimbingStill(false);
         velAdd(Vec2Df(0, _x_acc));
      } else if (_y_dir == Direction::NONE) {
         scrooge -> setClimbingStill(true);
         velAdd(Vec2Df(0, -_vel.y));
      }
   }
   // detect and resolve collisions if needed
   if (_collidable)
      resolveCollisions();

   // move
   setX(x() + _vel.x);
   setY(y() + _vel.y);
}

bool Entity::collidableWith(Object * obj) {
   if (obj -> to < StaticObject * > () || obj -> to < Entity * > ()) // Cast dinamico al tipo definito < >? Serve a verificare se può collidere con l'oggetto che gli viene passato
      return true;
   else
      return false;
}

void Entity::resolveCollisions() {
   // simulate next frame pos to get objects within united bounding rect
   QPointF curPos = pos();
   QRectF curRect = qsceneCollider();
   setX(x() + _vel.x);
   setY(y() + _vel.y);
   QList < Object * > likely_collisions;
   QList < QGraphicsItem * > items_in_rect = Game::instance() -> world() -> items(qsceneCollider().united(curRect));
   for (auto item: items_in_rect) {
      Object * obj = dynamic_cast < Object * > (item);
      if (obj && obj -> collidable() && obj != this && collidableWith(obj))
         likely_collisions.push_back(obj);
   }
   setPos(curPos); // restore current pos

   // sort collisions in ascending order of contact time
   Vec2Df cp, cn;
   double ct = 0, min_t = INFINITY;
   std::vector < std::pair < Object * , double >> sortedByContactTime;
   for (auto & obj: likely_collisions)
      if (DynamicRectVsRect(sceneCollider(), vel(), obj -> sceneCollider(), cp, cn, ct))
         sortedByContactTime.push_back({
            obj,
            ct
         });
   std::sort(sortedByContactTime.begin(), sortedByContactTime.end(),
      [this](const std::pair < Object * , double > & a,
         const std::pair < Object * , double > & b) {
         // if contact time is the same, give priority to nearest object
         return a.second != b.second ? a.second < b.second : dist(a.first) < dist(b.first);
      });

   // solve the collisions in correct order
   for (auto obj: sortedByContactTime)
      if (DynamicRectVsRect(sceneCollider(), vel(), obj.first -> sceneCollider(), cp, cn, ct)) {
         if (!obj.first -> compenetrable() || ((obj.first -> isBumper()) && (!(dynamic_cast < Scrooge * > (this)) && !(dynamic_cast < Block * > (this)) && !(dynamic_cast < Spawnable * > (this)))))
            velAdd(cn * Vec2Df(std::abs(_vel.x), std::abs(_vel.y)) * (1 - ct));

         obj.first -> hit(this, normal2dir(cn));
         hit(obj.first, inverse(normal2dir(cn)));
      }
}

void Entity::paint(QPainter * painter) {
   // x-mirroring
   if (_mirror_x_dir != Direction::NONE &&
      (_x_dir == _mirror_x_dir || (_x_dir == Direction::NONE && _prev_x_dir == _mirror_x_dir))) {
      painter -> translate(_boundingRect.width(), 0); // move x origin to right side
      painter -> scale(-1, 1); // mirror x-axis
   }

   Object::paint(painter);
}