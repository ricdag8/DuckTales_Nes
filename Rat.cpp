#include "Rat.h"

#include "Block.h"

#include "Sprites.h"

#include "GameConfig.h"

#include "StaticObject.h"

#include "Game.h"

using namespace DT;

Rat::Rat(QPointF pos): Enemy(pos, 39, 27) {
    _sprite = Sprites::instance() -> getSprite("rat");
    Sprites::instance() -> get("rat-run-0", & _texture_walk[0]);
    Sprites::instance() -> get("rat-run-1", & _texture_walk[1]);
    Sprites::instance() -> get("rat-jump-0", & _texture_walk[2]);
    Sprites::instance() -> get("rat-angry-0", & _texture_angry[0]);

    _jumping = false;
    _floored = true;
    _running = false;
    _reset = true;
    _starting = false;
    _angry = false;
    _recentlyHit = false;
    _y_vel_max = 3;

    _hp = 1;
}

void Rat::jump(bool on, Direction dir) {
    if (on) {
        if (!midair()) {
            if (!_floored) {
                _y_vel_max = 3;
                _y_gravity = 0.05;

                std::cout << "Salto 1\n";
                std::cout.flush();
                velAdd(Vec2Df(dir2speed(dir) * 0.5, -2.5));
            } else {
                _y_vel_max = 5;
                _y_gravity = 0.15;
                std::cout << "Salto 2\n";
                std::cout.flush();
                velAdd(Vec2Df(dir2speed(dir) * 0.2, -3.5));
            }
            _x_dir = dir;
            _jumping = true;
            if (!_floored) {
                schedule("stop1", 60, [this]() {
                    _x_dir = Direction::NONE;
                    _jumping = false;
                    _floored = true;
                });
                schedule("down", 80, [this, dir]() {
                    jump(true, inverse(dir));
                });
            } else {
                schedule("stop1", 61, [this]() {
                    _x_dir = Direction::NONE;
                    _jumping = false;
                    _reset = true;
                });
            }
        }
    }

}
void Rat::advance() {
    /*if(x() != 70*TILE){
   std::cout<<_angry<<"\n"; // Debugging serve per capire se resetta bene la posizione --> Bisogna controllare i parametri del primo salto
       std::cout.flush();}
   */
    if (Game::instance() -> bossFightStatus() && !Game::instance() -> GBFA()) {
        if (_reset && !_running && !midair() && !_angry) {
            _angry = false;
            if (chanceCalculator(0.5)) {
                _reset = false;
                _floored = false;
                std::cout << "Inizio salto\n";
                std::cout.flush();
                if (chanceCalculator(0.5)) {
                    schedule("wait1", 50, [this]() {
                        jump(true, Direction::RIGHT);
                    });
                } else {
                    schedule("wait2", 50, [this]() {
                        jump(true, Direction::LEFT);
                    });
                }
            } else {
                if (_reset && !_running) {
                    _reset = false;
                    schedule("wait3", 50, [this]() {
                        schedule("wait4", 5, [this]() {
                            _running = true;
                        });
                        if (x() < Game::instance() -> player() -> x()) {
                            move(Direction::RIGHT);
                        } else {
                            move(Direction::LEFT);
                        }
                        velAdd(Vec2Df(dir2speed(_x_dir) * 1, 0));
                    });
                }
            }

            if (chanceCalculator(0.5)) { // Non mi pare la faccia sempre
                _angry = true;
                schedule("wait6", 30, [this]() {
                    _angry = false;
                });
            }
        }

        if (_running && (floor(x()) == 1133 || ceil(x()) == 1133)) { // Stop zone compresa fra 1132 e 1134
            std::cout << "Inizio decelerazione\n";
            std::cout.flush();

            if (chanceCalculator(0.9)) { // Non sempre si ferma al centro, ma è raro che non lo faccia
                _x_dir = Direction::NONE;
                _running = false;
                schedule("wait5", 5, [this]() {
                    _reset = true;
                });
            }
        }

        Enemy::advance();
    }
}

bool Rat::animate() {
    bool showSprite = (_recentlyHit && (FRAME_COUNT / 3) % 2 == 0);
    if (!_recentlyHit) {
        if (midair() && !_reset) {
            _animRect = & _texture_walk[2];
        } else {

            if (_running) {
                _animRect = & _texture_walk[(FRAME_COUNT / 9) % 2];
            } else if (_angry) {
                _animRect = & _texture_angry[0];
            } else {
                _animRect = & _texture_walk[1];
            }
        }
    } else {
        if (midair() && !_reset) {
            _animRect = showSprite ? & _texture_walk[2] : nullptr;
        } else {

            if (_running) {
                _animRect = showSprite ? & _texture_walk[(FRAME_COUNT / 9) % 2] : nullptr;

            } else if (_angry) {
                _animRect = showSprite ? & _texture_angry[0] : nullptr;

            } else {
                _animRect = showSprite ? & _texture_walk[1] : nullptr;

            }
        }

    }

    return true;
}

bool Rat::hit(Object * what, Direction fromDir) {
    Scrooge * scrooge = what -> to < Scrooge * > ();
    if (what -> to < StaticObject * > () && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT)) {
        //_x_dir = inverse(_x_dir);
        move(inverse(_x_dir));
        velAdd(Vec2Df(-_vel.x, 0));
        //_y_gravity *= -1;
        return true;
    }

    if (scrooge && scrooge -> pogoing() && fromDir == Direction::UP) {
        lifeDown(); // Da implementare ancora la vita, per ora Rat segue la logica di Enemy che basta 1 hit per morire
    }

    if (Enemy::hit(what, fromDir))
        return true;

    return false;
}

int Rat::dir2speed(Direction dir) { // Funziona per fare il fighetto e togliere un paio di if, ma si può benissimo farne a meno
    if (dir == Direction::RIGHT) {
        return 1;
    } else if (dir == Direction::LEFT) {
        return -1;
    } else {
        return 0;
    }
}

void Rat::lifeDown() {
    if (_recentlyHit)
        return;

    if (_hp > 1) {
        _hp--;
        schedule("rh", 2, [this]() {
            recentlyHit(true);
        });
    } else {
        die();
        new Block(QPointF(72 * TILE - 8, 83 * TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::CHEESE);
    }
}

void Rat::recentlyHit(bool on) {
    _recentlyHit = on;

    if (on)
        schedule("flash", 100, [this]() {
            _recentlyHit = false;
        });
}
