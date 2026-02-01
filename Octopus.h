#ifndef OCTOPUS_H
#define OCTOPUS_H

#include "Enemy.h"

namespace DT {
class Octopus;
}

class DT::Octopus: public Enemy {
private: Direction _type;

public:

    Octopus(QPointF pos, Direction _type);
    Direction type() {
        return _type;
    }
    // implemented abstract methods
    virtual std::string name() override {
        return "Octopus [" + std::to_string(_id) + "]";
    }

    // reimplemented abstract methods
    virtual bool hit(Object * what, Direction fromDir) override;
    virtual void advance() override;
};

#endif // OCTOPUS_H
