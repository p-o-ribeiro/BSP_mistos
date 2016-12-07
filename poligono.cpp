#include "poligono.h"
#include "vetor.h"
#include "math.h"
#include <GL/glut.h>


Poligono::Poligono()
{

}

//double Poligono::produtoVetorial(Ponto p)
//{
//    Ponto vetor=p2-p1;
//    p=p-p1;
//    return vetor%p;
//}


//double Poligono::dot_product(Ponto p)
//{
//    Ponto m = pontoMedio();
//    double vx, vy, ux, uy;
//    vx = o.x-m.x;
//    vy = o.y-m.y;
//    ux = p.x-m.x;
//    uy = p.y-m.y;

//    double dot_product = vx*ux + vy*uy;
//    return dot_product;
//}

//double Poligono::angle(Ponto p)
//{
//    Ponto m = pontoMedio();
//    double vx, vy, ux, uy;
//    vx = o.x-m.x;
//    vy = o.y-m.y;
//    ux = p.x-m.x;
//    uy = p.y-m.y;

//    double angle = acos( (vx*ux + vy*uy)/(sqrt(ux*ux+uy*uy)* sqrt(vx*vx+vy*vy)) );
//    return angle;
//}

Ponto Poligono::pontoMedio()
{
    Ponto medio( (p2.x+p1.x )/2, (p2.y+p1.y )/2);
    return medio;
}

Ponto Poligono::pontoNormal()
{
//    cout << "CHAMADA pontoNormal()" << endl;
    Vetor v = p2-p1;
//    cout << p1 << endl;
//    cout << p2 << endl;
//    cout << "Vetor em questao "<< v.x << ","<< v.y << endl;
//    cout << "operacao "<< v.x*v.x + v.y*v.y << endl;
    double inner = v.x/sqrt(v.x*v.x + v.y*v.y);
//    cout << "inner " << inner << endl;
    double angle = acos(inner);
    Ponto normal = pontoMedio();
//    cout << "ponto medio ao vetor" << normal << endl;
//    cout << "angulo " << angle << endl;
    normal.x+= cos(PI/2+angle)*NORMAL_OFFSET;
    normal.y+= sin(PI/2+angle)*NORMAL_OFFSET;
//    cout << "ponto normal ao vetor" << normal << endl;
//    cout << "FIM CHAMADA pontoNormal()" << endl;
    return normal;
}


void Poligono::pinta(){
    glColor3f(cor.r,cor.g,cor.b);
    glBegin(GL_POLYGON);
    glVertex3f(p1.x, p1.y , 0.f );
    glVertex3f(p1.x, p1.y , altura );
    glVertex3f(p2.x, p2.y , altura);
    glVertex3f(p2.x, p2.y ,0.f);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(p1.x, p1.y , 0.f );
    glVertex3f(p1.x, p1.y , altura );
    glVertex3f(p2.x, p2.y , altura);
    glVertex3f(p2.x, p2.y ,0.f);
    glEnd();
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
}
