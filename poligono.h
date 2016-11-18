#ifndef POLIGONO_H
#define POLIGONO_H

#include "ponto.h"

class Poligono
{
public:
    Poligono();

    Ponto p1;
    Ponto p2;
    Ponto o;

    double angle(Ponto p);

    Ponto pontoMedio();

};

#endif // POLIGONO_H
