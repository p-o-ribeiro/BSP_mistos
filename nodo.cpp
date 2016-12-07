#include "nodo.h"
#include "vetor.h"
#include <GL/glut.h>

#define FRENTE 1
#define COLINEAR 2
#define ATRAS 3


int vezes = 0;

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


Nodo::Nodo(Poligono p){
    poligono = p.clonar();
}

//Nodo::Nodo(vector<Poligono> poligonos)
//{
//    Poligono p = poligonos.pop_back();
//    poligono = new Poligono();
//    while(!poligonos.empty()){
//        p= poligonos.back();
//        adiciona(&p);
//    }
//}



void Nodo::adiciona(Poligono p){
    //    if(p != NULL){
    if(poligono == NULL){
        poligono = p.clonar();
    }else{
        //        cout<< p << endl;
        Poligono* p_frente = NULL;
        Poligono* p_atras = NULL;
        double s,t;
        int status_i = intersec2d(poligono->p1, poligono->p2, p.p1, p.p2, s, t);
        int status_p1 = testePonto(p.p1);
        int status_p2 = testePonto(p.p2);


        if(
                (status_p1 == FRENTE && status_p2 == FRENTE) ||
                (status_p1 == COLINEAR && status_p2 == FRENTE) ||
                (status_p1 == FRENTE && status_p2 == COLINEAR) ||
                (status_p1 == COLINEAR && status_p2 == COLINEAR) //Caso especial de parede colinear em todos os pontos a parede atual
                ){
            p_frente = p.clonar();
            if(this->frente != NULL)
                this->frente->adiciona(*p_frente);
            else{
                this->frente = new Nodo(*p_frente);
            }
            return;
        }

        if(
                (status_p1 == ATRAS && status_p2 == ATRAS) ||
                (status_p1 == COLINEAR && status_p2 == ATRAS) ||
                (status_p1 == ATRAS && status_p2 == COLINEAR)
                ){
            p_atras = p.clonar();
            if(this->atras != NULL)
                this->atras->adiciona(*p_atras);
            else{
                this->atras = new Nodo(*p_atras);
            }
            return;
        }

        if(status_i != 0){
            Ponto pi;
            pi.x = poligono->p1.x + (poligono->p2.x-poligono->p1.x)*s;
            pi.y = poligono->p1.y + (poligono->p2.y-poligono->p1.y)*s;
            if(status_p1 == FRENTE){

                p_frente = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p1.x, p.p1.y));
                p_frente->cor = p.cor;
                p_atras = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p2.x, p.p2.y));
                p_atras->cor = p.cor;

                cout<<"Cores: " << p_atras->cor << " =  " << p_frente->cor << endl;

                if(this->frente != NULL)
                    this->frente->adiciona(*p_frente);
                else{
                    this->frente = new Nodo(*p_frente);
                }

                if(this->atras != NULL){
                    this->atras->adiciona(*p_atras);
                }else{
                    this->atras = new Nodo(*p_atras);
                }
            }else{

                p_frente = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p2.x, p.p2.y));
                p_frente->cor = p.cor;
                p_atras = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p1.x, p.p1.y));
                p_atras->cor = p.cor;

                cout<<"Cores: " << p_atras->cor << " =  " << p_frente->cor << endl;

                if(this->frente != NULL)
                    this->frente->adiciona(*p_frente);
                else{
                    this->frente = new Nodo(*p_frente);
                }

                if(this->atras != NULL){
                    this->atras->adiciona(*p_atras);
                }else{
                    this->atras = new Nodo(*p_atras);
                }

            }
        }



    }

    //    }

}




//Deprecado::
//Nodo* Nodo::maisProximo(const Ponto &posicao, double distMin){
//    Nodo* escolhido = NULL;
//    if(this != NULL){
//        double dist = !(this->poligono.pontoMedio() - posicao);
//        if(distMin > dist){
//           distMin = dist;
//           escolhido = this;
//        }
//        Nodo* maisProxEsq;
//        double distEsq;
//        if(this->frente !=NULL){
//            maisProxEsq = this->frente->maisProximo(posicao, dist);
//            if(maisProxEsq != NULL){
//                distEsq = !(maisProxEsq->poligono.pontoMedio() - posicao);
//                if(dist > distEsq){
//                    dist = distEsq;
//                    escolhido = maisProxEsq;
//                }
//            }
//        }

//        Nodo* maisProxDir;
//        double distDir;
//        if(this->atras !=NULL){
//            maisProxDir = this->atras->maisProximo(posicao, dist);
//            if(maisProxDir != NULL){
//                distDir = !(maisProxDir->poligono.pontoMedio() - posicao);
//                if(dist > distDir){
//                    dist = distDir;
//                    escolhido = maisProxDir;
//                }
//            }

//        }
//        return escolhido;
//    }else{
//        return NULL;
//    }
//}

void Nodo::pintor(Nodo* arv, Ponto pos_observador){
    if(arv == NULL || arv->poligono == NULL){
        return;
    }
    //Nodo folha
    if(arv->frente == NULL && arv->atras == NULL){
        arv->poligono->pinta();
    }

    Vetor normal = arv->poligono->pontoNormal() - arv->poligono->pontoMedio();
    Vetor normal_observador = pos_observador - arv->poligono->pontoMedio();
    //    bool positivo = (normal_observador * normal) >= 0;
    double escalar = (normal_observador * normal);
    if(abs(escalar)<0.0001){
        pintor(arv->frente, pos_observador);
        pintor(arv->atras, pos_observador);
        escalar = 0;
    }
    else if(escalar > 0){
        pintor(arv->atras, pos_observador);
        arv->poligono->pinta();
        pintor(arv->frente, pos_observador);
    } else {
        pintor(arv->frente, pos_observador);
        arv->poligono->pinta();
        pintor(arv->atras, pos_observador);
    }


    //    if(positivo){
    //        if(arv->frente != NULL)
    //            pintor(arv->frente, pos_observador);
    //    }else{
    //        if(arv->atras != NULL)
    //            pintor(arv->atras, pos_observador);
    //    }

    //    drawPolygon(arv);

    //    if(positivo){
    //        if(arv->atras != NULL)
    //            pintor(arv->atras, pos_observador);
    //    }else{
    //        if(arv->frente != NULL)
    //            pintor(arv->frente, pos_observador);
    //    }

}




void Nodo::drawPolygon(Nodo* arv){
    glColor3f(arv->poligono->cor.r,arv->poligono->cor.g,arv->poligono->cor.b);
    glBegin(GL_POLYGON);
    glVertex3f(arv->poligono->p1.x, arv->poligono->p1.y , 0.f );
    glVertex3f(arv->poligono->p1.x, arv->poligono->p1.y , arv->poligono->altura );
    glVertex3f(arv->poligono->p2.x, arv->poligono->p2.y , arv->poligono->altura);
    glVertex3f(arv->poligono->p2.x, arv->poligono->p2.y ,0.f);
    glEnd();
}

void Nodo::bfs(Nodo* arv){
    if(arv != NULL){
        bfs(arv->frente);
        cout<< " " << *(arv->poligono) << endl;
        bfs(arv->atras);
    }
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

void Nodo::divide(Poligono* outro, Poligono* &p_frente, Poligono* &p_atras){
    //Variaveis parametricas
    double s,t;
    int i = intersec2d(poligono->p1, poligono->p2, outro->p1, outro->p2, s, t);
    Vetor normal = poligono->pontoNormal() - poligono->pontoMedio();
    cout << "Chamada DIVIDE" << endl;
    cout << "Poligono:::" << *poligono << endl;
    cout << "Outro:::" << *outro << endl;

    cout << "ponto normal " << poligono->pontoNormal() << endl;
    cout << "ponto medio" << poligono->pontoMedio() << endl;
    Vetor ov1 = outro->p1 - poligono->pontoMedio();
    cout << "v1 " << ov1 << endl;
    Vetor ov2 = outro->p2 - poligono->pontoMedio();
    cout << "v2 " << ov2 << endl;
    double escalar1 = (normal * ov1);
    double escalar2 = (normal * ov2);
    cout << *poligono << endl;

    cout << "Escalares " << escalar1 << " " << escalar2 << endl;

    //Caso encontre interseccao
    if(i != 0){

        if(abs(escalar1) <= 0.01)
            escalar1 = 0;
        if(abs(escalar2) <= 0.01)
            escalar2 = 0;
        cout << "Ajuste aproximado " << escalar1 << " " << escalar2 << endl;
        Ponto pi;
        pi.x = poligono->p1.x + (poligono->p2.x-poligono->p1.x)*s;
        pi.y = poligono->p1.y + (poligono->p2.y-poligono->p1.y)*s;

        // primeiro ponto frente, segundo ponto atras
        if(escalar1 > 0 && escalar2 < 0){
            *p_frente = Poligono(outro->p1, pi);
            *p_atras = Poligono(pi, outro->p2);
            return;
        } else
            // primeiro ponto atras, segundo ponto frente
            if(escalar1 < 0 && escalar2 > 0){
                *p_atras = Poligono(outro->p1, pi);
                *p_frente = Poligono(outro->p2, pi);
                return;
            } else
                // primeiro ponto colinear, segundo ponto atras
                if(escalar1 == 0 && escalar2 < 0){

                    *p_atras = Poligono(outro->p1, outro->p2);
                    return;
                } else
                    // primeiro ponto colinear, segundo ponto frente
                    if(escalar1 == 0 && escalar2 > 0){
                        //            delete p_atras;
                        *p_frente = Poligono(outro->p1, outro->p2);
                        return;
                    } else
                        // primeiro ponto atras, segundo ponto colinear
                        if(escalar1 < 0 && escalar2 == 0){
                            cout << "este caso" << endl;
                            cout << Poligono(outro->p1, outro->p2) << "<<" << endl;
                            p_atras = new Poligono(outro->p1, outro->p2);
                            //            *p_atras = Poligono(outro->p1, outro->p2);

                            cout << *p_atras << "<<" << endl;
                            cout << "eae" << endl;
                            return;
                        } else
                            // primeiro ponto frente, segundo ponto colinear
                            if(escalar1 > 0 && escalar2 == 0){
                                //            delete p_atras;
                                *p_frente = Poligono(outro->p1, outro->p2);
                                return;
                            }
        //ambos sao colineares e ha intersecao
        if(escalar1 == 0 && escalar2 == 0){
            *p_frente = Poligono(outro->p1, outro->p2);
            //            delete p_atras;
            return;
        }
        cout << "Interseccao " << endl;
        //Caso nao encontre interseccao
    }else{
        //Poligono na frente (Qualquer teste escalar serve)
        if(escalar1 >= 0){
            *p_frente = Poligono(outro->p1, outro->p2);
            //            delete p_atras;
            return;
        }
        //Poligono atras
        else{
            *p_atras = Poligono(outro->p1, outro->p2);
            //            delete p_frente;
            return;
        }
    }

    cout << "FIM Chamada DIVIDE" << endl;
}


int Nodo::testePonto(Ponto outro){
    Vetor normal = poligono->pontoNormal() - poligono->pontoMedio();
    Vetor ov1 = outro - poligono->pontoMedio();
    double prodEscalar = (normal * ov1);
    //THRESHOLD de tolerancia
    if(abs(prodEscalar) <=0.01){
        return COLINEAR;
    }else if(prodEscalar > 0){
        return FRENTE;
    }else{
        return ATRAS;
    }
}

