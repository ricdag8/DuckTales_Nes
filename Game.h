#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

#include <QTimer>

#include "GameConfig.h"

#include "Gizmoduck.h"

#include "Loader.h"

#include "Scrooge.h"

#include "Hud.h"

#include "Menu.h"

namespace DT {
   class Game;
   class Scrooge;
}

class DT::Game: public QGraphicsView {
   Q_OBJECT
   public:
      enum class GameState {
         READY,
         TITLE_SCREEN,
         RUNNING,
         PAUSED,
         GAME_OVER,
         GAME_CLEAR,
         LIFT_TO_DUCKBURG,
         LEVEL_SELECTION
      };
   enum class Message {
      LAUNCHPAD,
      REMOTE,
      EVY,
      TREASURE,
      KEY,
      NONE
   };
   private:
      GameState _state;
   Scrooge * _player;
   QGraphicsScene * _world;
   Loader * _builder;
   QTimer _engine;
   HUD * _hud;
   HUD * _points;
   Title * _title;
   Message _text;

   bool _left_pressed;
   bool _right_pressed;
   bool _up_pressed;
   bool _down_pressed;
   bool _jump_pressed;
   bool _grab_pressed;
   bool _crouch_pressed;
   bool _pogo_pressed;
   bool _jump_released;
   bool _pogo_released;
   bool beagleActive;
   bool _swing_pressed;
   bool _swing_released;
   qreal _counter_cam;
   bool _transitioning;
   bool _LPcheckpoint; // Launchpad checkpoint?

   bool _bossFight;
   bool _bossFightAnimation;
   std::string _level_music_loop;
   std::string _current_music_loop;

   int _arrowPos = 0;
   int startingX = 0;
   int startingY = 64;
   short int difficulty;

   // singleton
   static Game * _uniqueInstance;
   Game(QGraphicsView * parent = 0);

   public:
      static Game * instance();
   void setMessage(Message type) {
      _player -> move(Direction::NONE);
      _text = type;
   }
   Message messageStatus() {
      return _text;
   }
   bool grabStatus() {
      return _grab_pressed;
   }
   void setBeagleStatus(bool on) {
      beagleActive = on;
   }
   int arrowPos() {
      return _arrowPos;
   }
   void setArrowPos(int on) {
      _arrowPos = on;
   }
   QGraphicsScene * world() {
      return _world;
   }
   void setTitle(Title * on) {
      _title = on;
   }
   Scrooge * player() {
      return _player;
   }
   HUD * hud() {
      return _hud;
   }
   double aspectRatio() {
      return 16 * 1.14 / 15;
   }
   // event handlers
   virtual void keyPressEvent(QKeyEvent * e) override;
   virtual void keyReleaseEvent(QKeyEvent * e) override;
   virtual void wheelEvent(QWheelEvent * e) override;
   virtual void resizeEvent(QResizeEvent * event) override;
   void gameOver() {
      _state = GameState::GAME_OVER;
   }
   void gameClear() {
      _state = GameState::GAME_CLEAR;
   }

   void welcome();
   void levelSelection();
   GameState state() {
      return _state;
   }
   void liftToDuckburg() {
      _state = GameState::LIFT_TO_DUCKBURG;
   }
   void gizmo();
   void bossFight();
   void spawningPoint();
   void setBossFightAnim(bool on) {
      _bossFightAnimation = on;
   };
   bool GBFA() {
      return _bossFightAnimation;
   };
   void setBossFight(bool on) {
      _bossFight = on;
   };
   bool bossFightStatus() {
      return _bossFight;
   };
   void extracted(QGraphicsItem * & item);
   void cameraChangeY(Direction fromDir);
   void beakleyDrop();
   void centerView();
   void moveUp(bool on) {
      _up_pressed = on;
   }
   void moveDown(bool on) {
      _down_pressed = on;
   }
   double diff2chance();
   short int diff() {
      return difficulty;
   }
   void setCounterCam(qreal value) {
      _counter_cam = value;
   }
   bool LPCheckPoint() {
      return _LPcheckpoint;
   }
   void resetClimbing() {
      _up_pressed = false;
      _down_pressed = false;
   }
   public slots:
      void reset();
   void start();
   void nextFrame();
   void gameEnd();
   void playMusic(const std::string & name);
   void stopMusic(bool resumable = false);
   void resumeMusic();
   void restoreLevelMusic();
   void timeExpired();

};
#endif