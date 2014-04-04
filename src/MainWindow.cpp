#include <QtGui>
#include "headers/MainWindow.hh"
#include "headers/Canvas.hh"


MainWindow::MainWindow()
{
    resize(QSize(300,300));
    canvas = new Canvas(this, width(), height());
    createActions();
    createMenus();
    createToolBars();


    setCentralWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete canvas;
    delete saveAsAct;
    delete quitAct;
    delete resetAct;
}

void MainWindow::saveAs()
{
    const QString fileName = QFileDialog::getSaveFileName(this);
    canvas->saveImage(fileName);
}

void MainWindow::reset()
{
    canvas->reset();
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr("&File") );
    fileMenu->addAction(quitAct);
}

void MainWindow::createToolBars()
{
    toolBar = addToolBar(tr("File"));
    toolBar->addAction(saveAsAct);
    toolBar->addAction(resetAct);
}

void MainWindow::createActions()
{
    saveAsAct = new QAction(tr("&Save As"), this);
    saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    quitAct = new QAction(tr("&quit"), this);
    quitAct->setShortcut(tr("Alt+q"));
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    resetAct = new QAction(tr("&reset"), this);
    resetAct->setShortcut(tr("Ctrl+r"));
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));
}

