#ifndef POLIGONO_H
#define POLIGONO_H
#define NORMAL_OFFSET  1.0

#include "ponto.h"
#include <GL/glut.h>
#include <vector>
using namespace std;
class Cor{
public:
    Cor();
    float r;
    float g;
    float b;
    GLfloat material_ka[4];
    GLfloat material_kd[4];
    GLfloat material_ks[4];
    GLfloat material_ke[4];

    GLfloat material_Se = 20.0f;

    Cor& operator=(const Cor& other);

    friend ostream& operator <<(ostream& o, Cor p) {
      return o << "(red: " << p.r << ", green: " << p.g << ", blue: " << p.b << ")";
    }
};

class Poligono
{
public:
    Poligono();
    Poligono(Ponto p1, Ponto p2){
        this->p1 = p1;
        this->p2 = p2;
    }
    Ponto p1;
    Ponto p2;

//    double produtoVetorial(Ponto p);
    Cor cor;
    float altura = 1;

//    double angle(Ponto p);
    Ponto pontoMedio();
    Ponto pontoNormal();

    friend ostream& operator <<(ostream& o, Poligono p) {
      return o << "(" << p.p1.x << ", " << p.p1.y << ")" << "-> (" << p.p2.x << ", " << p.p2.y << ")";
    }

    Poligono* clonar();
    void pinta();
};

#endif // POLIGONO_H
