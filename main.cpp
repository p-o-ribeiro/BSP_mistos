//#include <QCoreApplication>
#include "interseccao_retas.h"
#include "ponto.h"
#include <cmath>
#include <GL/glut.h>
//#include <GL/glew.h>
#include <stdio.h>
#include <labirinto.h>
#include <algorithm>


float ang=0;
bool cima,baixo,esquerda,direita;
Labirinto mapa("labirinto.txt");
Ponto* posicao = new Ponto(mapa.getLargura()/2.f,mapa.getAltura()/2.f);

void light(void)
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  GLfloat lmKa[] = {0.0, 1.0, 0.0, 0.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);



  GLfloat light_pos[] = {-1.0f, -2.0f, -3.0f, 1.0f};
  GLfloat light_Ka[]  = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat light_Kd[]  = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);


}


void display(void){
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-posicao->x,-posicao->y,0.5f);
    glTranslatef(posicao->x,posicao->y,0.5f);
    light();
    glRotatef(90,1.f,0.f,0.f);
    glRotatef(ang,0.f,0.f,1.f);
    glTranslatef(-posicao->x,-posicao->y,0.5f);
    mapa.desenhaLabirintoBSP();
    glPopMatrix();
    glutSwapBuffers();
}



void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 0.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(-mapa.getLargura()/2.f,-mapa.getAltura()/2.f,-0.5f);

}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 's':
        baixo=true;
        break;
    case 'w':
        cima=true;
        break;
    case 'a':
        esquerda=true;
        break;
    case 'd':
        direita=true;
        break;
    case 27:                                         // tecla Esc (encerra o programa)
        exit(0);
        break;
    }
}


void atualizaPersonagem(int v)
{
    if(cima){
        posicao->y-=0.03*cos(ang*PI/180);
        posicao->x-=0.03*sin(ang*PI/180);

    }
    else if(baixo){
        posicao->y+=0.03*cos(ang*PI/180);
        posicao->x+=0.03*sin(ang*PI/180);
    }
    else if(esquerda){
        ang+=3;
    }
    else if(direita){
        ang-=3;
    }
    mapa.setAngulo(ang);
    cima=baixo=direita=esquerda=false;
    glutPostRedisplay();
    glutTimerFunc(100/6, atualizaPersonagem, 0);
}

int test();



int main(int argc, char *argv[])
{
    mapa.setPosicao(posicao);
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (700, 700);
    glutInitWindowPosition (500, 500);
    glutCreateWindow ("Main window");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100/6, atualizaPersonagem,0);
    glutMainLoop();
    return 0;
    //return a.exec();
}


//int test(){

//    Ponto p1 (5,0);
//    Ponto p2 (5,2);

//    vector<Poligono* > pols;
//    for(int i=4; i>= 1; i--){
//        Ponto p3 (0,i*5);
//        Ponto p4 (10,i*5);
//        Poligono* pol = new Poligono();
//        pol->p1 = p3;
//        pol->p2 = p4;
//        pols.push_back(pol);

//    }
////    random_shuffle(pols.begin(), pols.end());
//    for(int i=0; i < pols.size(); i++)
//        cout << *pols[i] << endl;

//    Nodo* av2 =  new Nodo(pols);
//    Vetor normal = p2-p1;
//    Vetor normal2 = av2->poligono->pontoNormal()- av2->poligono->pontoMedio();
//    bool positivo = (normal * normal2) >= 0;
//    Nodo::bfs(av2);
//    av2->pintor(av2, positivo);
//    return 0;
//}
