#include "Hud.h"

#include "Game.h"

#include "Sprites.h"

#include <QPainter>

#include <cmath>

using namespace DT;

HUD::HUD(int w, int h, QWidget * parent): QWidget(parent) {
   _background = Sprites::instance() -> getHUD("hud"); //per i testi sostituire hud con hud-text e togliere i commenti alla funzione paintevent
   _flashin_coin_timer.setInterval(150);

   resize(w, h);
   reset();
}

void HUD::start() {
   _time = 600;
}

void HUD::reset() {
   _score = 0;
   _coins = 0;
   _world = 1;
   _level = 1;
   _time = -1;
   _fps = 0;
   _last_digit = 0;
   _score_items.clear();
}

void HUD::togglePause() {
   if (_flashin_coin_timer.isActive())
      _flashin_coin_timer.stop();
   else
      _flashin_coin_timer.start();
}

void HUD::paintEvent(QPaintEvent * event) {
   QPainter painter(this);
   painter.setBackgroundMode(Qt::TransparentMode);

   int dx = 0;
   if (Game::instance() -> player() -> score() != 0) dx = std::log10(Game::instance() -> player() -> score());

   if (Game::instance() -> state() == Game::GameState::GAME_CLEAR) {
      _background = QPixmap(120, 82);
      _background.fill(Qt::black);
      painter.setWindow(0, 0, 120, 82);
      painter.drawPixmap(0, 0, _background);
      painter.drawPixmap(13, 18, Sprites::instance() -> getString("THE"));
      painter.drawPixmap(48, 18, Sprites::instance() -> getString("MOON"));

      painter.drawPixmap(21, 26, Sprites::instance() -> getString("LAND"));
      painter.drawPixmap(60, 26, Sprites::instance() -> getString("CLEAR"));

      painter.drawPixmap(14, 41, Sprites::instance() -> getString("TOTAL"));
      painter.drawPixmap(61, 41, Sprites::instance() -> getString("MONEY"));
      painter.drawPixmap(16, 48, Sprites::instance() -> getHUD("$"));
      painter.drawPixmap(97 - (9 * dx), 50, Sprites::instance() -> getNumber(Game::instance() -> player() -> score()));

      painter.drawPixmap(14, 65, Sprites::instance() -> getString("LAND"));
      painter.drawPixmap(23, 72, Sprites::instance() -> getHUD("$"));
      painter.drawPixmap(61, 65, Sprites::instance() -> getString("MONEY"));
      painter.drawPixmap(97 - (9 * dx), 74, Sprites::instance() -> getNumber(Game::instance() -> player() -> score()));
   } else {
      painter.setWindow(0, 0, TILE * 19, TILE * 9.1);

      _background = Sprites::instance() -> getHUD("hud-text");
      painter.drawPixmap(0, 0, _background);

      if (Game::instance() -> messageStatus() == Game::Message::NONE) {
         _background = Sprites::instance() -> getHUD("hud");
         painter.drawPixmap(0, 0, _background);

         painter.drawPixmap(131, 27, Sprites::instance() -> getNumber(Game::instance() -> player() -> lives())); // p.
         painter.drawPixmap(72 - (7 * dx), 13, Sprites::instance() -> getNumber(Game::instance() -> player() -> score())); // money sx
         painter.drawPixmap(151 - (9 * dx), 19, Sprites::instance() -> getNumber(Game::instance() -> player() -> score())); // money dx
         if (_time >= 0) {
            painter.drawPixmap(201, 19, Sprites::instance() -> getNumber(_time)); // time
         }
         painter.drawPixmap(115, 27, Sprites::instance() -> getString("P"));
         painter.drawPixmap(123, 27, Sprites::instance() -> getHUD("."));
         painter.drawPixmap(25, 25, Sprites::instance() -> getString("HP"));
         painter.drawPixmap(105, 11, Sprites::instance() -> getString("TOTAL"));
         painter.drawPixmap(164, 19, Sprites::instance() -> getString("TIME"));
         painter.drawPixmap(24, 13, Sprites::instance() -> getHUD("$"));
         painter.drawPixmap(92, 19, Sprites::instance() -> getHUD("$"));

         if (Game::instance() -> player() -> hp() == 6) {
            painter.drawPixmap(50, 25, Sprites::instance() -> getHUD("health-0"));
            painter.drawPixmap(58, 25, Sprites::instance() -> getHUD("health-0"));
            painter.drawPixmap(66, 25, Sprites::instance() -> getHUD("health-0"));
         } else if (Game::instance() -> player() -> hp() == 5) {
            painter.drawPixmap(50, 25, Sprites::instance() -> getHUD("health-0"));
            painter.drawPixmap(58, 25, Sprites::instance() -> getHUD("health-0"));
            painter.drawPixmap(66, 25, Sprites::instance() -> getHUD("health-1"));
         } else if (Game::instance() -> player() -> hp() == 4) {
            painter.drawPixmap(50, 25, Sprites::instance() -> getHUD("health-0"));
            painter.drawPixmap(58, 25, Sprites::instance() -> getHUD("health-0"));
         } else if (Game::instance() -> player() -> hp() == 3) {
            painter.drawPixmap(50, 25, Sprites::instance() -> getHUD("health-0"));
            painter.drawPixmap(58, 25, Sprites::instance() -> getHUD("health-1"));
         } else if (Game::instance() -> player() -> hp() == 2) {
            painter.drawPixmap(50, 25, Sprites::instance() -> getHUD("health-0"));
         } else if (Game::instance() -> player() -> hp() == 1) {
            painter.drawPixmap(50, 25, Sprites::instance() -> getHUD("health-1"));
         }
      } else {
         _background = Sprites::instance() -> getHUD("hud-text");
         painter.drawPixmap(0, 0, _background);
         if (Game::instance() -> messageStatus() == Game::Message::REMOTE) {
            painter.drawPixmap(23, 18, Sprites::instance() -> getString("MESSAGE"));
            painter.drawPixmap(101, 11, Sprites::instance() -> getString("BLESS"));
            painter.drawPixmap(145, 11, Sprites::instance() -> getString("ME"));
            painter.drawPixmap(169, 11, Sprites::instance() -> getString("BAGPIPES"));
            painter.drawPixmap(101, 19, Sprites::instance() -> getString("NOW"));
            painter.drawPixmap(131, 19, Sprites::instance() -> getString("GIZMODUCK"));
            painter.drawPixmap(209, 19, Sprites::instance() -> getString("CAN"));
            painter.drawPixmap(101, 27, Sprites::instance() -> getString("BLAST"));
            painter.drawPixmap(149, 27, Sprites::instance() -> getString("THAT"));
            painter.drawPixmap(189, 27, Sprites::instance() -> getString("WALL"));
         } else if (Game::instance() -> messageStatus() == Game::Message::LAUNCHPAD) {
            painter.drawPixmap(23, 18, Sprites::instance() -> getString("MESSAGE"));
            painter.drawPixmap(101, 11, Sprites::instance() -> getString("YOU"));
            painter.drawPixmap(133, 11, Sprites::instance() -> getString("WANT"));
            painter.drawPixmap(173, 11, Sprites::instance() -> getString("A"));
            painter.drawPixmap(189, 11, Sprites::instance() -> getString("LIFT"));
            painter.drawPixmap(101, 19, Sprites::instance() -> getString("BACK"));
            painter.drawPixmap(141, 19, Sprites::instance() -> getString("TO"));
            painter.drawPixmap(165, 19, Sprites::instance() -> getString("DUCKBORG"));
            painter.drawPixmap(101, 27, Sprites::instance() -> getString("MR"));
            painter.drawPixmap(119, 27, Sprites::instance() -> getHUD("."));
            painter.drawPixmap(124, 27, Sprites::instance() -> getString("D"));
            painter.drawPixmap(133, 27, Sprites::instance() -> getHUD("."));
            painter.drawPixmap(149, 27, Sprites::instance() -> getString("YES"));
            painter.drawPixmap(181, 27, Sprites::instance() -> getString("Z"));
            painter.drawPixmap(197, 27, Sprites::instance() -> getString("NO"));
            painter.drawPixmap(223, 27, Sprites::instance() -> getString("X"));
         } else if (Game::instance() -> messageStatus() == Game::Message::EVY) {
            painter.drawPixmap(23, 18, Sprites::instance() -> getString("MESSAGE"));
            painter.drawPixmap(101, 11, Sprites::instance() -> getString("THERE"));
            painter.drawPixmap(143, 11, Sprites::instance() -> getString("IS"));
            painter.drawPixmap(168, 11, Sprites::instance() -> getString("A"));
            painter.drawPixmap(182, 11, Sprites::instance() -> getString("KEY"));
            painter.drawPixmap(211, 11, Sprites::instance() -> getString("IN"));
            painter.drawPixmap(101, 19, Sprites::instance() -> getString("THE"));
            painter.drawPixmap(133, 19, Sprites::instance() -> getString("UFO"));
            painter.drawPixmap(165, 19, Sprites::instance() -> getString("WE"));
            painter.drawPixmap(189, 19, Sprites::instance() -> getString("CAN"));
            painter.drawPixmap(213, 19, Sprites::instance() -> getHUD("'"));
            painter.drawPixmap(219, 19, Sprites::instance() -> getString("T"));
            painter.drawPixmap(103, 27, Sprites::instance() -> getString("GO"));
            painter.drawPixmap(125, 27, Sprites::instance() -> getString("ON"));
            painter.drawPixmap(149, 27, Sprites::instance() -> getString("WITHOUT"));
            painter.drawPixmap(211, 27, Sprites::instance() -> getString("IT"));
         } else if (Game::instance() -> messageStatus() == Game::Message::TREASURE) {
            painter.drawPixmap(23, 18, Sprites::instance() -> getString("MESSAGE"));
            painter.drawPixmap(101, 11, Sprites::instance() -> getString("IT"));
            painter.drawPixmap(120, 11, Sprites::instance() -> getHUD("'"));
            painter.drawPixmap(130, 11, Sprites::instance() -> getString("S"));
            painter.drawPixmap(147, 11, Sprites::instance() -> getString("A"));
            painter.drawPixmap(163, 11, Sprites::instance() -> getString("HIDDEN"));
            painter.drawPixmap(101, 19, Sprites::instance() -> getString("TREASURE"));
            painter.drawPixmap(167, 19, Sprites::instance() -> getHUD("."));
            }else if (Game::instance() -> messageStatus() == Game::Message::KEY) {
            painter.drawPixmap(23, 18, Sprites::instance() -> getString("MESSAGE"));
            painter.drawPixmap(101, 11, Sprites::instance() -> getString("IT"));
            painter.drawPixmap(120, 11, Sprites::instance() -> getHUD("'"));
            painter.drawPixmap(130, 11, Sprites::instance() -> getString("S"));
            painter.drawPixmap(147, 11, Sprites::instance() -> getString("A"));
            painter.drawPixmap(165, 11, Sprites::instance() -> getString("KEY"));
            painter.drawPixmap(192, 11, Sprites::instance() -> getString("TO"));
            painter.drawPixmap(130, 19, Sprites::instance() -> getString("THE"));
            painter.drawPixmap(162, 19, Sprites::instance() -> getString("UFO"));
            
         }
      }
   }

}

void HUD::flashCoin() {
   static int animation_counter = 0;
   _coin = & _flashin_coin_animation[(animation_counter++) % 6];

   update();
}

void HUD::subTime() {
   _time -= 1;
   update();
   _last_digit = _time % 10;

   if (_time == 0)
      emit timeExpired();
}

void HUD::addScore(int s, QPointF pos) {
   _score += s;
   if (pos != QPointF(-1, -1))
      _score_items.push_back(ScoreItem(s, pos));
   update();
}

void HUD::advance() {
   for (auto & s: _score_items)
      s++;

   update();
}

ScoreItem::ScoreItem(int score, QPointF pos) {
   _expired = false;
   _origin = Game::instance() -> mapFromScene(pos);
   _origin.setX(_origin.x() / Game::instance() -> transform().m11());
   _origin.setY(_origin.y() / Game::instance() -> transform().m22());

   if (score == 0) // oneup
      //Sounds::instance()->play("oneup");
      _age = 0;
   //_texture = Sprites::instance()->getScore(score);
}

void ScoreItem::operator++(int) {
   if (!_expired)
      _expired = ++_age == 120;
}

void ScoreItem::draw(QPainter * painter) {
   if (!_expired)
      painter -> drawPixmap(_origin + QPointF(0, -_age * 0.5), _texture);
}