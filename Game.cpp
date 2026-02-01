#include "Game.h"

#include "BBoy.h"

#include "GameConfig.h"

#include "Launchpad.h"

#include "Loader.h"

#include "Scheduler.h"

#include "Object.h"

#include "Scrooge.h"

#include "Spawnable.h"

#include "Beakley.h"

#include "Hud.h"

#include "BBoy.h"

#include <QKeyEvent>

#include <QOpenGLWidget>

#include <QApplication>

#include <QPainter>

#include <QGraphicsPixmapItem>

#include <QBrush>

#include <QMediaPlayer>

#include "Sounds.h"

#include "Menu.h"

#include <QThread>

#include <QPalette>

using namespace DT;

Game * Game::_uniqueInstance = 0;
Game * Game::instance() {
   if (_uniqueInstance == 0)
      _uniqueInstance = new Game();
   return _uniqueInstance;
}

Game::Game(QGraphicsView * parent): QGraphicsView(parent) {
   _world = new QGraphicsScene();
   _world -> setSceneRect(0, 0, TILE * 128, TILE * 86.5); // Vista di default è 0 56.5
   setScene(_world);
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setInteractive(false);
   //Game::instance()->world()->setBackgroundBrush(QBrush(QImage(":/background/theMoon.png")));

   QObject::connect( & _engine, SIGNAL(timeout()), this, SLOT(nextFrame()));
   _engine.setInterval(1000 / 60);
   _engine.setTimerType(Qt::PreciseTimer);

   _builder = new Loader();
   _player = 0;
   _counter_cam = 0;
   beagleActive = 1;

   /*
   QOpenGLWidget* gl = new QOpenGLWidget();
   setViewport(gl);
   */
   _hud = new HUD(width(), height(), this);
   _points = new HUD(14 * TILE - 2, 9.5 * TILE - 8, this);

   connect(_hud, SIGNAL(timeExpired()), this, SLOT(timeExpired()));
   reset();
}

void Game::reset() {

   _state = GameState::READY;
   _text = Message::NONE;
   _engine.stop();
   _world -> clear();
   //_world->setSceneRect(0, 0, TILE * 30, TILE * 30);
   _hud -> setVisible(false);
   _hud -> reset();
   _points -> setVisible(false);
   _points -> reset();
   _player = 0;
   _builder = 0;
   beagleActive = 1;
   difficulty = 0;
   _arrowPos = 0;
   _counter_cam = 0;
   _bossFight = 0;
   _bossFightAnimation = 0;
   _left_pressed = false;
   _right_pressed = false;
   _up_pressed = false;
   _down_pressed = false;
   _pogo_pressed = false;
   _pogo_released = false;
   _jump_pressed = false;
   _jump_released = false;
   _crouch_pressed = false;
   _grab_pressed = false;
   _swing_pressed = false;
   _swing_released = false;
   _transitioning = false;
   _LPcheckpoint = false;

   _current_music_loop = _level_music_loop = "";

   QTimer::singleShot(0, this, & Game::welcome);
}

void Game::welcome() {

   if (_state == GameState::READY) {
      _state = GameState::TITLE_SCREEN;
      _world -> clear();
      _engine.setInterval(1000 / (FPS / 2)); // 30 FPS per avere l'occhiolino nel menù iniziale come nel gioco originale
      _engine.start();
      //Sounds::instance()->stopMusic(_music);
      Loader::load("Title");
      //Sounds::instance()->playMusic(_music, false)
      playMusic("titlescreen1");
   }
}

void Game::levelSelection() {
   _state = GameState::LEVEL_SELECTION;
   _world -> clear();
   Loader::load("Level");
   _arrowPos = 0;

   _player = _builder -> load("levelSelection");
   playMusic("levelselection");

}

void Game::gizmo() {
   for (auto item: _world -> items()) {
      Gizmoduck * gizmo = dynamic_cast < Gizmoduck * > (item);
      if (gizmo) {
         gizmo -> activate();
         _player -> setGizmoCinematicStatus(true);

      }
   }
}

void Game::bossFight() {
   _bossFight = true;
   _bossFightAnimation = true;
   _LPcheckpoint = false; // Se inizia la Boss Fight cambia nuovamente il punto di respawning
   _player -> startBossFightAnimation();
   playMusic("bossbattledrums");
}

void Game::start() {
   std::cout << "Start\n";
   std::cout.flush();
   if (_state == GameState::LEVEL_SELECTION) {
      FRAME_COUNT = 0;
      _state = GameState::RUNNING;
      _world -> clear();
      //_world->setSceneRect(64*TILE, 75*TILE, TILE * 64, TILE * 11.5);
      _engine.setInterval(1000 / FPS);
      _engine.start();
      _hud -> setVisible(true);
      _hud -> start();
      _player = _builder -> load("theMoon");
      _player -> setSitting(false);
      //QMediaPlayer * music= new QMediaPlayer();
      playMusic("themoontheme");
   }
}

void Game::nextFrame() {

   FRAME_COUNT++;
   if (_state == GameState::TITLE_SCREEN || _state == GameState::LEVEL_SELECTION || _state == GameState::GAME_CLEAR) { // era if (_state != GameState::RUNNING && _state != GameState::TITLE_SCREEN), non ne capisco il senso, da vedere

      /*std::cout<<_arrowPos<<"\n";
          std::cout.flush();
          */
      for (auto item: _world -> items()) {
         Object * obj = dynamic_cast < Object * > (item);

         if (obj && (obj -> isVisible())) {
            obj -> advance(); // physics, collision detection and resolution, game logic
            obj -> animate(); // animation
            //obj -> updateSchedulers(); // game logic
            //obj->paint();			 // graphics, automatically called by Qt
         }
      }
      update();

      return;
   }
   // process inputs	 (PLAYER CONTROLS)

   if (!_player -> gizmoduckCinematic() && !_player -> launchpadAttachment() && !_bossFightAnimation && !_player -> respawningGF() && !_transitioning && _text == Message::NONE) { // Commandi di movimento accessibili solo se nessuna è True
      if (!_player -> climbing()) { // durante climbing non tutti i movimenti sono consentiti
         if (_left_pressed && _right_pressed)
            _player -> move(Direction::NONE);
         else if (_left_pressed || _player -> launchpadAttachment())
            _player -> move(Direction::LEFT);
         else if (_right_pressed)
            _player -> move(Direction::RIGHT);
         else
            _player -> move(Direction::NONE);

         if (_grab_pressed) {
            _player -> grab(true);
            _grab_pressed = false;
         }

         if (_pogo_pressed) // Qui va aggiunta una condizione che non consente di attivare il pogo se si è a terra ma che non impedisca di rimbalzare quando si è in pogoing
         {
            _player -> pogo(true);
         } else if (_pogo_released) {
            _player -> pogo(false);
            _pogo_released = false;
         }
         if (_crouch_pressed && !_pogo_pressed) {
            _player -> crouch(true);
            _player -> move(Direction::NONE);

         } else
            _player -> crouch(false);

      } else {
         if (_down_pressed && _up_pressed) {
            /*std::cout << "if(_down_pressed && _up_pressed)\n";
            std::cout.flush();*/
            _player -> move(Direction::NONE);
         } else if (_up_pressed) {
            /*std::cout << "else if(_up_pressed)\n";
            std::cout.flush();*/
            _player -> move(Direction::UP);
         } else if (_down_pressed) {
            /*
            std::cout << "else if(_down_pressed)\n";
            std::cout.flush();*/
            _player -> move(Direction::DOWN);
         } else
            _player -> move(Direction::NONE);
         if (_jump_pressed) {
            _player -> setClimbing(false);
         }

      }
      if (_swing_pressed) {
         _player -> swing(true);
         _swing_pressed = false;

      } else if (_swing_released) {
         _player -> swing(false);
         _swing_released = false;

      }

      if (_jump_pressed) {
         _player -> jump(true);
         _jump_pressed = false;
      } else if (_jump_released) {
         _player -> jump(false);
         _jump_released = false;
      }
   }
   if (!beagleActive && !_bossFight && _player -> x() > 95 * TILE && _player -> y() > 70 * TILE) {
      std::cout << "Respawning\n";
      std::cout.flush();
      // Meglio schedulare il respawn dopo un paio di FRAME
      beagleActive = true;
      _player -> schedule("restore", 100, [this]() {
         spawningPoint();
      });
      /*spawningPoint(); // Respawing naive, funzione per valutare il primo blocco utile su cui potersi poggiare
            beagleActive = true; // C'è unironically un memory leak...
*/
   }

   for (auto item: _world -> items()) {
      Object * obj = dynamic_cast < Object * > (item);

      if (obj && (obj -> isVisible() || (dynamic_cast < Enemy * > (item) && !dynamic_cast < BBoy * > (item) && !dynamic_cast < Enemy * > (item) -> isVisible()))) { // Enemy: ho bisogno che updati anche se invisibili per il respawning, MA NON PER BBOY
         obj -> advance(); // physics, collision detection and resolution, game logic
         obj -> animate(); // animation
         obj -> updateSchedulers(); // game logic
         //obj->paint();			 // graphics, automatically called by Qt
      }
   }

   //centerOn(_player->pos()); for Debugging

   if (_state == GameState::LIFT_TO_DUCKBURG) {
      centerOn(_player -> x(), _player -> y() - 2 * TILE);
   } else if (!_player -> inRatPit()) {
      centerView();
   } else {
      centerOn(72 * TILE, 79 * TILE); // Durante la boss fight, camera fissa nel pit
   }

   update();

   if (FRAME_COUNT % 60 == 0) {
      _hud -> subTime();
   }

   if (_player -> dead()) {
      gameOver();
   }

   if (_state == GameState::GAME_OVER || _state == GameState::GAME_CLEAR || _state == GameState::LIFT_TO_DUCKBURG) {
      gameEnd();
   }

}

void Game::keyPressEvent(QKeyEvent * e) {
   if (e -> isAutoRepeat())
      return;
   // Game controls
   if (e -> key() == Qt::Key_S) {
      if (_state == GameState::TITLE_SCREEN) {
         difficulty = _arrowPos;
         levelSelection();
      } else if (_state == GameState::LEVEL_SELECTION && _arrowPos == 0) {
         start();
      }
   } else if (e -> key() == Qt::Key_R)
      reset();
   /*
   else if (e->key() == Qt::Key_P)
       togglePause();
   */
   else if (e -> key() == Qt::Key_C) {
      for (auto item: _world -> items()) {
         if (dynamic_cast < Object * > (item)) {
            dynamic_cast < Object * > (item) -> toggleCollider();
         }
      }
   } else if (e -> key() == Qt::Key_Minus) {
      _engine.setInterval(250);
   } else if (e -> key() == Qt::Key_Plus) {
      _engine.setInterval(1000 / FPS);
   }

   // Player controls
   if ((_state == GameState::RUNNING && _player)) // if (_state == GameState::RUNNING && _player)
   {
      if (e -> key() == Qt::Key_Left) {

         _left_pressed = true;

      } else if (e -> key() == Qt::Key_Right) {

         _right_pressed = true;

      } else if (e -> key() == Qt::Key_Down) {
         if (!_player -> climbing()) {
            _crouch_pressed = true;
         } else {
            _down_pressed = true;
         }
      } else if (e -> key() == Qt::Key_Space) {
         _jump_pressed = true;
         _jump_released = false;
      } else if (e -> key() == Qt::Key_X) {
         if (_text == Message::NONE) {
            _swing_pressed = true;
            _swing_released = false;
         } else {
            if (_text == Message::LAUNCHPAD) {
               _LPcheckpoint = true;
            } // se premi X durante l'interazione con Launchpad, ti viene cambiato il respawning point
            _text = Message::NONE; // Altrimenti, in ogni altro caso, si rimette l'HUD normale.
         }

      } else if (e -> key() == Qt::Key_Up) {
         if (_player -> climbing()) {
            _up_pressed = true;
         } else {
            _grab_pressed = true;
         }
      } else if (e -> key() == Qt::Key_Z) {
         if (_text == Message::NONE) {
            _pogo_pressed = true;
         } else if (_text == Message::LAUNCHPAD) {
            for (auto item: _world -> items()) {
               Launchpad * launchpad = dynamic_cast < Launchpad * > (item);
               if (launchpad) {
                  launchpad -> flyingAnimation(_player);
                  _state = GameState::LIFT_TO_DUCKBURG;
                  _hud -> setVisible(false);
                  break;
               }
            }
            _text = Message::NONE;
         }
      }

      // Cheats
      /*
      else if (e->key() == Qt::Key_I)
      {
          // invincibility
      }
      */
      else if (e -> key() == Qt::Key_K) {
         startingX++;
         setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
      } else if (e -> key() == Qt::Key_H) {
         startingX--;
         setSceneRect(TILE * startingX--, TILE * startingY, TILE * 128, TILE * 15);
      } else if (e -> key() == Qt::Key_U) {
         startingY--;
         setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
      } else if (e -> key() == Qt::Key_J) {
         startingY++;
         setSceneRect(TILE * startingX, TILE * startingY, TILE * 128, TILE * 15);
      }
   } else if (_state == GameState::TITLE_SCREEN) {
      if (e -> key() == Qt::Key_Left && _arrowPos > 0) {
         _arrowPos--;
      } else if (e -> key() == Qt::Key_Right && _arrowPos < 2) {
         _arrowPos++;
      }
   } else if (_state == GameState::LEVEL_SELECTION) {
      if (e -> key() == Qt::Key_Up && _arrowPos < 4) {
         _arrowPos++;
      } else if (e -> key() == Qt::Key_Down && _arrowPos > 0) {
         _arrowPos--;
      }
   }
}

void Game::keyReleaseEvent(QKeyEvent * e) {
   if (e -> isAutoRepeat())
      return;

   // player controls
   if ((_state == GameState::RUNNING || _state == GameState::TITLE_SCREEN || _state == GameState::LEVEL_SELECTION) && _player) {
      if (e -> key() == Qt::Key_Left)
         _left_pressed = false;
      else if (e -> key() == Qt::Key_Right)
         _right_pressed = false;
      else if (e -> key() == Qt::Key_Space) {
         _jump_pressed = false;
         _jump_released = true;
      } else if (e -> key() == Qt::Key_Down) {
         if (_player -> climbing()) {
            _down_pressed = false;
         } else {
            _crouch_pressed = false;
         }
      } else if (e -> key() == Qt::Key_X) {

         _swing_pressed = false;
         _swing_released = true;

      } else if (e -> key() == Qt::Key_Up) {
         if (_player -> climbing()) {
            _up_pressed = false;
         }
      } else if (e -> key() == Qt::Key_Z) {
         _pogo_pressed = false;
         _pogo_released = true;
      }
   }
}

void Game::wheelEvent(QWheelEvent * e) {

   if (e -> angleDelta().y() > 0)
      scale(1.1, 1.1);
   else
      scale(1 / 1.1, 1 / 1.1);

}

void Game::resizeEvent(QResizeEvent * evt) {
   fitInView(0, 0, TILE * 16 - 4, TILE * 15 - 4);
}

void Game::spawningPoint() {
   BBoy * test = new BBoy(QPointF(_player -> x() - 6 * TILE, _player -> y() - TILE));
}

void Game::beakleyDrop() {
   for (auto item: _world -> items()) {
      Beakley * beakley = dynamic_cast < Beakley * > (item);
      if (beakley) {
         int change = 1;
         for (int i = 0; i < 2; i++) {
            Spawnable * drop = new Spawnable(beakley -> pos(), TILE, TILE, Spawnable::Type::ICE_CREAM);
            drop -> thrownPhysics();
            change = change * -1;
            if (change == -1) {
               drop -> setDir(Direction::LEFT);
            } else {
               drop -> setDir(Direction::RIGHT);
            }
            drop -> velAdd(Vec2Df(change * 0.3, -1));
            break;
         }
      }
   }
}

void Game::gameEnd() {
   if (_state != GameState::GAME_CLEAR && _state != GameState::GAME_OVER)
      return;

   if (_state == GameState::GAME_CLEAR) {
      centerOn(0, 82 * TILE);
      _player -> move(Direction::NONE);
      _player -> climbingPhysics();
      _player -> setSitting(true);
      _player -> setPos(7.35 * TILE, 82 * TILE);
      _hud -> setVisible(false);
      _points -> setVisible(true);
      _points -> move(QPoint(9 * TILE, 10.5 * TILE));
   } else if (_state == GameState::GAME_OVER) {
      std::cout << "Game Over";
      reset();
   }
}

void Game::centerView() {

   qreal fixedY = 1024; //1300 per rat
   qreal playerX = _player -> x();
   qreal newY = fixedY + _counter_cam; //in questo punto viene aggiornato anche il valore della nuova

   centerOn(playerX, newY);
}

double Game::diff2chance() {
   switch (difficulty) {
   case 0:
      return 0.9;
      break;
   case 1:
      return 0.5;
      break;
   case 2:
      return 0.1;
      break;
   }
}

void Game::cameraChangeY(Direction fromDir) {
   const int transition_speed = 20; // Aumentato ulteriormente per una transizione più lenta
   const int incr = 240; //dovrebbe essere più o meno il valore corretto per la finestra di gioco
   _transitioning = true;
   int incremento = 0;
   if (fromDir == Direction::UP) {
      incremento = incr / transition_speed;
   } else if (fromDir == Direction::DOWN) {
      incremento = -incr / transition_speed;
   }

   // Applica la transizione graduale
   for (int i = 0; i < transition_speed; i++) {
      _counter_cam += incremento;

      centerView();

      update();
      QCoreApplication::processEvents(); // Aggiorna gli eventi della GUI
      QThread::msleep(30); // Attendere 30 millisecondi (puoi regolare questo valore)
   }
   _transitioning = false;

}

void Game::playMusic(const std::string & name) {
   if (!_current_music_loop.empty())
      Sounds::instance() -> stop(_current_music_loop);

   _current_music_loop = name;
   if (!_current_music_loop.empty())
      Sounds::instance() -> play("themoontheme", true);
}

void Game::stopMusic(bool resumable) {
   if (!_current_music_loop.empty())
      Sounds::instance() -> stop(_current_music_loop, resumable);
}

void Game::resumeMusic() {
   if (!_current_music_loop.empty())
      Sounds::instance() -> resume(_current_music_loop);
}

void Game::restoreLevelMusic() {
   if (!_current_music_loop.empty())
      playMusic(_level_music_loop);
}

void Game::timeExpired() {
   _player -> die();
}