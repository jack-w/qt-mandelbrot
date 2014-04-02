#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

class Canvas;

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();

private:
    void createMenus();

    QMenu *fileMenu;
    Canvas *canvas;
};

#endif
