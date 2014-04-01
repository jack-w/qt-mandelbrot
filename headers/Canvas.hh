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
        ~Canvas();

    protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);
        void resizeEvent(QResizeEvent *);

    private:
        void myDrawRect(const QPoint & endPoint);

        void resizeImage(QImage * image, const QSize & newSize);

        QImage *image;
        QImage *tmpImage;
        int penWidth;
        QColor penColor;
        QPoint lastPoint;
        bool drawing;
};

#endif
