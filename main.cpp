//#include <QCoreApplication>
#include "interseccao_retas.h"
#include "ponto.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    Ponto p1 (0,0);
    Ponto p2 (2,0);

    Ponto p3 (0,2);
    Ponto p4 (2,2);

    Ponto pi;
    double s, t;

    pi = intersec2d(p1, p2, p3, p4, s, t);
    //return a.exec();
}
