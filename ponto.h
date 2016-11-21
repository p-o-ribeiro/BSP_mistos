#ifndef PONTO_H
#define PONTO_H

#define PI 3.14159265
#include<iostream>
using namespace std;

struct Ponto {
    double x, y;
    Ponto(double x = 0, double y = 0): x(x), y(y) {}


    Ponto operator +(Ponto q) { return Ponto(x + q.x, y + q.y); }
    Ponto operator -(Ponto q) { return Ponto(x - q.x, y - q.y); }
    Ponto operator *(double t) { return Ponto(x * t, y * t); }
    Ponto operator /(double t) { return Ponto(x / t, y / t); }
    double operator *(Ponto q) { return x * q.x + y * q.y; }
    double operator %(Ponto q) { return x * q.y - y * q.x; }


    friend ostream& operator <<(ostream& o, Ponto p) {
      return o << "(" << p.x << ", " << p.y << ")";
    }
 };





#endif // PONTO_H
