#include "Beakley.h"

#include "Sprites.h"

#include "Scrooge.h"

#include "GameConfig.h"

#include "Spawnable.h"

using namespace DT;

Beakley::Beakley(QPointF pos, double width, double height): Entity(pos, width, height) {

   _activated = false;
   _sprite = Sprites::instance() -> getSprite("beakley");
   Sprites::instance() -> get("beakley-0", & _texture_beakley[0]);
   Sprites::instance() -> get("beakley-1", & _texture_beakley[1]);
   Sprites::instance() -> get("beakley-1", & _texture_beakley[2]);

}

bool Beakley::animate() {

   _animRect = & _texture_beakley[(FRAME_COUNT / 10) % 2];

   return 1;
}