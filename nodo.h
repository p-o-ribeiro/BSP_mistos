#ifndef NODO_H
#define NODO_H

#include <vector>
#include "poligono.h"
#include "interseccao_retas.h"
#include <cmath>
#include <vetor.h>

using namespace std;

class Nodo{
    private:
        //vector<Poligono> poligonos;



    public:
        Poligono* poligono;
        Nodo* frente = NULL;
        Nodo* atras = NULL;
        Nodo(Poligono p);
//        Nodo(vector<Poligono> poligonos);
        Nodo(vector<Poligono> poligonos);
        void divide(Poligono* outro, Poligono* &frente, Poligono* &atras);
        void adiciona(Poligono p);

        static void pintor(Nodo* arv, Ponto pos_observador);
        static void bfs(Nodo* arv);
        Nodo* maisProximo(const Ponto &posicao, double distMin);
        int testePonto(Ponto outro);
        static void drawPolygon(Nodo* arv);
};

#endif // NODO_H
