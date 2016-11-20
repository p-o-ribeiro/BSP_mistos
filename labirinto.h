#ifndef LABIRINTO_H
#define LABIRINTO_H
#include <GL/glut.h>
#include <poligono.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;
class labirinto
{
public:
    labirinto(const char[]);
    void desenhaLabirinto();
    int getAltura() const;
    void setAltura(int value);

    int getLargura() const;
    void setLargura(int value);

private:
    vector<Poligono> paredes;
    int altura,largura;
    string nomeArquivo;
    void leLabirinto();


};

#endif // LABIRINTO_H
