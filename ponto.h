#ifndef PONTO_H
#define PONTO_H

#define PI 3.14159265
#include<iostream>
#include <math.h>
#include <vetor.h>

using namespace std;

struct Ponto {
    double x, y, z;
    Ponto(double x = 0, double y = 0): x(x), y(y) {}


    Vetor operator +(Ponto q) { return Vetor(x + q.x, y + q.y); }
    Vetor operator -(Ponto q) { return Vetor(x - q.x, y - q.y); }
    Vetor operator *(double t) { return Vetor(x * t, y * t); }
    Vetor operator /(double t) { return Vetor(x / t, y / t); }

    double operator !() { return sqrt(x * x + y*y); } // Distancia da origem (modulo)


    friend ostream& operator <<(ostream& o, Ponto p) {
      return o << "(" << p.x << ", " << p.y << ")";
    }
 };






#endif // PONTO_H
