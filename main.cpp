#include "mainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    (new DT::MainWindow())->show();

    return app.exec();
}
