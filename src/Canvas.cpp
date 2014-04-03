#include <cmath>
#include <QtGui>
#include <QRubberBand>
#include <QDebug>
#include "headers/Canvas.hh"
#include "headers/Fractal.hh"


Canvas::Canvas(QWidget *parent, int w, int h)
  : QWidget(parent), 
    penWidth(1), 
    penColor(Qt::black), 
    firstPoint(QPoint(0,0)), 
    drawing(false), 
    zoomLevel(1.0),
    autoIterations(true)
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
//    qDebug() << fractal->width() << " , " << fractal->height() ;
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
    setZoomLevel();
    fractal->changeView(firstPoint, secondPoint);
    fractal->draw();
}

void Canvas::setZoomLevel()
{
    double delta1, delta2;
    double x1,y1, x2,y2;
    double r1,i1, r2,i2;
    x1 = firstPoint.x();
    y1 = firstPoint.y();
    x2 = secondPoint.x();
    y2 = secondPoint.y();
    delta1 = abs(x1 - x2);
    delta2 = abs(y1 - y2);
    r1 = fractal->getA1()*x1 + fractal->getT1();
    i1 = fractal->getA2()*y1 + fractal->getT2();
    r2 = fractal->getA1()*x2 + fractal->getT1();
    i2 = fractal->getA2()*y2 + fractal->getT2();
    if (width()/height() < delta1/delta2) {
        zoomLevel = zoomLevel * abs((fractal->getRu() - fractal->getRl()) / (r1-r2));
    }
    else {
        zoomLevel = zoomLevel * abs((fractal->getIu() - fractal->getIl()) / (i1-i2));
    }

//    qDebug() << zoomLevel;
    if (autoIterations == true) {
        fractal->setIterations(27*pow(zoomLevel,0.2)+100);
        qDebug() << fractal->getIterations();
    }

}
