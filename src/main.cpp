#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow(4);
    mainWindow.showFullScreen();
    return app.exec();
}
