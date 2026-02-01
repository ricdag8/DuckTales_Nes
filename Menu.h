#pragma once

#include "Object.h"

#include "StaticObject.h"

namespace DT {
class Title;
class FlashingText;
class Arrow;
class Level;
}

class DT::Title: public Object {
private:

    QRect _animTitle;
    bool _moving;
    Arrow * _arrow;
    QGraphicsPixmapItem * _scrooge_0;
    QGraphicsPixmapItem * _scrooge_1;

    QRect _anim[2];

public:

    Title();
    Arrow * arrow() {
        return _arrow;
    }

    // implemented abstract methods
    virtual void advance() override;
    virtual bool animate() override;
    virtual bool hit(Object * what, Direction fromDir) override {
        return true;
    }
    virtual std::string name() override {
        return "Title";
    }
};

class DT::Level: public Object {
private: Arrow * _arrow;
    Arrow * _mapArrow;
    QGraphicsPixmapItem * iconLeft;
    QGraphicsPixmapItem * iconRight;
public: Level();

    virtual void advance() override;
    virtual bool animate() override;
    virtual bool hit(Object * what, Direction fromDir) override {
        return true;
    }
    virtual std::string name() override {
        return "Level";
    }

};

class DT::Arrow: public Object {
public: enum class Type {
        VERTICAL,
        HORIZONTAL
    };

private: friend class Title;
    friend class Level;

    QRect _anim[2];
    int _pos;
    int prev_pos;
    Type _type;

public:

    Arrow(QPointF pos, double width, double height, Type type);

    // implemented abstract methods
    virtual void advance() override;
    virtual bool animate() override;
    virtual bool hit(Object * what, Direction fromDir) override {
        return true;
    }
    virtual std::string name() override {
        return "Arrow";
    }
};
