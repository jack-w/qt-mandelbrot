#include <QApplication>
#include "headers/MainWindow.hh"
#include "headers/Canvas.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main;

    main.show();



    return app.exec();
}
