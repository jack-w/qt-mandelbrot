#include <cmath>
#include <QImage>
#include <QDebug>
#include "headers/Fractal.hh"



Fractal::Fractal(int w, int h)
  : QImage(w,h,QImage::Format_RGB32), 
    rl(-2), 
    ru(2), 
    il(-2), 
    iu(2) 
{
    arg.cr = 0;
    arg.ci = 0;
    arg.iterations = 100;
    arg.escape = 4;
    arg.innerColor = qRgb(0,0,0);
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
    iu(old.iu) 
{
    arg.cr = 0;
    arg.ci = 0;
    arg.iterations = 100;
    arg.escape = 4;
    arg.innerColor = qRgb(0,0,0);
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
    arg.cr = old.arg.cr;
    arg.ci = old.arg.ci;
    arg.iterations = old.arg.iterations;
    arg.escape = old.arg.escape;
    arg.innerColor = old.arg.innerColor;

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
        arg.A1 = (ru-rl) / width();
        arg.A2 = (il-iu) / height();
        arg.t1 = rl;
        arg.t2 = iu;
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

Arg Fractal::getArg()
{
    return arg;
}

QList<colRange> & Fractal::accessCList()
{
    return arg.clist;
}

void Fractal::setRu(double d)
{
    ru = d;
}

void Fractal::setRl(double d)
{
    rl = d;
}

void Fractal::setIu(double d)
{
    iu = d;
}

void Fractal::setIl(double d)
{
    il = d;
}

void Fractal::setA1(double d)
{
    arg.A1 = d;
}

void Fractal::setA2(double d)
{
    arg.A2 = d;
}

void Fractal::setT1(double d)
{
    arg.t1 = d;
}

void Fractal::setT2(double d)
{
    arg.t2 = d;
}

void Fractal::setIterations(double it)
{
    arg.iterations = floor(it);
}


void Fractal::reset()
{
    ru = 2;
    rl = -2;
    iu = 2;
    il = -2;
    arg.iterations = 100;
    adjustRatio();
}

void Fractal::calculateFractal()
{
    int x,y;

    for (y = 0; y < height(); y++) {
        arg.ai = arg.A2*y + arg.t2;
        for (x = 0; x < width(); x++) {
            arg.ar = arg.A1*x + arg.t1;
//            qDebug() << x << "\t" << ar << "\t" << y << "\t" << ai;
            calc((data+x+y*width()), arg);
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
            setPixel(x,y,getColor((data+x+y*w),arg));
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
        rl = arg.A1*x1 + arg.t1;
        ru = arg.A1*x2 + arg.t1;
    }
    else {
        rl = arg.A1*x2 + arg.t1;
        ru = arg.A1*x1 + arg.t1;
    }
    if (y1 < y2) {
        iu = arg.A2*y1 + arg.t2;
        il = arg.A2*y2 + arg.t2;
    }
    else {
        iu = arg.A2*y2 + arg.t2;
        il = arg.A2*y1 + arg.t2;
    }

    adjustRatio();
}


QRgb grey(Data * data, Arg & arg)
{
    int icount;
    double count = (double)(data)->it;

    if (count > arg.iterations - 0.001) {
        return arg.innerColor;
    }
    
    count = count + 5 - log(log(data->norm + 1))/log(2);

    icount = floor(256.0*count/arg.iterations);

//    qDebug() << i << "\t" << j << "\t" << (data+i+j*width())->it;

    return qRgb(icount,icount,icount);
}


void mandelbrot(Data *data, Arg & arg)
{
    double zr=0, zi=0, tmp=0;
    int i;
    for (i = 0; i < arg.iterations && tmp < arg.escape; i++) {
        tmp = zr;
        zr = (zr + zi)*(zr - zi) + arg.ar;
        zi = 2*tmp*zi + arg.ai;

        tmp = zr*zr + zi*zi;
    }
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + arg.ar;
    zi = 2*tmp*zi + arg.ai;
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + arg.ar;
    zi = 2*tmp*zi + arg.ai;
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + arg.ar;
    zi = 2*tmp*zi + arg.ai;
    tmp = zr;
    zr = (zr + zi)*(zr - zi) + arg.ar;
    zi = 2*tmp*zi + arg.ai;

    tmp = zr*zr + zi*zi;

    data->it = i;
//    qDebug() << data->it;
    data->norm = tmp;
}
