#include "labirinto.h"

Labirinto::Labirinto(const char nomeArquivo[])
{
    this->nomeArquivo=nomeArquivo;
    leLabirinto();

    arvore= new Nodo(paredes.back());
    paredes.pop_back();
    while(!paredes.empty()){
        arvore->adiciona(paredes.back());
        paredes.pop_back();
    }
    cout << "adiciona OK" << endl;
}
void Labirinto::leLabirinto()
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

float *Labirinto::getAngulo() const
{
    return angulo;
}

void Labirinto::setAngulo(float *value)
{
    angulo = value;
}


void Labirinto::setPosicao(Ponto* pos){
    this->posicao = pos;
}

void Labirinto::desenhaLabirinto(){
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
        glVertex3f(paredes[i].p1.x, paredes[i].p1.y , 0.f );
        glVertex3f(paredes[i].p1.x, paredes[i].p1.y , paredes[i].altura );
        glVertex3f(paredes[i].p2.x, paredes[i].p2.y ,paredes[i].altura);
        glVertex3f(paredes[i].p2.x, paredes[i].p2.y ,0.f);
        glEnd();
    }
    glPopMatrix();

}

void Labirinto::desenhaLabirintoBSP()
{
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

//    Ponto pos_teste(20,20);
//    cout << "Copiado" << (*posicao) << endl;
//    double distMin = !(paredes[0].pontoMedio()-(*posicao));
//    Nodo* proximo = arvore->maisProximo((*posicao), distMin);
    //cout << proximo->poligono.p1 << " - " << proximo->poligono.p2 << endl;

    double x =  posicao->x+5*cos((*angulo)*PI/180);
    double y =  posicao->y+5*cos((*angulo)*PI/180);
    Ponto pos2 = Ponto(x,y);

    Vetor normal = pos2 - (*posicao);
    Nodo::pintor(arvore, *posicao);



}
int Labirinto::getAltura() const
{
    return altura;
}

void Labirinto::setAltura(int value)
{
    altura = value;
}
int Labirinto::getLargura() const
{
    return largura;
}

void Labirinto::setLargura(int value)
{
    largura = value;
}


