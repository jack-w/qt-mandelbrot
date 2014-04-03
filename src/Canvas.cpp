#include <QtGui>
#include <QRubberBand>
#include <QDebug>
#include "headers/Canvas.hh"
#include "headers/Fractal.hh"


Canvas::Canvas(QWidget *parent, int w, int h)
    : QWidget(parent), penWidth(1), penColor(Qt::black), firstPoint(QPoint(0,0)), drawing(false)
{
    resize(QSize(w,h));
    fractal = new Fractal(width(), height());
    selection = new QRubberBand(QRubberBand::Rectangle, this);
    fractal->draw();
    setMinimumSize(QSize(300,300));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    qDebug() << "Canvas - w: " << width() << ", h: " << height();
//    qDebug() << "Fractal - w: " << fractal->getWidth() << ", h: " << fractal->getHeight();

}

Canvas::~Canvas()
{
    delete fractal;
    delete selection;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), *fractal);
}

void Canvas::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        firstPoint = event->pos();
        drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent * event)
{
    int dx = event->pos().x()-firstPoint.x();
    int dy = event->pos().y()-firstPoint.y();
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        if (dx > 0 && dy > 0) {
            selection->setGeometry(firstPoint.x(),firstPoint.y(),dx,dy);
        }
        else if (dx < 0 && dy > 0) {
            selection->setGeometry(event->pos().x(),firstPoint.y(),-dx,dy);
        }
        else if (dx > 0 && dy < 0) {
            selection->setGeometry(firstPoint.x(),event->pos().y(),dx,-dy);
        }
        else {
            selection->setGeometry(event->pos().x(),event->pos().y(),-dx,-dy);
        }

        selection->show();
    }


//    qDebug()    << "("
//                << fractal->getA1()*event->pos().x()+fractal->getT1()
//                << ","
//                << fractal->getA2()*event->pos().y()+fractal->getT2()
//                << ")";
}

void Canvas::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        secondPoint = event->pos();
        zoomIn();
        update();
        selection->hide();
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    resizeImage(fractal, event->size());
    fractal->draw();
    qDebug() << fractal->width() << " , " << fractal->height() ;
    update();
}


void Canvas::resizeImage(Fractal * fractal, const QSize & newSize)
{
    if (fractal->size() == newSize) {
        return;
    }
    Fractal newFractal(newSize.width(),newSize.height());

    QPainter painter(&newFractal);
    painter.drawImage(QPoint(0,0), *fractal);

    *fractal = newFractal;
}

void Canvas::zoomIn()
{
    fractal->changeView(firstPoint, secondPoint);
    fractal->draw();
}
