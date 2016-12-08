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
}
void Labirinto::leLabirinto()
{
    fstream arquivo;
    arquivo.open (nomeArquivo, std::fstream::in);
    if(!arquivo.is_open()){
        cout<<"Arquivo "<<nomeArquivo<<" não foi aberto"<<endl;
        return;
    }
    //Quantidade de paredes do arquivo
    int numeroParedes;
    arquivo>>altura>>largura>>numeroParedes;
    paredes.resize(numeroParedes);
    //Leitura de cada parede
    for (int i=0;i<numeroParedes;i++){
        arquivo>>paredes[i].p1.y>>paredes[i].p1.x;
        arquivo>>paredes[i].p2.y>>paredes[i].p2.x;
    }

}

float Labirinto::getAngulo() const
{
    return angulo;
}

void Labirinto::setAngulo(float value)
{
    angulo = value;
}


void Labirinto::setPosicao(Ponto* pos){
    this->posicao = pos;
}


//Funcao inicial de desenho antes do uso de BSP
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


/**
 * @brief Labirinto::desenhaLabirintoBSP
 *
 * Rotina grafica principal do projeto, responsavel por definicoes de
 * iluminacao e chamada do algoritmo do pintor para as paredes
 */
void Labirinto::desenhaLabirintoBSP()
{

    //Definicoes de material para o piso
    GLfloat material_Ka[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
    GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
    GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
    GLfloat material_Se = 20.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
    glColor3f(0.5f,1.0f,1.0f);
    double dx=largura/10.0;
    double dy=altura/10.0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            glBegin(GL_POLYGON);
            glVertex3f(dx*i, dy*j ,0);
            glVertex3f(dx*(i+1), dy*j ,0 );
            glVertex3f(dx*(i+1), dy*(j+1) ,0);
            glVertex3f(dx*i, dy*(j+1) ,0);
            glEnd();
        }
    }


    double x =  posicao->x-1*sin((angulo)*PI/180);
    double y =  posicao->y-1*cos((angulo)*PI/180);
    Ponto pos2 = Ponto(x,y); // Ponto deslocado conforme angulo de visao
    //Algoritmo do pintor:
    Nodo::pintor(arvore, pos2);

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


