#include "nodo.h"

Ponto interseccao(Poligono p, Poligono q)
{
    Ponto r;
    Ponto k=p.p1,l=p.p2,m=q.p1,n=q.p2;
    double det;

    det = (n.x - m.x) * (l.y - k.y)  -  (n.y - m.y) * (l.x - k.x);

    if (det == 0.0)
        return 0 ; // não há intersecção

    r.x = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x))/ det ;
    r.y = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x))/ det ;
    return r;
}

Nodo::Nodo(vector<Poligono> &poligonos){

    vector<Poligono> frente,tras;
    this->poligonos.push_back(poligonos.back());//escolhe um
    poligonos.pop_back();
    Poligono p=this->poligonos.front();
    for(int i=0;i<poligonos.size();i++){//para toda lista de poligonos
        if (p.produtoVetorial(poligonos[i].p1)==0 && p.produtoVetorial(poligonos[i].p2)==0){//na mesma linha
            this->poligonos.push_back(poligonos[i]);
        }
        else if (p.produtoVetorial(poligonos[i].p1)>=0 && p.produtoVetorial(poligonos[i].p2)>=0){//na frente
            frente.push_back(poligonos[i]);
        }
        else if(p.produtoVetorial(poligonos[i].p1)<=0 && p.produtoVetorial(poligonos[i].p2)<=0){//atras
            tras.push_back(poligonos[i]);
        }
        else{//parte na frente parte atras
            Poligono pfrente,ptras;
            Ponto intersec=interseccao(p,poligonos[i]);
            if(p.produtoVetorial(poligonos[i].p1)<=0){
                pfrente.p1=poligonos[i].p1;
                pfrente.p2=intersec;
                frente.push_back(pfrente);
                ptras.p1=poligonos[i].p2;
                ptras.p2=intersec;
                frente.push_back(ptras);
            }
            else{
                pfrente.p1=poligonos[i].p2;
                pfrente.p2=intersec;
                frente.push_back(pfrente);
                ptras.p1=poligonos[i].p1;
                ptras.p2=intersec;
                frente.push_back(ptras);
            }
        }
    }
    if(!frente.empty()) //aplica o algoritmo pros nodos da frente
        this->frente = new Nodo(frente);
    else
        this->frente=NULL;
    if(!tras.empty())//aplica o algoritmo pros nodos de tras
        this->tras = new Nodo (tras);
    else
        this->tras=NULL;
}

/**
 * @brief Nodo::divide
 * @param outro
 * @param frente
 * @param tras
 *
 *  Funcao responsavel por comparar o nodo a um poligono fora da arvore BSP.
 *  Divide o poligono externo em dois caso haja intersecao
 */

void Nodo::divide(Poligono outro, Poligono &frente, Poligono &tras){
    Poligono p= this->poligonos.front();
    if (p.produtoVetorial(outro.p1)>=0 && p.produtoVetorial(outro.p2)>=0){//na frente

    }
    else if(p.produtoVetorial(outro.p1)<=0 && p.produtoVetorial(outro.p2)<=0){//atras

    }
    else{//parte na frente parte atras

    }

    //    double s,t;
    //    int i = intersec2d(poligonos.p1, poligonos.p2, outro.p1, outro.p2, s, t);

    //    double a1 = poligonos.angle(outro.p1);
    //    double a2 = poligonos.angle(outro.p2);


    //    //Caso encontre interseccao
    //    if(i != 0){
    //        Ponto pi;
    //        pi.x = poligonos.p1.x + (poligonos.p2.x-poligonos.p1.x)*s;
    //        pi.y = poligonos.p1.y + (poligonos.p2.y-poligonos.p1.y)*s;

    //        if(abs(a1) < (PI / 2)){
    //            frente.p1 = outro.p1;
    //        }else{
    //            tras.p1 = outro.p1;
    //        }


    //        if(abs(a2) < (PI / 2)){
    //            frente.p1 = outro.p2;
    //        }else{
    //            tras.p1 = outro.p2;
    //        }

    //        //Amboss nodos compartilham o ponto de interseccao
    //        frente.p2 = pi;
    //        tras.p2 = pi;

    //    //Caso nao encontre interseccao
    //    }else{
    //        if(abs(a1) < (PI / 2)){
    //            frente.p1 = outro.p1;
    //            frente.p2 = outro.p2;
    //        }else{
    //            tras.p1 = outro.p1;
    //            tras.p2 = outro.p2;
    //        }
    //    }

}
