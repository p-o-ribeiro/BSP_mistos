//#include <QCoreApplication>
#include "interseccao_retas.h"
#include "ponto.h"
#include <cmath>
#include <GL/glut.h>
#include <labirinto.h>

labirinto mapa("labirinto.txt");
float ang=0;
bool cima,baixo,esquerda,direita;
Ponto posicao(mapa.getLargura()/2.f,mapa.getAltura()/2.f);

void display(void){
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-posicao.x,-posicao.y,0.5f);
    glTranslatef(posicao.x,posicao.y,0.5f);
    glRotatef(90,1.f,0.f,0.f);
    glRotatef(ang,0.f,0.f,1.f);
    glTranslatef(-posicao.x,-posicao.y,0.5f);

    mapa.desenhaLabirinto();
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
        posicao.y-=0.3*cos(ang*PI/180);
        posicao.x-=0.3*sin(ang*PI/180);

    }
    else if(baixo){
        posicao.y+=0.3*cos(ang*PI/180);
        posicao.x+=0.3*sin(ang*PI/180);
    }
    else if(esquerda){
        ang+=3;
    }
    else if(direita){
        ang-=3;
    }
    cima=baixo=direita=esquerda=false;
    glutPostRedisplay();
    glutTimerFunc(100/6, atualizaPersonagem, 0);
}
int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    Ponto p1 (0,0);
    Ponto p2 (2,0);

    Ponto p3 (0,2);
    Ponto p4 (2,2);

    Ponto pi;
    double s, t;

    pi = intersec2d(p1, p2, p3, p4, s, t);
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
