#include "mainWindow.h"
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QIcon>

using namespace DT;


MainWindow::MainWindow() : QWidget(0)
{
    _game = Game::instance();
    _layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    _layout->setSpacing(0);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->addItem(new QSpacerItem(0, 0));
    _layout->addWidget(_game);
    _layout->addItem(new QSpacerItem(0, 0));
    setLayout(_layout);
    setStyleSheet("background-color: black;");
    setFixedWidth(16*TILE*2);
    setFixedHeight(16*TILE*2);
    //resize(_game->aspectRatio() * 480, 480);
    setWindowTitle("DuckTales [NES]");
    setWindowIcon(QIcon(":/icons/ducktalesicon.ico"));


    //showFullScreen();
}

