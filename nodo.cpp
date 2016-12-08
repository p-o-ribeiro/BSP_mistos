#include "nodo.h"
#include "vetor.h"
#include <GL/glut.h>

#define FRENTE 1
#define COLINEAR 2
#define ATRAS 3



//Construtor padrao
Nodo::Nodo(Poligono p){
    poligono = p.clonar();
}



/**
 * @brief Nodo::adiciona
 * @param p
 *
 * Funcao responsavel por adicionar um novo poligono a BSP
 * trata tambem o caso de divisao de poligonos
 */
void Nodo::adiciona(Poligono p){
    if(poligono == NULL){
        poligono = p.clonar();
    }else{

        Poligono* p_frente = NULL;  // Ponteiro para poligono frontal
        Poligono* p_atras = NULL;  // Ponteiro para poligono de tras
        double s,t;
        int status_i = intersec2d(poligono->p1, poligono->p2, p.p1, p.p2, s, t);
        int status_p1 = testePonto(p.p1);
        int status_p2 = testePonto(p.p2);


        //Casos em que o novo poligono eh localizado inteiramente na frente
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

        //Casos em que o novo poligono eh localizado inteiramente atras
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

        //Casos em que o poligono fica subdividido em dois
        if(status_i != 0){
            Ponto pi; //Ponto de intersecao
            pi.x = poligono->p1.x + (poligono->p2.x-poligono->p1.x)*s;
            pi.y = poligono->p1.y + (poligono->p2.y-poligono->p1.y)*s;
            if(status_p1 == FRENTE){ // P1 eh o ponto na frente do poligono

                p_frente = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p1.x, p.p1.y));
                p_frente->cor = p.cor;
                p_atras = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p2.x, p.p2.y));
                p_atras->cor = p.cor;

                //Testa se ja existe um poligono instanciado a frente do atual
                if(this->frente != NULL)
                    this->frente->adiciona(*p_frente);
                else{
                    this->frente = new Nodo(*p_frente);
                }
                //Testa se ja existe um poligono instanciado atras do atual
                if(this->atras != NULL){
                    this->atras->adiciona(*p_atras);
                }else{
                    this->atras = new Nodo(*p_atras);
                }
            }else{  // P2 eh o ponto na frente do poligono

                p_frente = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p2.x, p.p2.y));
                p_frente->cor = p.cor;
                p_atras = new Poligono(Ponto(pi.x, pi.y), Ponto(p.p1.x, p.p1.y));
                p_atras->cor = p.cor;

                //Testa se ja existe um poligono instanciado a frente do atual
                if(this->frente != NULL)
                    this->frente->adiciona(*p_frente);
                else{
                    this->frente = new Nodo(*p_frente);
                }

                //Testa se ja existe um poligono instanciado atras do atual
                if(this->atras != NULL){
                    this->atras->adiciona(*p_atras);
                }else{
                    this->atras = new Nodo(*p_atras);
                }

            }
        }
    }
}




/**
 * @brief Nodo::pintor
 * @param arv
 * @param pos_observador
 *
 * Algoritmo do pintor para a BSP, o ponto do observador eh passado
 * por parametro
 */
void Nodo::pintor(Nodo* arv, Ponto pos_observador){
    if(arv == NULL || arv->poligono == NULL){
        return;
    }
    //Nodo folha
    if(arv->frente == NULL && arv->atras == NULL){
        arv->poligono->pinta();
    }

    // Normal do poligono atual
    Vetor normal = arv->poligono->pontoNormal() - arv->poligono->pontoMedio();
    //Vetor de orientacao do observador em rel. ao poligono
    Vetor normal_observador = pos_observador - arv->poligono->pontoMedio();

    double escalar = (normal_observador * normal);
    //Caso em que o poligono eh colinear
    if(abs(escalar)<0.0001){ //THRESHOLD para tratar imprecisao numerica
        pintor(arv->frente, pos_observador);
        pintor(arv->atras, pos_observador);
        escalar = 0;
    }
    else if(escalar > 0){ //Caso de orientacao frontal
        pintor(arv->atras, pos_observador);
        arv->poligono->pinta();
        pintor(arv->frente, pos_observador);
    } else { // Caso de orientacao traseira
        pintor(arv->frente, pos_observador);
        arv->poligono->pinta();
        pintor(arv->atras, pos_observador);
    }
}


//Funcao BFS usada para fins de depuracao
void Nodo::bfs(Nodo* arv){
    if(arv != NULL){
        bfs(arv->frente);
        cout<< " " << *(arv->poligono) << endl;
        bfs(arv->atras);
    }
}


/**
 * @brief Nodo::testePonto
 * @param outro
 * @return
 * Teste de relacao entre ponto individual e o poligono
 */
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

