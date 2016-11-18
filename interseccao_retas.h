#ifndef INTERSECCAO_RETAS_H
#define INTERSECCAO_RETAS_H

#include "ponto.h"
#include "poligono.h"


int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double &s, double &t)
{
 double det;

 det = (n.x - m.x) * (l.y - k.y)  -  (n.y - m.y) * (l.x - k.x);

 if (det == 0.0)
  return 0 ; // não há intersecção

  s = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x))/ det ;
  t = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x))/ det ;

 return 1; // há intersecção
}


#endif // INTERSECCAO_RETAS_H
