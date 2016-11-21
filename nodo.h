#ifndef NODO_H
#define NODO_H

#include <vector>
#include "poligono.h"
#include "interseccao_retas.h"
#include <cmath>

using namespace std;

class Nodo
{
private:
    vector<Poligono> poligonos;
    Nodo* frente;
    Nodo* tras;

public:
    Nodo();
    Nodo(vector<Poligono> &poligonos);
    void divide(Poligono outro, Poligono &frente, Poligono &tras);

};

#endif // NODO_H
