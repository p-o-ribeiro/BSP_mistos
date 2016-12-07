#ifndef VETOR_H
#define VETOR_H

#define PI 3.14159265
#include <iostream>
#include <ponto.h>
using namespace std;

struct Vetor {
    double x, y, z;
    Vetor(double x = 0, double y = 0, double z=0): x(x), y(y), z(z) {}


    Vetor operator +(Vetor q) { return Vetor(x + q.x, y + q.y,  z + q.z); }
    Vetor operator -(Vetor q) { return Vetor(x - q.x, y - q.y, z- q.z); }
    Vetor operator *(double t) { return Vetor(x * t, y * t, z * t); }
    Vetor operator /(double t) { return Vetor(x / t, y / t, z / t); }
    double operator *(Vetor q) { return x * q.x + y * q.y + z*q.z; }
    Vetor operator %(Vetor q) { return Vetor(y*q.z-z*q.y, z*q.x-x*q.z, x*q.y - y*q.x); }


    friend ostream& operator <<(ostream& o, Vetor v) {
      return o << "(" << v.x << ", " << v.y << ")";
    }
 };




#endif // VETOR_H
