#ifndef LABIRINTO_H
#define LABIRINTO_H
//#include <GL/glew.h>
#include <GL/glut.h>
#include <poligono.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <nodo.h>
using namespace std;
class Labirinto
{
public:
    Labirinto(const char[]);
    void desenhaLabirinto();
    void desenhaLabirintoBSP();
    int getAltura() const;
    void setAltura(int value);

    int getLargura() const;
    void setLargura(int value);
    void setPosicao(Ponto* pos);



    float getAngulo() const;
    void setAngulo(float value);

private:
    vector<Poligono> paredes;
    Nodo* arvore;
    int altura,largura;
    string nomeArquivo;
    void leLabirinto();
    Ponto* posicao;
    float angulo;

};

#endif // LABIRINTO_H
