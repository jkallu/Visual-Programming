#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(node);

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setGeometry(0, 0, 800, 800);
    mainWindow.show();

    return app.exec();
}
