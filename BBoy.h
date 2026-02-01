#ifndef BBOY_H
#define BBOY_H

#include "Enemy.h"

namespace DT {
   class BBoy;
}

class DT::BBoy: public Enemy {
   protected: bool _jumping;
   double _prev_x_val;
   Direction fromDirBackup;
   public:

      BBoy(QPointF pos);
   // implemented abstract methods
   virtual std::string name() override {
      return "Beagle Boy[" + std::to_string(_id) + "]";
   }

   // reimplemented abstract methods
   virtual bool hit(Object * what, Direction fromDir) override;
   virtual void advance() override;
   virtual bool animate() override;
   virtual void jump(bool on = true) override;
   virtual void die() override;

};

#endif // BBOY_H