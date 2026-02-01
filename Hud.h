#pragma once

#include <QWidget>

#include <QTimer>

#include <QPainter>

#include "Sprites.h"

namespace DT {
   class HUD;
   class ScoreItem;
}

class DT::HUD: public QWidget {
   Q_OBJECT

   private:

      QPixmap _background;
   QPixmap * _coin;
   int _score;
   int _coins;
   int _world;
   int _level;
   int _time;
   int _fps;
   QTimer _flashin_coin_timer;
   QPixmap _flashin_coin_animation[6];
   std::list < ScoreItem > _score_items;
   int _last_digit;

   public:

      HUD(int w, int h, QWidget * parent);

   void togglePause();
   void start();
   void reset();
   void addScore(int s, QPointF pos = QPointF(-1, -1));
   void addCoin() {
      _coins += 1;
      update();
   }
   void setWorld(int w) {
      _world = w;
      update();
   }
   void setLevel(int l) {
      _level = l;
      update();
   }
   void setFPS(int v) {
      _fps = v;
      update();
   }
   void subTime();
   void advance();

   virtual void paintEvent(QPaintEvent * event) override;

   protected slots:

      void flashCoin();

   signals:

      void timeExpired();
};

class DT::ScoreItem {
   private:

      QPixmap _texture;
   QPointF _origin;
   int _age;
   bool _expired;

   public:

      ScoreItem(int score, QPointF pos);
   void operator++(int);
   void draw(QPainter * painter);
   bool expired() {
      return _expired;
   }
};