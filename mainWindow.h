#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QBoxLayout>

#include "Game.h"

namespace DT {
class MainWindow;
}

class DT::MainWindow: public QWidget {
    Q_OBJECT
private:
    Game * _game;
    QBoxLayout * _layout;
public:
    MainWindow();
};
#endif // MAINWINDOW_H
