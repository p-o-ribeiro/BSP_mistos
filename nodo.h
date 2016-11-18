#ifndef NODO_H
#define NODO H

#include <vector>
#include "poligono.h"

using namespace std;

class Nodo
{
public:
    Nodo(vector<Poligono> poligonos);
    Poligono nodo;
    Nodo* frente;
    Nodo* tras;

    void divide(Poligono outro, Poligono &frente, Poligono &tras);

};

#endif // NODO
