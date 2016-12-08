#include "poligono.h"
#include "vetor.h"
#include "math.h"
#include <GL/glut.h>


Poligono::Poligono()
{

}

Ponto Poligono::pontoMedio()
{
    Ponto medio( (p2.x+p1.x )/2, (p2.y+p1.y )/2);
    return medio;
}

Ponto Poligono::pontoNormal()
{

    Vetor v = p2-p1;
    double inner = v.x/sqrt(v.x*v.x + v.y*v.y);
    double angle = acos(inner);
    Ponto normal = pontoMedio();
    normal.x+= cos(PI/2+angle)*NORMAL_OFFSET;
    normal.y+= sin(PI/2+angle)*NORMAL_OFFSET;
    return normal;
}

/**
 * @brief Poligono::pinta
 * Metodo responsavel por pintar cada parede individualmente
 */
void Poligono::pinta(){
    glColor3f(cor.r,cor.g,cor.b);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cor.material_ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cor.material_kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cor.material_ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, cor.material_ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cor.material_Se);
    double dx=(p2.x-p1.x)/10.0;
    double dy=(p2.y-p1.y)/10.0;
    double dz=altura/10.0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            glBegin(GL_POLYGON);
            glVertex3f(p1.x+dx*i, p1.y+dy*i , dz*j );
            glVertex3f(p1.x+dx*i, p1.y+dy*i , dz*(j+1) );
            glVertex3f(p1.x+dx*(i+1), p1.y+dy*(i+1) , dz*(j+1));
            glVertex3f(p1.x+dx*(i+1), p1.y+dy*(i+1) , dz*j);
            glEnd();
        }
    }
}

Poligono * Poligono::clonar(){
    Ponto p1 = Ponto(this->p1.x, this->p1.y);
    Ponto p2 = Ponto(this->p2.x, this->p2.y);
    return new Poligono(p1, p2);
}

Cor::Cor()
{
    r=(rand()%100)/100.f;
    g=(rand()%100)/100.f;
    b=(rand()%100)/100.f;
    for (int i=0;i<3;i++){
        material_ka[i]=(rand()%5)/100.f;
        material_kd[i]=0.5f+(rand()%50)/100.f;
        material_ks[i]=0.5f+(rand()%50)/100.f;
    }
    material_ka[3]=1.0f;
    material_kd[3]=1.0f;
    material_ks[3]=1.0f;
    material_ke[0]=0.1f;
    material_ke[1]=0.0f;
    material_ke[2]=0.0f;
    material_ke[3]=0.0f;
}
Cor& Cor::operator=(const Cor& other) // copy assignment
{
    this->r=other.r;
    this->g=other.g;
    this->b=other.b;
    for(int i=0;i<4;i++){
        this->material_ka[i]=other.material_ka[i];
        this->material_kd[i]=other.material_kd[i];
        this->material_ke[i]=other.material_ke[i];
        this->material_ks[i]=other.material_ks[i];
    }
    return *this;
}
