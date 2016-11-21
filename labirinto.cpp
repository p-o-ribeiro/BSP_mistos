#include "labirinto.h"

labirinto::labirinto(const char nomeArquivo[])
{
    this->nomeArquivo=nomeArquivo;
    leLabirinto();
    Arvore= new Nodo(paredes);
}
void labirinto::leLabirinto()
{
    fstream arquivo;
    arquivo.open (nomeArquivo, std::fstream::in);
    if(!arquivo.is_open()){
        cout<<"Arquivo "<<nomeArquivo<<" não foi aberto"<<endl;
        return;
    }
    int numeroParedes;
    arquivo>>altura>>largura>>numeroParedes;
    paredes.resize(numeroParedes);
    for (int i=0;i<numeroParedes;i++){
        arquivo>>paredes[i].p1.y>>paredes[i].p1.x;
        arquivo>>paredes[i].p2.y>>paredes[i].p2.x;
    }

}
void labirinto::desenhaLabirinto(){
    //glPushMatrix();
    glColor3f(0.5f,1.0f,1.0f);
    glBegin(GL_POLYGON);
    glVertex3f(0.f  , 0.f , 0.f );
    glVertex3f(0.f, altura , 0.f );
    glVertex3f(largura, altura ,0.f);
    glVertex3f(largura  , 0.f ,0.f);
    glEnd();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.f  , 0.f , 0.f );
    glVertex3f(0.f, altura , 0.f );
    glVertex3f(largura, altura ,0.f);
    glVertex3f(largura  , 0.f ,0.f);
    glEnd();
    for (uint i=0;i<paredes.size();i++){
    glColor3f(paredes[i].cor.r,paredes[i].cor.g,paredes[i].cor.b);
    glBegin(GL_POLYGON);
    glVertex3f(paredes[i].p1.x  , paredes[i].p1.y , 0.f );
    glVertex3f(paredes[i].p1.x, paredes[i].p1.y , paredes[i].altura );
    glVertex3f(paredes[i].p2.x, paredes[i].p2.y ,paredes[i].altura);
    glVertex3f(paredes[i].p2.x, paredes[i].p2.y ,0.f);
    glEnd();
    }

    for (uint i=0;i<paredes.size();i++){

        glColor3f(0.0f,0.0f,0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(paredes[i].p1.x  , paredes[i].p1.y , 0.f );
        glVertex3f(paredes[i].p1.x, paredes[i].p1.y , paredes[i].altura );
        glVertex3f(paredes[i].p2.x, paredes[i].p2.y ,paredes[i].altura);
        glVertex3f(paredes[i].p2.x, paredes[i].p2.y ,0.f);
        glEnd();
    }
    glPopMatrix();

}

void labirinto::desenhaLabirintoBSP()
{

}
int labirinto::getAltura() const
{
    return altura;
}

void labirinto::setAltura(int value)
{
    altura = value;
}
int labirinto::getLargura() const
{
    return largura;
}

void labirinto::setLargura(int value)
{
    largura = value;
}


