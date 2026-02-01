#ifndef DYNAMICPLATFORM_H
#define DYNAMICPLATFORM_H

#include "Entity.h"

#include <map>

namespace DT {
   class DynamicPlatform;
}

class DT::DynamicPlatform: public Entity {
   protected:

      std::map < Entity * ,
   Direction > _attached;
   QRect _texture_platform[1];
   public:

      DynamicPlatform(QPointF pos);

   // implemented abstract methods
   virtual void advance() override;
   virtual bool hit(Object * what, Direction fromDir) override;

   // nonimplemented
   virtual bool animate() override {
      return 1;
   };
   virtual std::string name() override {
      return "Platform [" + std::to_string(_id) + "]";;
   }
};

#endif
