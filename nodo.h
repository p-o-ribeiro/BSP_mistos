#ifndef NODO_H
#define NODO_H

#include <vector>
#include "poligono.h"
#include "interseccao_retas.h"
#include <cmath>

using namespace std;

class Nodo
{
public:
    Nodo(vector<Poligono> poligonos);
    Poligono poligono;
    Nodo* frente;
    Nodo* tras;

private:
    void divide(Poligono outro, Poligono &frente, Poligono &tras);

};

#endif // NODO_H
