#include "Spawnable.h"

#include "Sprites.h"

#include "StaticObject.h"

#include "Block.h"

#include "Scrooge.h"

#include "Game.h"

#include "Sounds.h"

using namespace DT;

Spawnable::Spawnable(QPointF pos, double width, double height, Spawnable::Type type, bool canFall): Entity(pos, width, height) {
    _sprite = Sprites::instance() -> getSprite("spawnable");
    _compenetrable = true;
    _type = type;
    _canFall = canFall;
    if (_canFall) {
        _y_gravity = 0;
    } else {
        _y_gravity = 0.5;
    }
    if (_type == Type::ICE_CREAM) {
        Sprites::instance() -> get("ice-cream", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
    } else if (_type == Type::CAKE) {
        Sprites::instance() -> get("cake", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
    } else if (_type == Type::DIAMOND_YELLOW_SMALL) {
        _value = 10000;
        Sprites::instance() -> get("diamond-small-0", & _texture_spawnable[0]);
        Sprites::instance() -> get("diamond-small-1", & _texture_spawnable[1]);

        //_animRect = &_texture_spawnable[0];
    } else if (_type == Type::DIAMOND_YELLOW_BIG) {
        _value = 10000;
        Sprites::instance() -> get("diamond-big-0", & _texture_spawnable[0]);
        Sprites::instance() -> get("diamond-big-1", & _texture_spawnable[1]);
        Sprites::instance() -> get("diamond-big-2", & _texture_spawnable[2]);
        Sprites::instance() -> get("diamond-big-3", & _texture_spawnable[3]);
        //_animRect = &_texture_spawnable[0];
    } else if (_type == Type::DIAMOND_RED_BIG) {
        _value = 50000;
        Sprites::instance() -> get("diamond-big-4", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
    } else if (_type == Type::STAR) {
        _value = 0;
        Sprites::instance() -> get("star-0", & _texture_spawnable[0]);
        Sprites::instance() -> get("star-1", & _texture_spawnable[1]);
    } else if (_type == Type::KEY) {
        Sprites::instance() -> get("key", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
    } else if (_type == Type::TREASURE) {
        _value = 1000000;
        Sprites::instance() -> get("treasure", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
        setPos(QPointF(x() + TILE / 2, y()));
        _vel = {
            0,
            -2
        };
        _y_gravity = 0.05;

    } else if (_type == Type::REMOTE) {
        Sprites::instance() -> get("remote", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
    } else if (_type == Type::PROJECTILE) {
        _sprite = Sprites::instance() -> getSprite("projectile");
        Sprites::instance() -> get("projectile-0", & _texture_spawnable[0]);
        Sprites::instance() -> get("projectile-1", & _texture_spawnable[1]);
        _animRect = & _texture_spawnable[0];
    }

    if (_type == Type::CHEESE) {
        Sprites::instance() -> get("cheese", & _texture_spawnable[0]);
        _animRect = & _texture_spawnable[0];
    }
}

void Spawnable::thrownPhysics() {
    Entity::defaultPhysics();
    _y_vel_max = 2;
    _x_vel_max = 0.9;
    _y_gravity = 0.05;
}

bool Spawnable::animate() // Da aggiungere animazione di spawning e metodo migliore per le texture di quelli con un solo frame
{
    if (_canFall == 0 || (_canFall == 1 && _canFallHit == 1)) {
        if (_type == Type::DIAMOND_YELLOW_BIG) {
            _animRect = & _texture_spawnable[(FRAME_COUNT / 9) % 4];
        } else if (_type == Type::DIAMOND_YELLOW_SMALL) {
            _animRect = & _texture_spawnable[(FRAME_COUNT / 9) % 2];
        } else if (_type == Type::STAR) {
            _animRect = & _texture_spawnable[(FRAME_COUNT / 9) % 2];
        } else if (_type == Type::DIAMOND_RED_BIG) {
            _animRect = & _texture_spawnable[(FRAME_COUNT / 9) % 1];
        } else if (_type == Type::PROJECTILE && !taken) {
            _animRect = & _texture_spawnable[(FRAME_COUNT / 9) % 2];
        } else if (_type == Type::PROJECTILE && taken) {
            _animRect = & _texture_spawnable[(FRAME_COUNT / 9) % 2 + 2]; // +2 così alterna indce 2 e 3
        } else if (_type == Type::ICE_CREAM) {
            _animRect = & _texture_spawnable[0];
        } else if (_type == Type::TREASURE) {

            _animRect = & _texture_spawnable[0];
        } else if (_type == Type::TREASURE) {
            _animRect = & _texture_spawnable[0];
        } else if (_type == Type::CAKE) {
            _animRect = & _texture_spawnable[0];
        }

    } else {
        _animRect = & _texture_spawnable[Qt::transparent];
    }

    return 1;
}

bool Spawnable::hit(Object * what, Direction fromDir) {
    Scrooge * scrooge = what -> to < Scrooge * > ();
    StaticObject * sobj = what -> to < StaticObject * > ();

    if (scrooge && !_canFallHit && _canFall) {
        _collidable = false; // Metto a true per non consentire a Scrooge di prenderlo mentre l'oggeto è in caduta
        schedule("fall", 10, [this] {
            _collidable = true;
        });
        _canFallHit = true;
        _y_gravity = 0.5;
        return true;
    }

    if (scrooge && !taken && !(_type == Spawnable::Type::PROJECTILE)) {
        scrooge -> scoreAdd(this -> _value);
        Game::instance() -> hud() -> addScore(this -> _value);
        if (_type == Type::ICE_CREAM) {
            if (scrooge -> hp() < 6) {
                scrooge -> hpAdd(1);
            }
            Sounds::instance() -> play("spawnable");
        } else if (_type == Type::CAKE) {
            scrooge -> hpAdd(6 - scrooge -> hp()); // Restora tutti gli hp
            Sounds::instance() -> play("spawnable");
        } else if (_type == Type::STAR) {
            scrooge -> setInvincible(true);
            Sounds::instance() -> play("spawnable");
        } else if (_type == Type::KEY) {
            scrooge -> setKeyStatus(true);
            Game::instance() -> setMessage(Game::Message::KEY);
            Sounds::instance() -> play("spawnable");
        } else if (_type == Type::REMOTE) {
            Game::instance() -> setMessage(Game::Message::REMOTE);
            scrooge -> setRemoteStatus(true);
        } else if (_type == Type::DIAMOND_RED_BIG || _type == Type::DIAMOND_YELLOW_BIG || _type == Type::DIAMOND_YELLOW_SMALL) {
            Sounds::instance() -> play("spawnable");
        } else if (_type == Type::CHEESE) {
            Game::instance() -> gameClear();
        } else if (_type == Type::TREASURE) {
            Game::instance() -> setMessage(Game::Message::TREASURE);
        }
        std::cout << "Score: " << scrooge -> score() << "\n";
        taken = true;
        setVisible(false);
        return true;
    }

    if (sobj && sobj -> _type == StaticObject::Type::DEATHLINE) {
        setVisible(false);
    }

    if (sobj && sobj -> _type == StaticObject::Type::GREEN_GATE && _type == Type::PROJECTILE) {
        taken = true; // Taken su Projectile non significa nulla, ma piuttosto che inizializzare un'altra variabile "hit", utilizzo questa per flaggare la collisione col GREEN_GATE
        _x_dir = Direction::NONE;
        _sprite = Sprites::instance() -> getSprite("block");
        _boundingRect = QRect(0, 0, TILE, TILE);
        Sprites::instance() -> get("block-broken-0", & _texture_spawnable[2]);
        Sprites::instance() -> get("block-broken-1", & _texture_spawnable[3]);
        schedule("disappear", 40, [this]() {
            setVisible(false);
        });
    }

    return false;
}
