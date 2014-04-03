#include <cmath>
#include <QImage>
#include <QDebug>
#include "headers/Fractal.hh"



Fractal::Fractal(int w, int h)
  : QImage(w,h,QImage::Format_RGB32), 
    rl(-2), 
    ru(2), 
    il(-2), 
    iu(2), 
    cr(0), 
    ci(0),
    iterations(50),
    escape(4)
{
    data = new Data[w*h];
    calc = mandelbrot;
    getColor = grey;
    adjustRatio();


//    qDebug() << "Fractal :" << width();
}

Fractal::Fractal(Fractal & old)
  : QImage(old.width(),old.height(),QImage::Format_RGB32),
    rl(old.rl), 
    ru(old.ru), 
    il(old.il), 
    iu(old.iu), 
    cr(old.cr), 
    ci(old.ci),
    iterations(old.iterations),
    escape(old.escape)
{
    data = new Data[width()*height()];
    for (int i = 0; i < width()*height(); i++) {
        (data+i)->it = (old.data+i)->it;
        (data+i)->norm = (old.data+i)->norm;
    }
}

Fractal & Fractal::operator=(Fractal & old)
{
    QImage::operator=(old);

    rl = old.rl;
    ru = old.ru;
    il = old.il;
    iu = old.iu;
    cr = old.cr;
    ci = old.ci;
    iterations = old.iterations;
    escape = old.escape;

    adjustRatio();

    delete [] data;
    data = new Data[old.width()*old.height()];

    return *this;
}

Fractal::~Fractal()
{
    delete [] data;
}

void Fractal::adjustRatio()
{
    double delta;
    if (height() > 0 && width() > 0 && (iu-il) > 0) {
        if ((double)width()/height() > (ru-rl)/(iu-il)) {
            delta = ((double)width()/height())*(iu-il);
            delta = delta - (ru-rl);
            ru += delta/2;
            rl -= delta/2;
        }
        else {
            delta = ((double)height()/width())*(ru-rl);
            delta = delta - (iu-il);
            iu += delta/2;
            il -= delta/2;
        }
        A1 = (ru-rl) / width();
        A2 = (il-iu) / height();
        t1 = rl;
        t2 = iu;
//        qDebug() << rl << " " << ru << " " << il << " " << iu ;
//        qDebug() << A1*0+t1 << " " << A1*width()+t1 << " " << A2*height()+t2 << " " << A2*0+t2 ;
    }
}


double Fractal::getRu()
{
    return ru;
}

double Fractal::getRl()
{
    return rl;
}

double Fractal::getIu()
{
    return iu;
}

double Fractal::getIl()
{
    return il;
}

double Fractal::getA1()
{
    return A1;
}

double Fractal::getA2()
{
    return A2;
}

double Fractal::getT1()
{
    return t1;
}

double Fractal::getT2()
{
    return t2;
}

void Fractal::calculateFractal()
{
    double ar, ai;
    int x,y;

    for (y = 0; y < height(); y++) {
        ai = A2*y + t2;
        for (x = 0; x < width(); x++) {
            ar = A1*x + t1;
//            qDebug() << x << "\t" << ar << "\t" << y << "\t" << ai;
            calc((data+x+y*width()), ar,ai,cr,ci,iterations,escape);
//            qDebug() << x << y << (data+x+y*width())->it;
        }
//        qDebug() << "";
    }
}

void Fractal::setImage()
{
    int x,y;
    int w=width();
    for (y = 0; y < height(); y++) {
        for (x = 0; x < width(); x++) {
            setPixel(x,y,getColor((data+x+y*w),iterations,clist));
        }
//        qDebug() << "" ;
    }
}

void Fractal::draw()
{
    adjustRatio();
    calculateFractal();
    setImage();
}

void Fractal::changeView(QPoint p1, QPoint p2)
{
    double x1=p1.x(),x2=p2.x(),y1=p1.y(),y2=p2.y();

    if (x1 < x2) {
        rl = A1*x1 + t1;
        ru = A1*x2 + t1;
    }
    else {
        rl = A1*x2 + t1;
        ru = A1*x1 + t1;
    }
    if (y1 < y2) {
        iu = A2*y1 + t2;
        il = A2*y2 + t2;
    }
    else {
        iu = A2*y2 + t2;
        il = A2*y1 + t2;
    }

    adjustRatio();
}


QRgb grey(Data * data, int iterations, QList<colRange> clist)
{
    int icount;
    double count = (double)(data)->it + 5 - log(log(data->norm + 1))/log(2);

    if (count > iterations - 0.001) {
        return qRgb(0,0,0);
    }
    icount = floor(256.0*count/iterations);

//    qDebug() << i << "\t" << j << "\t" << (data+i+j*width())->it;

    return qRgb(icount,icount,icount);
}

void mandelbrot(Data *data, double & ar, double & ai, double & cr, double & ci, int & it, double & escape)
{
    double zr=0, zi=0, tmp=0;
    int i;
    for (i = 0; i < it && tmp < escape; i++) {
        tmp = zr;
        zr = (zr + zi)*(zr - zi) + ar;
        zi = 2*tmp*zi + ai;

        tmp = zr*zr + zi*zi;
    }
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + ar;
    zi = 2*tmp*zi + ai;
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + ar;
    zi = 2*tmp*zi + ai;
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + ar;
    zi = 2*tmp*zi + ai;
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + ar;
    zi = 2*tmp*zi + ai;

    tmp = zr*zr + zi*zi;

    data->it = i;
//    qDebug() << data->it;
    data->norm = tmp;
}
