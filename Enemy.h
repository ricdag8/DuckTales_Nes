#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

namespace DT {
   class Enemy;
}

class DT::Enemy: public Entity {
   protected:

      bool _dying;
   bool _dead;
   bool _respawning;
   QPointF _respawningPos;
   QRect _texture_walk[3];

   public:

      Enemy(QPointF pos, double width, double height);

   // getters
   QPixmap * sprite() {
      return _sprite;
   }
   bool dying() {
      return _dying;
   }

   // implemented abstract methods
   virtual bool hit(Object * what, Direction fromDir) override;
   virtual bool animate() override;
   virtual void advance() override;

   // nonimplemented abstract methods
   virtual std::string name() override = 0;
   void respawning();
   // actions
   virtual void die();
};
#endif // ENEMY_H