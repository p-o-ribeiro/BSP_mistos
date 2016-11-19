#ifndef LABIRINTO_H
#define LABIRINTO_H
#include <GL/glut.h>
#include <poligono.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class labirinto
{
public:
    labirinto(const char[]);
    void desenhaLabirinto();
private:
    vector<Poligono> paredes;
    int altura,largura;
    string nomeArquivo;
    void leLabirinto();


};

#endif // LABIRINTO_H
