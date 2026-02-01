#ifndef BEAKLEY_H
#define BEAKLEY_H
#include <QPointF>
#include "Scrooge.h"
#include "Entity.h"
#include <QPixmap>

namespace DT{
    class Beakley;
}

class DT::Beakley : public Entity
{
protected:
    QRect _texture_beakley[3];
    bool _activated;    

public:

    Beakley(QPointF pos, double width, double height);

    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override {return true;};
    virtual std::string name() override { return "Beakley" ;  }
   
};

#endif 