#include "Enemy.h"

#include "GameConfig.h"

#include "Scrooge.h"

#include "StaticObject.h"

#include "Block.h"

#include "Game.h"

#include "Rat.h"

#include "PinkAlien.h"

#include "Octopus.h"

#include "BBoy.h"

#include "Sounds.h"

using namespace DT;

Enemy::Enemy(QPointF pos, double width, double height): Entity(pos, width, height) {
   _collider.adjust(3, 3, -3, -1);
   _respawning = false;
   _dying = false;
   _dead = false;
   _respawningPos = pos;
   _mirror_x_dir = Direction::LEFT;

}

bool Enemy::hit(Object * what, Direction fromDir) {
   Scrooge * scrooge = what -> to < Scrooge * > ();
   if (scrooge && !(fromDir == Direction::UP && scrooge -> pogoing())) // Da aggiungere condizione su invincibilità, vedi stessa funzione in Enemy su BubbleBobble
   {
      if (!scrooge -> invincibile()) {
         scrooge -> lifeDown();

         return true;

      }
   }
   /*
       else if(scrooge && scrooge->pogoing() && fromDir == Direction::UP){
           die();

           scrooge->_y_acc_up;
           return true;
       }*/
   else if (what -> to < StaticObject * > () && _dying) // && fromDir == Direction::DOWN
   {
      //setVisible(false);
      // spawn item
      // schedule respawn?
      return true;
   }

   return false;
}

bool Enemy::animate() {
   if (_dying)
      _animRect = & _texture_walk[1];
   else
      _animRect = & _texture_walk[(FRAME_COUNT / 9) % 2];

   return 1;
}

void Enemy::advance() {
   Entity::advance();
   if (!dynamic_cast < Rat * > (this) && !dynamic_cast < BBoy * > (this) && _dead && !_respawning) { // Rat non deve respawnare, BBoy hanno un'altra logica di respawning
      _respawning = false;
      respawning();
   }
}

void Enemy::respawning() {
   if ((abs(Game::instance() -> player() -> x() - x()) > Game::instance() -> width() / 2) ||
      (abs(Game::instance() -> player() -> y() - y()) > Game::instance() -> height() / 2)) {
      _collidable = true;
      _dead = false;
      defaultPhysics();

      setVisible(true);
      if (dynamic_cast < PinkAlien * > (this) || (dynamic_cast < Octopus * > (this) && dynamic_cast < Octopus * > (this) -> type() == Direction::RIGHT)) {
         _y_gravity = 0;
         move(Direction::RIGHT);
      } else {
         _y_acc_up = 0.1;
         _y_vel_max = 1;
         move(Direction::UP);
      }
   } else {
      _respawning = false;
   }
}

void Enemy::die() {
   Sounds::instance() -> play("enemydie");
   _respawningPos = pos();
   _dying = true; // Blocco l'animazione per i pochi frame che nemico sale verso l'alto durante la morte
   _collidable = false;
   schedule("die", 45, [this]() {
      setVisible(false);
      if (!dynamic_cast < Rat * > (this) && !dynamic_cast < BBoy * > (this)) {
         setPos(_respawningPos);
      }
      _y_gravity = 0;
      _vel = {
         0,
         0
      };
      _y_dir = Direction::NONE;
      _x_dir = Direction::NONE;
      _dying = false;
      _dead = true;
   });
   _y_dir = Direction::DOWN;
   _y_gravity = 0.15;
   _vel.x = 0.3;

   setY(y() - 17);
   _y_acc_up = 2;
   _y_vel_max = 3;
   _x_vel_max = 3;
   _x_vel_min = 0.01;
}