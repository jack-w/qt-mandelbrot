#include <QtGui>
#include <QRubberBand>
#include "../headers/Canvas.hh"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent), penWidth(1), penColor(Qt::black), firstPoint(QPoint(0,0)), drawing(false)
{
    image = new QImage(width(),height(), QImage::Format_RGB32);
    selection = new QRubberBand(QRubberBand::Rectangle, this);
    image->fill(qRgb(55,155,255));
    setMinimumSize(QSize(300,300));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
}

Canvas::~Canvas()
{
    delete image;
    delete selection;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), *image);
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


void Canvas::resizeImage(QImage * image, const QSize & newSize)
{
    if (image->size() == newSize) {
        return;
    }
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);

    *image = newImage;
}
