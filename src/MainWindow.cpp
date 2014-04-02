#include <QtGui>
#include "headers/MainWindow.hh"
#include "headers/Canvas.hh"


MainWindow::MainWindow()
{
    resize(QSize(300,300));
    canvas = new Canvas(this, width(), height());
    createMenus();


    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr("&Datei") );
}
