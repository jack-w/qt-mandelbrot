#ifndef FRACTAL_HH
#define FRACTAL_HH

class Fractal;
class QImage;
class QSize;
struct Div;
struct colRange;

void mandelbrot(Div *div, double & ar, double & ai, double & cr, double & ci, int & it, double & escape);

QRgb grey(Div *,int,QList<colRange> clist);

struct Div
{
    int it;
    double norm;
};

struct colRange
{
    double p;
    QRgb c;
};

class Fractal : public QImage
{
    public:
        Fractal(int width = 200, int height = 200);
        ~Fractal();

        void (*calc)(Div *div, double & ar, double & ai, double & cr, double & ci, int & it, double & escape);
        void adjustRatio();
        double getRu();
        double getRl();
        double getIu();
        double getIl();
        double getA1();
        double getA2();
        double getT1();
        double getT2();

        void calculateFractal();
        void setImage();
        QRgb (*getColor)(Div *,int,QList<colRange> clist);



    private:
        double rl,ru,il,iu;
        double A1, A2, t1, t2;
        double cr,ci;
        int iterations;
        double escape;
        Div * div;
        QList<colRange> clist;

};

#endif
