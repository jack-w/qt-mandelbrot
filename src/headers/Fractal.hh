#ifndef FRACTAL_HH
#define FRACTAL_HH

class Fractal;
class QImage;
class QSize;
struct Data;
struct colRange;

void mandelbrot(Data *data, double & ar, double & ai, double & cr, double & ci, int & it, double & escape);

QRgb grey(Data *,int,QList<colRange> clist);

struct Data
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
//    Q_OBJECT
    public:
        Fractal(int width = 200, int height = 200);
        Fractal(Fractal & old);
        Fractal & operator=(Fractal & old);
        ~Fractal();

        void (*calc)(Data *data, double & ar, double & ai, double & cr, double & ci, int & it, double & escape);
        void adjustRatio();

        double getRu();
        double getRl();
        double getIu();
        double getIl();
        double getA1();
        double getA2();
        double getT1();
        double getT2();
        int getIterations();

        void setRu(double );
        void setRl(double );
        void setIu(double );
        void setIl(double );
        void setA1(double );
        void setA2(double );
        void setT1(double );
        void setT2(double );
        void setIterations(double);

        void reset();

        void calculateFractal();
        void setImage();
        QRgb (*getColor)(Data *,int,QList<colRange> clist);

        void draw();

        void changeView(QPoint p1, QPoint p2);


    private:
        double rl,ru,il,iu;
        double A1, A2, t1, t2;
        double cr,ci;
        int iterations;
        double escape;
        Data * data;
        QList<colRange> clist;

};

#endif
