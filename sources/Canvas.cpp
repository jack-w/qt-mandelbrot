#include <QtGui>
#include "../headers/Canvas.hh"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent), penWidth(1), penColor(Qt::black), drawing(false)
{
    image.fill(qRgb(200,200,200));
    setMinimumSize(QSize(300,300));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
}

void Canvas::myDrawRect(const QPoint & endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(lastPoint.x(),lastPoint.y(), lastPoint.x() - endPoint.x(),lastPoint.y() - endPoint.y());

    int rad = (penWidth/2) + 1;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad,-rad,rad,rad));
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    qDebug() << image.size();
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        myDrawRect(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), image);
}
