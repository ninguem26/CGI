
/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees
and is provided without guarantee or warrantee expressed or
implied. This program is -not- in the public domain. */

/* blender renders two spinning icosahedrons (red and green).
The blending factors for the two icosahedrons vary sinusoidally
and slightly out of phase.  blender also renders two lines of
text in a stroke font: one line antialiased, the other not.  */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float t = 0.1;
float time = 0.0;
float rotate_speed = 1;
float angulo = 30.0f;
float dir = 1.0f;
float rotate = 0.1f;
int cX = 120;
int cY = 120;
int size = 40;

double to_rad(double degree) {
    return degree * (M_PI/180.0);
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

// Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

// Desenha um quadrado preenchido com a cor corrente
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2i(0, -90);
        glVertex2i(0, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(cX - size*cos(to_rad(300 + rotate)), cY - size*sin(to_rad(300 + rotate)));
        glVertex2i(cX - size*cos(to_rad(240 + rotate)), cY - size*sin(to_rad(240 + rotate)));
        glVertex2i(cX, cY);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2i(cX - size*cos(to_rad(30 + rotate)), cY - size*sin(to_rad(30 + rotate)));
        glVertex2i(cX - size*cos(to_rad(-30 + rotate)), cY - size*sin(to_rad(-30 + rotate)));
        glVertex2i(cX, cY);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(cX + size*cos(to_rad(30 + rotate)), cY + size*sin(to_rad(30 + rotate)));
        glVertex2i(cX + size*cos(to_rad(-30 + rotate)), cY + size*sin(to_rad(-30 + rotate)));
        glVertex2i(cX, cY);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2i(cX - size*cos(to_rad(120 + rotate)), cY - size*sin(to_rad(120 + rotate)));
        glVertex2i(cX - size*cos(to_rad(60 + rotate)), cY - size*sin(to_rad(60 + rotate)));
        glVertex2i(cX, cY);
    glEnd();
    printf("%f\n", cos(to_rad(angulo)));

// Executa os comandos OpenGL
    glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
// Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
           // Evita a divisao por zero
    if(h == 0) h = 1;

           // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

           // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    if (w <= h)
        gluOrtho2D (0.0f, 250.0f, 0.0f, 250.0f*h/w);
    else
        gluOrtho2D (0.0f, 250.0f*w/h, 0.0f, 250.0f);
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
void Timer(int value)
{
    // Rotaciona o cata-vento
    rotate += rotate_speed;
    time += t;

    if(time >= 10){
        time = 0;
        rotate_speed *= -1;
        if(size == 40) {
            size *= 2;
        } else {
            size = 40;
        }
    }

    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cata-Vento");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutTimerFunc(33, Timer, 1);
    Inicializa();
    glutMainLoop();
return 0;             /* ANSI C requires main to return int. */
}
