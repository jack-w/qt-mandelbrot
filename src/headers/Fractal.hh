#ifndef FRACTAL_HH
#define FRACTAL_HH

class Fractal;
class QImage;
class QSize;
struct Data;
struct colRange;
struct Arg;

void mandelbrot(Data *data, Arg & arg);

QRgb grey(Data *,Arg & arg);

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

struct Arg
{
    double A1;
    double A2;
    double t1;
    double t2;

    double ar;
    double ai;
    double cr;
    double ci;
    double iterations;
    double escape;
    QRgb innerColor;
    QList<colRange> clist;
};

class Fractal : public QImage
{
//    Q_OBJECT
    public:
        Fractal(int width = 200, int height = 200);
        Fractal(Fractal & old);
        Fractal & operator=(Fractal & old);
        ~Fractal();

        void (*calc)(Data *data, Arg & arg);
        void adjustRatio();

        double getRu();
        double getRl();
        double getIu();
        double getIl();
        Arg getArg();

        QList<colRange> & accessCList();

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
        QRgb (*getColor)(Data *data,Arg & arg);

        void draw();

        void changeView(QPoint p1, QPoint p2);


    private:
        double rl,ru,il,iu;
        Arg arg;
        Data * data;

};

#endif
