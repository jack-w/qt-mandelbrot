#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

class Canvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private slots:
    void saveAs();
    void reset();

private:
    void createMenus();
    void createToolBars();
    void createActions();

    Canvas *canvas;

    QMenu *fileMenu;
    QToolBar *toolBar;

    QAction *resetAct;
    QAction *saveAsAct;
    QAction *quitAct;
};

#endif
