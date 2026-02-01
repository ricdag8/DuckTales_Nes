#include "Block.h"

#include "Sprites.h"

#include "Scrooge.h"

#include "Sounds.h"

#include "Enemy.h"

#include "Spawnable.h"

#include "Game.h"

#include "StaticObject.h"

using namespace DT;

Block::Block(QPointF pos, double width, double height, Block::Type type, bool invisible, Spawnable::Type spawnable): Entity(pos, width, height) {
   _pos = pos;
   _type = type;
   _invisible = invisible;
   _breakable = false;
   _launched = false;
   _collided = false;
   _compenetrable = false;
   _spawnable = spawnable;
   _block_hit = false; //gestisco l'animazione della collisione tra due blocchi
   _enemy_hit = false; //gestisco l'animazione per la collisione tra nemici;
   _sprite = Sprites::instance() -> getSprite("block");

   if (_type == Type::BRICK) {

      Sprites::instance() -> get("block-0", & _texture_block[0]);
      Sprites::instance() -> get("block-1", & _texture_block[1]);
      Sprites::instance() -> get("block-broken-0", & _texture_broken_block[0]);
      Sprites::instance() -> get("block-broken-1", & _texture_broken_block[1]);
      Sprites::instance() -> get("block-hit-0", & _texture_block_hit[0]);
      _animRect = & _texture_block[0];
   } else if (_type == Type::CHEST_BIG) {

      Sprites::instance() -> get("chest-big-0", & _texture_chest_big[0]);
      Sprites::instance() -> get("block-broken-0", & _texture_broken_block[0]);
      Sprites::instance() -> get("block-broken-1", & _texture_broken_block[1]);
      _animRect = & _texture_chest_big[0];
   } else if (_type == Type::CHEST_SMALL) {
      Sprites::instance() -> get("chest-small-0", & _texture_chest_small[0]);
      Sprites::instance() -> get("block-broken-0", & _texture_broken_block[0]);
      Sprites::instance() -> get("block-broken-1", & _texture_broken_block[1]);
      _animRect = & _texture_chest_small[0];

      if (_invisible) {
         //setVisible(false);
         _compenetrable = true;
      } else {
         setVisible(true);
         _compenetrable = false;
      }
   } else if (_type == Type::SPHERE) {
      Sprites::instance() -> get("sphere-0", & _texture_block[0]);
      Sprites::instance() -> get("block-broken-0", & _texture_broken_block[0]);
      Sprites::instance() -> get("block-broken-1", & _texture_broken_block[1]);
      Sprites::instance() -> get("block-hit-0", & _texture_block_hit[0]);
      _animRect = & _texture_block[0];
   } else if (_type == Type::BATTERY) {
      Sprites::instance() -> get("battery-0", & _texture_block[0]);
      _animRect = & _texture_block[0];
   }

   setZValue(1);
   _y_gravity = 0;

}

bool Block::hit(Object * what, Direction fromDir) {
   Scrooge * scrooge = what -> to < Scrooge * > ();
   Enemy * enm = what -> to < Enemy * > ();
   StaticObject * sobj = what -> to < StaticObject * > ();
   Block * block = what -> to < Block * > ();

   if (scrooge && fromDir == Direction::UP && scrooge -> pogoing() && _type != Type::BATTERY) {
      _collidable = false;
      _breakable = true; //utilizzo breakable per gestire le interazioni con pogoing ---> è broken non breakable...
      schedule("disappear", 20, [this]() {
         setVisible(false);
      });
      if (_type == Type::BRICK && chanceCalculator(0.05)) { // 5% di possibilità di spawnare
         new Spawnable(this -> pos(), TILE, TILE, _spawnable);
      } else if (_type == Type::CHEST_SMALL || _type == Type::CHEST_BIG) {
         new Spawnable(this -> pos(), TILE, TILE, _spawnable);
      }
      this -> setZValue(3);
   }

   if (scrooge && _type == Type::CHEST_SMALL) {
      if (_invisible) {
         setVisible(true);
         _compenetrable = false;
         _invisible = false; // metto invisible a false così puo diventare visible
      }
   }

   if (_type == Type::BATTERY) {

   }

   if (scrooge && scrooge -> swinging()) {
      if (_type == Type::BATTERY) {
         if (fromDir == Direction::LEFT) {
            _x_dir = Direction::RIGHT;
            _y_acc_up = 0;

         }
         if (fromDir == Direction::RIGHT) {
            _x_dir = Direction::LEFT;
            _y_acc_up = 0;
            velAdd(Vec2Df(-20, 0));
         }
      }
      if (_type == Type::CHEST_SMALL) {
         if (fromDir == Direction::LEFT) {
            _x_dir = Direction::RIGHT;
            _y_acc_up = 0;
            velAdd(Vec2Df(20, 0));
         }
         if (fromDir == Direction::RIGHT) {
            _x_dir = Direction::LEFT;
            _y_acc_up = 0;
            velAdd(Vec2Df(-20, 0));
         }
      }

      if (_type == Type::SPHERE) {
         if (fromDir == Direction::LEFT) {
            _x_dir = Direction::RIGHT;
            _y_acc_up = 0;
            velAdd(Vec2Df(10, -10));
         }
         if (fromDir == Direction::RIGHT) {
            _x_dir = Direction::LEFT;
            _y_acc_up = 0;
            velAdd(Vec2Df(-10, -10));
         }

      }
      if (_type == Type::CHEST_BIG) {
         schedule("disappear", 30, [this]() {
            setVisible(false);
         });
      }

      if (_type == Type::BRICK) {
         if (fromDir == Direction::LEFT) {
            velAdd(Vec2Df(0.15, -3));
            _x_dir = Direction::RIGHT;
            _y_gravity = 0.13;
            _compenetrable = true;
            schedule("disappear", 30, [this]() {
               setVisible(false);
            });
         }
         if (fromDir == Direction::RIGHT) {
            velAdd(Vec2Df(-0.15, -3));
            _x_dir = Direction::LEFT;
            _y_gravity = 0.13;
            _compenetrable = true;
            schedule("disappear", 30, [this]() {
               setVisible(false);
            });
         }

         _launched = true; //launched  serve per gestire le animazioni di brick quando viene hittato da scrooge
      }

   }

   if (enm && this -> midair()) {
      this -> move(Direction::NONE);
      schedule("disappear", 4, [this]() {

         setVisible(false);
      });

      enm -> die();
      Sounds::instance() -> play("enemydie");
      _enemy_hit = true;
   }

   if (sobj && fromDir == Direction::UP && sobj -> _type != StaticObject::Type::BUMPER) {
      move(Direction::NONE);
      _compenetrable = false;
      _breakable = true;
      schedule("disappear", 8, [this]() {

         setVisible(false);

      });
   }
   if (sobj && sobj -> _type == StaticObject::Type::BUMPER && (fromDir == Direction::DOWN || fromDir == Direction::LEFT || fromDir == Direction::RIGHT)) {
      _compenetrable = true;
   }
   if (sobj && _type == Type::BRICK && fromDir == Direction::DOWN) {
      move(Direction::NONE);
   }

   /* if (block)  // da implementare le collisioni tra due blocchi. se si toccano solamente quello lanciato da scrooge deve rompersi. se collidano, il blocco deve essere non compenetrable e deve rompersi subito, attivo _breakable=true
//da gestire anche la collisione tra battery e brick
    {

    }*/

   return true;
}

bool Block::animate() {

   if (_type == Type::CHEST_SMALL && _invisible) {
      _animRect = & _texture_chest_small[Qt::transparent];
   } else if (_type == Type::CHEST_SMALL && !_invisible) {
      schedule("startAnimation", 15, [this]() {
         // Questo blocco di codice sarà eseguito dopo l'intervallo di tempo specificato (1 secondo)
         _animRect = & _texture_chest_small[0];

      }, false);

   }

   if ((_type == Type::SPHERE || _type == Type::BRICK || _type == Type::CHEST_BIG || _type == Type::CHEST_SMALL) && _breakable == true) {

      _animRect = & _texture_broken_block[(FRAME_COUNT / 10) % 2];
   }

   if (_launched && _type == Type::BRICK) {
      if (_vel.y < 0)
         _animRect = & _texture_block[1];
      else if (_vel.y > 0)
         _animRect = & _texture_broken_block[(FRAME_COUNT / 9) % 2];
   }

   if ((_type == Type::BRICK || _type == Type::SPHERE) && _enemy_hit) {
      _animRect = & _texture_block_hit[0];
   }

   
   return true;
}