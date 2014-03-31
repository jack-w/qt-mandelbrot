#ifndef CANVAS_HH
#define CANVAS_HH

#include <QWidget>

class QColor;
class QImage;
class QPoint;
class QAction;

class Canvas : public QWidget
{
    Q_OBJECT

    public:
        Canvas(QWidget *parent = 0);

    private:
        void myDrawRect(const QPoint & endPoint);

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);


        QImage image;
        int penWidth;
        QColor penColor;
        QPoint lastPoint;
        bool drawing;
};

#endif
