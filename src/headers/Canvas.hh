#ifndef CANVAS_HH
#define CANVAS_HH

#include <QWidget>
#include <QRubberBand>

class QColor;
class QImage;
class QPoint;
class QAction;
class Fractal;

class Canvas : public QWidget
{
    Q_OBJECT

    public:
        Canvas(QWidget *parent = 0, int w = 300, int h = 300);
        ~Canvas();

        bool saveImage(const QString & fileName, const char * fileFormat = NULL);
        void reset();


    protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);
        void resizeEvent(QResizeEvent *);

    private:
        void resizeImage(Fractal *fractal, const QSize & newSize);
        void zoomIn();
        void setZoomLevel();

        Fractal *fractal;
        QRubberBand *selection;
        QPoint firstPoint, secondPoint;
        bool drawing;
        double zoomLevel;
        bool autoIterations;
};

#endif
