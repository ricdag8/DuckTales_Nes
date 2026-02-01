#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"

// Entity are objects that can move!
namespace DT {
   class Entity;
}
class DT::Entity: public Object {
   protected:
      // physics parameters (expressed in pixels/frame unit)
      double _y_gravity; // downwards vertical acceleration due to gravity
   double _y_acc_up; // upwards vertical acceleration (e.g. jump force)
   double _x_acc; // horizontal acceleration due to movement
   double _x_dec_rel;
   double _x_vel_max; // maximum horizontal velocity
   double _x_vel_min; // minimum horizontal velocity
   double _y_vel_max; // maximum vertical velocity
   double _y_vel_min; // minimum vertical velocity

   // attributes
   Direction _x_dir; // current horizontal movement direction
   Direction _prev_x_dir; // previous horizontal movement direction
   Direction _mirror_x_dir; // direction that needs animation mirroring
   Direction _y_dir; // current vertical movement direction
   Direction _prev_y_dir; // previous vertical movement direction
   Direction _mirror_y_dir; // direction that needs animation mirroring
   Vec2Df _vel; // current velocity
   Vec2Df _prev_vel; // velocity in the previous frame
   // collision detection/resolution
   virtual bool collidableWith(Object * obj);
   void resolveCollisions();

   public: Entity(QPointF pos, double width, double height);
   Vec2Df vel() const {
      return _vel;
   }
   void velAdd(Vec2Df amount);
   void velClip(double vx, double vy);
   void velClipX(double v);
   void velClipY(double v);

   // state queries
   bool skidding() const;
   bool grounded() const;
   bool falling() const;
   virtual bool midair() const;

   // actions
   virtual void move(Direction dir);
   virtual void jump(bool on = true);

   // game physics
   virtual void advance() override;
   virtual void defaultPhysics();

   // nonimplemented abstract methods
   virtual bool animate() override = 0;
   virtual bool hit(Object * what, Direction fromDir) override = 0;
   virtual std::string name() override = 0;

   virtual void paint(QPainter * painter) override;

};

#endif // ENTITY_H
