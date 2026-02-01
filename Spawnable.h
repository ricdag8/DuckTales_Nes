#pragma once

#include "Entity.h"

namespace DT {
class Spawnable;
}

class DT::Spawnable: public Entity {
protected: double _value = 0;
    bool taken = 0;
    bool _canFall = 0;
    bool _canFallHit = 0;
    QRect _texture_spawnable[5];
public: bool canFall() {
        return _canFall;
    }
    enum class Type {
        NONE,
        DIAMOND_RED_BIG,
        DIAMOND_YELLOW_BIG,
        DIAMOND_YELLOW_SMALL,
        STAR,
        ICE_CREAM,
        CAKE,
        KEY,
        TREASURE,
        REMOTE,
        PROJECTILE,
        CHEESE
    };Spawnable::Type _type;

    double value() {
        return _value;
    }
    Spawnable(QPointF pos, double width, double height, Spawnable::Type _type, bool canFall = 0);
    void thrownPhysics();
    void setDir(Direction dir) {
        _x_dir = dir;
    }
    // implemented abstract methods
    virtual bool animate() override;
    virtual bool hit(Object * what, Direction fromDir) override;
    virtual std::string name() override {
        return "Spawnable";
    }

    // default spawn and live phases
    //virtual void spawn();
    friend class Gizmoduck;

};
