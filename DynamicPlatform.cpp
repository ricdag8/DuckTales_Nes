#include "DynamicPlatform.h"
#include "Sprites.h"
#include "Game.h"
//#include <QPainter>
#include <QPixmap>
#include "StaticObject.h"



using namespace DT;

DynamicPlatform::DynamicPlatform(QPointF pos) : Entity(pos, 33, 17)
{
    _compenetrable = false;
    _sprite = Sprites::instance()->getSprite("platform");
    Sprites::instance()->get("platform", &_texture_platform[0]);


    _y_vel_max=0;
    _x_vel_max=1;
    move(Direction::LEFT);;

    }


void DynamicPlatform::advance()
{
   Entity::advance();
   _animRect = &_texture_platform[0];

    for (auto obj : _attached)
    {
        // object "on" the platform -> object moves along with platform
        if (obj.second == Direction::UP)
            obj.first->moveBy(_vel);

        // object hits platform from the bottom -> object pos corrected along y
        else if (obj.second == Direction::DOWN)
            obj.first->moveBy(Vec2Df(0, _vel.y));

        // object hits platform from one side -> object pos corrected along x
        else
            obj.first->moveBy(Vec2Df(_vel.x, 0));
    }
    _attached.clear();

}

bool DynamicPlatform::hit(Object* what, Direction fromDir)
{
    Scrooge* ent = what->to<Scrooge*>();

    if (!_compenetrable && ent && ent->compenetrable())
    {
        _compenetrable=false;
        _attached[ent] = fromDir;
    }

    if(what->to<StaticObject*>() && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT)){
        move(inverse(_x_dir));
        return true;
    }

return false;
}
