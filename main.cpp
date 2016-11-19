//#include <QCoreApplication>
#include "interseccao_retas.h"
#include "ponto.h"
#include <cmath>
#include <GL/glut.h>
#include <labirinto.h>

labirinto mapa("labirinto.txt");
void display(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    /* Cubo 1 */
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);


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
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (-04.0, -04.0, -10.0);
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 27:                                         // tecla Esc (encerra o programa)
        exit(0);
        break;
    }
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
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (500, 500);
    glutCreateWindow ("Main window");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
    //return a.exec();
}
