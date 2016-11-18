#include "interseccao_retas.h"

point line_intersect(point p, point q, point r, point s) {
   point a = q - p, b = s - r, c = point(p % q, r % s);
   return point(point(a.x, b.x) % c, point(a.y, b.y) % c) / (a % b);
}
