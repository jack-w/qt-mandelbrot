#ifndef FRACTAL_HH
#define FRACTAL_HH

class Fractal;
class QImage;
class QSize;
struct Div;
struct colRange;

struct Div
{
    int it;
    double mag;
    QRgb color;
};

struct colRange
{
    double p;
    QRgb c;
};

class Fractal
{
    public:
        Fractal(int width = 200, int height = 200);
        ~Fractal();

        void (*calc)(Div *div, double & ar, double & ai, double & cr, double & ci, int & it, double & escape);
        void adjustRatio();
        void setWidth(int);
        void setHeight(int);
        int getWidth();
        int getHeight();
        double getRu();
        double getRl();
        double getIu();
        double getIl();
        double getA1();
        double getA2();
        double getT1();
        double getT2();

        void calculateFractal();
        void setImage(QImage *image);
        QRgb (*getColor)(int,int,Div *,int,int,QList<colRange> clist);


    private:
        int width, height;
        double rl,ru,il,iu;
        double A1, A2, t1, t2;
        double cr,ci;
        int iterations;
        double escape;
        Div * div;
        QList<colRange> clist;

};

void mandelbrot(Div *div, double & ar, double & ai, double & cr, double & ci, int & it, double & escape);

QRgb grey(int,int,Div *,int,int,QList<colRange> clist);
#endif
