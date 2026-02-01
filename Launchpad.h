#ifndef LAUNCHPAD_H
#define LAUNCHPAD_H
#include <QPointF>

#include "Scrooge.h"

#include "Entity.h"

#include <QPixmap>

namespace DT {
class Launchpad;
}

class DT::Launchpad: public Entity {
protected: QRect _texture_launchpad[1];
    QRect _texture_launchpad_flying[2];
    bool _flying = 0;

public:

    Launchpad(QPointF pos, double width, double height);

    virtual bool animate() override;
    virtual bool hit(Object * what, Direction fromDir) override;
    virtual std::string name() override {
        return "Launchpad";
    }
    void flyingAnimation(Scrooge * scrooge);
};

#endif // LAUNCHPAD_H
