#include "Launchpad.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Game.h"
#include "Scrooge.h"
using namespace DT;

Launchpad::Launchpad(QPointF pos, double width, double height):Entity(pos, width, height)
{
    _sprite = Sprites::instance()->getSprite("launchpad");
    Sprites::instance()->get("launchpad-standing", &_texture_launchpad[0]);
    Sprites::instance()->get("launchpad-flying-0", &_texture_launchpad_flying[0]);
    Sprites::instance()->get("launchpad-flying-1", &_texture_launchpad_flying[1]);

    _animRect = &_texture_launchpad[0];
}


bool Launchpad::animate()
{
    if(_flying){
        _boundingRect = QRectF(0, 0, 53, 71);
        _collider = _boundingRect;
        _animRect = &_texture_launchpad_flying[(FRAME_COUNT / 9) % 2];
    }
    return 1;
}

bool Launchpad::hit(Object *what, Direction fromDir)
{
    Scrooge* scrooge = dynamic_cast<Scrooge*>(what);
    if(scrooge && !_flying){
        Game::instance()->setMessage(Game::Message::LAUNCHPAD);
    }
    return 0;
}

void Launchpad::flyingAnimation(Scrooge* scrooge)
{
    _flying = true;
    _y_gravity = 0;
    scrooge->_vel = {0, 0};
    scrooge->climbingPhysics();
    scrooge->_launchpadAttached = true;
    _x_dir = Direction::LEFT;
    scrooge->_x_dir = Direction::LEFT;
    scrooge->_y_dir = Direction::NONE;

    setPos(10*TILE, 4.5*TILE);
    scrooge->setPos(x() + TILE/2, y() + 3*TILE);

    _x_vel_max = 1;
    scrooge->_x_vel_max = 1,
    scrooge->_vel = {-_x_vel_max, 0};
    velAdd(Vec2Df(-_x_vel_max, 0));

}







