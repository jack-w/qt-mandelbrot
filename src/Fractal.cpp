#include <cmath>
#include <QImage>
#include <QDebug>
#include "headers/Fractal.hh"



Fractal::Fractal(int w, int h)
  : width(w), 
    height(h), 
    rl(-2), 
    ru(2), 
    il(-2), 
    iu(2), 
    cr(0), 
    ci(0),
    iterations(50),
    escape(4)
{
    div = new Div[w*h];
    calc = mandelbrot;
    getColor = grey;
    adjustRatio();

    qDebug() << "Fractal :" << width;
}

Fractal::~Fractal()
{
    delete [] div;
}

void Fractal::adjustRatio()
{
    double delta;
    if (height > 0 && width > 0 && (iu-il) > 0) {
        if (width/height > (ru-rl)/(iu-il)) {
            delta = (width/height)*(iu-il);
            delta = delta - (ru-rl);
            ru += delta/2;
            rl -= delta/2;
        }
        else {
            delta = (height/width)*(ru-rl);
            delta = delta - (iu-il);
            iu += delta/2;
            il -= delta/2;
        }
        A1 = (ru-rl) / width;
        A2 = (il-iu) / height;
        t1 = rl;
        t2 = iu;
        qDebug() << rl << " " << ru << " " << il << " " << iu ;
        qDebug() << A1*0+t1 << " " << A1*width+t1 << " " << A2*height+t2 << " " << A2*0+t2 ;
    }
}

void Fractal::setWidth(int w)
{
    width = w;
}

void Fractal::setHeight(int h)
{
    height = h;
}

int Fractal::getWidth()
{
    return width;
}

int Fractal::getHeight()
{
    return height;
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
    int i,j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            ar = A1*j + t1;
            ai = A2*i + t2;
            calc((div+i*width+j), ar,ai,cr,ci,iterations,escape);
        }
    }
}

void Fractal::setImage(QImage *image)
{
    int i,j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            image->setPixel(j,i,getColor(i,j,(div+j+i*width),width,iterations,clist));
        }
    }
}

QRgb grey(int i, int j, Div * div, int width, int iterations, QList<colRange> clist)
{
    int icount;
    double count = (div+j+i*width)->it + 5 - log(log((div+j+i*width)->mag + 1))/log(2);

    if (count > iterations - 0.001) {
        return qRgb(0,0,0);
    }
    icount = floor(256*count/iterations);

    return qRgb(icount,icount,icount);
}

void mandelbrot(Div *div, double & ar, double & ai, double & cr, double & ci, int & it, double & escape)
{
    double zr=0, zi=0, tmp, abs=0;
    int i;
    for (i = 0; i < it && abs < escape; i++) {
        tmp = zr;
        zr = (zr + zi)*(zr - zi) + ar;
        zi = 2*tmp*zi + ai;

        abs = zr*zr + zi*zi;
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

    abs = zr*zr + zi*zi;

    div->it = i;
    div->mag = abs;
}
