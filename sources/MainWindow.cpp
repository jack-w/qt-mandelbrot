#include <QtGui>
#include "../headers/MainWindow.hh"
#include "../headers/Canvas.hh"


MainWindow::MainWindow()
{
    canvas = new Canvas;
    createMenus();

    resize(QSize(300,300));

    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr("&Datei") );
}
