#ifndef PINKALIEN_H
#define PINKALIEN_H

#include "Enemy.h"

namespace DT {
class PinkAlien;
}

class DT::PinkAlien: public Enemy {
private:

public:

    PinkAlien(QPointF pos);

    // implemented abstract methods
    virtual std::string name() override {
        return "Pink Alien[" + std::to_string(_id) + "]";
    }

    // reimplemented abstract methods
    virtual bool hit(Object * what, Direction fromDir) override;
    virtual void advance() override;
};

#endif // PINKALIEN_H
