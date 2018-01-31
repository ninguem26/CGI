
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

float xPos = 120;
float yPos = 270;
float xSpeed = 5;
float ySpeed = 5;
float xSize = 100;
float ySize = 50;

void timerUp(int value);
void timerDown(int value);

// Função callback chamada para fazer o desenho
void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

// Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

// Desenha um quadrado preenchido com a cor corrente
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2i(xPos, yPos + ySize);
        glVertex2i(xPos, yPos);
        glVertex2i(xPos + xSize, yPos);
        glVertex2i(xPos + xSize, yPos + ySize);
    glEnd();

// Executa os comandos OpenGL
    glFlush();
}

// Inicializa parâmetros de rendering
void init (void)
{
// Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void changeWindowSize(GLsizei w, GLsizei h)
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
        gluOrtho2D (0.0f, 400.0f, 0.0f, 400.0f*h/w);
    else
        gluOrtho2D (0.0f, 400.0f*w/h, 0.0f, 400.0f);
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
void timer(int value)
{
    xPos += xSpeed;
    yPos += ySpeed;

    if(xPos + xSize > glutGet(GLUT_WINDOW_WIDTH) || xPos < 0){
        xSpeed *= -1;
    }

    if(yPos + ySize > glutGet(GLUT_WINDOW_HEIGHT) || yPos < 0){
        ySpeed *= -1;
    }
    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33,timer, 1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Blocos");
    glutDisplayFunc(draw);
    glutReshapeFunc(changeWindowSize);
    glutTimerFunc(33, timer, 1);
    init();
    glutMainLoop();
return 0;             /* ANSI C requires main to return int. */
}
