#include <QApplication>
#include <QDebug>
#include "src/headers/MainWindow.hh"
#include "src/headers/Canvas.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main;

    main.show();




    return app.exec();
}
