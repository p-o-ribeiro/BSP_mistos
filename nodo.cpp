#include "nodo.h"



Nodo::Nodo(vector<Poligono> poligonos){


    Poligono frente;
    Poligono atras;



}


void Nodo::divide(Poligono outro, Poligono &frente, Poligono &tras){
    double s,t;
    int i = intersec2d(poligono.p1, poligono.p2, outro.p1, outro.p2, s, t);

    double a1 = poligono.angle(outro.p1);
    double a2 = poligono.angle(outro.p2);


    //Caso encontre interseccao
    if(i != 0){
        Ponto pi;
        pi.x = poligono.p1.x + (poligono.p2.x-poligono.p1.x)*s;
        pi.y = poligono.p1.y + (poligono.p2.y-poligono.p1.y)*s;

        if(abs(a1) < (PI / 2)){
            frente.p1 = outro.p1;
        }else{
            tras.p1 = outro.p1;
        }


        if(abs(a2) < (PI / 2)){
            frente.p1 = outro.p2;
        }else{
            tras.p1 = outro.p2;
        }

        //Amboss nodos compartilham o ponto de interseccao
        frente.p2 = pi;
        tras.p2 = pi;

    //Caso nao encontre interseccao
    }else{
        if(abs(a1) < (PI / 2)){
            frente.p1 = outro.p1;
            frente.p2 = outro.p2;
        }else{
            tras.p1 = outro.p1;
            tras.p2 = outro.p2;
        }
    }

}
