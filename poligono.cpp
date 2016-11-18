#include "poligono.h"
#include "math.h"

Poligono::Poligono()
{

}

double Poligono::angle(Ponto p)
{
    Ponto m = pontoMedio();
    double vx, vy, ux, uy;
    vx = o.x-m.x;
    vy = o.y-m.y;
    ux = p.x-m.x;
    uy = p.y-m.y;

    double angle = acos( (vx*ux + vy*uy)/(sqrt(ux*ux+uy*uy)* sqrt(vx*vx+vy*vy)) );
}

Ponto Poligono::pontoMedio()
{
    Ponto medio( (p1.x-p2.x )/2, (p1.y-p2.y )/2);
    return medio;
}
