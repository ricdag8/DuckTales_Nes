#pragma once


#include "Spawnable.h"

namespace DT {
   class Block;
}

class DT::Block: public Entity {

   protected:

      QPointF _pos;

   bool _bouncing;
   bool _disabled;
   bool _spawned;
   bool _launched;
   bool _breakable;
   bool _collided;
   bool _brick_breakable;
   bool _invisible;
   bool _enemy_hit;
   bool _block_hit;
   QRect _texture_block[3];
   QRect _texture_broken_block[2];
   QRect _texture_battery[1];
   QRect _texture_chest_big[1];
   QRect _texture_chest_small[1];
   QRect _texture_block_hit[1];

   Spawnable::Type _spawnable;

  

   public:

      enum class Type {
         BRICK,
         SPHERE,
         QUESTION,
         HIDDEN,
         CHEST_BIG,
         CHEST_SMALL,
         BATTERY
      };
   Block::Type _type;

   Block(
      QPointF pos,
      double width,
      double height,
      Block::Type _type,
      bool invisible = false,
      Spawnable::Type spawnable = Spawnable::Type::NONE);
   virtual bool animate() override;

   //virtual bool midair() const override;
   virtual std::string name() override {
      return "Block";
   }
   virtual bool hit(Object * what, Direction fromDir) override;

};
