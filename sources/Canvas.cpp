#include <QtGui>
#include "../headers/Canvas.hh"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent), penWidth(1), penColor(Qt::black), lastPoint(QPoint(0,0)), drawing(false)
{
    image = new QImage(width(),height(), QImage::Format_RGB32);
    tmpImage = new QImage(width(),height(), QImage::Format_RGB32);
    image->fill(qRgb(255,255,255));
    tmpImage->fill(qRgb(255,255,255));
    setMinimumSize(QSize(300,300));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
}

Canvas::~Canvas()
{
    delete image;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), *tmpImage);
}

void Canvas::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent * event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        myDrawRect(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    resizeImage(image, event->size());
    update();
}

void Canvas::myDrawRect(const QPoint & endPoint)
{
    *tmpImage = *image;
    QPainter painter(tmpImage);
    painter.setPen(QPen(penColor,penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(lastPoint.x(), lastPoint.y(), endPoint.x()-lastPoint.x(), endPoint.y()-lastPoint.y());

    int rad = (penWidth/2) + 50;
    update(QRect(lastPoint,endPoint).normalized().adjusted(-rad,-rad,rad,rad));
}

void Canvas::resizeImage(QImage * image, const QSize & newSize)
{
    if (image->size() == newSize) {
        return;
    }
    QImage newImage(newSize, QImage::Format_RGB32);

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);

    *image = newImage;
}
