#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

#include "Object.h"

namespace DT {
class StaticObject;

}
//using Activator = std::function<void()>;

class DT::StaticObject: public Object {
public: enum class Type {
        TERRAIN,
        ROPE,
        SPIKE,
        GATE,
        BUMPER,
        DEATHLINE,
        GREEN_GATE,
        ACTIVATOR,
        RAT_WALL
    };
    enum class Activator {
        FLOOR,
        BOSS,
        GIZMO,
        CAMERA,
        BEAKLEY,
        EVY,
        CLIMBING
    };

protected: QRect _texture_green_gate[1];
    bool _hit;
    bool _activated;
    bool _camera;
public:

    StaticObject(QPointF pos, double width, double height, StaticObject::Type type = StaticObject::Type::TERRAIN);
    StaticObject(QPointF pos, double width, double height, StaticObject::Activator type); //ACTIVATOR CLASS

    // implemented abstract methods
    StaticObject::Activator activator_type;
    StaticObject::Type _type;
    virtual void advance() override {}
    virtual bool animate() override;
    virtual bool hit(Object * what, Direction fromDir) override;
    virtual std::string name() override {
        return "StaticObject";
    }
};

#endif
