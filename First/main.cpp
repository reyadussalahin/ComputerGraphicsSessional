/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
//#include<bits/stdc++.h>

using namespace std;

void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void solve(int x1, int y1, int x2, int y2)
{
//    int x1, y1, x2, y2;
//    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    if(x2 < x1)
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    double m = 1.0 * (y1 - y2) / (x1 - x2);
    int flag = ((y1 - y2) == (x1 - x2));

//    printf("%f\n", m);
    double x = x1, y = y1;
    int tx, ty;
    while(x < x2)
    {
        if(flag)
        {
            x = x + 1;
            y = y + 1;
            tx = ceil(x);
            ty = ceil(y);
        }
        else
        {
            if(m < 1.0)
            {
                x = x + 1;
                y = y + m;
                tx = ceil(x);
                ty = ceil(y);
//              printf("%d %d\n", tx, ty);
            }
            else
            {
                x = x + m;
                y = y + 1;
                tx = round(x);
                ty = round(y);
//              printf("%d %d\n", tx, ty);
            }
        }
        plot(tx, ty);
    }
//    printf("%d %d\n", x, y);
}

void display(void)
{
    solve(0, 10, 50, 48);
}

void init()
{
    glClearColor(0.7, 0.7, 0.7, 0.7);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char *argv[])
{
//    solve();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("First...............");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}

//static int slices = 16;
//static int stacks = 16;
//
///* GLUT callback Handlers */
//
//static void resize(int width, int height)
//{
//    const float ar = (float) width / (float) height;
//
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity() ;
//}
//
//static void display(void)
//{
//    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
//    const double a = t*90.0;
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColor3d(1,0,0);
//
//    glPushMatrix();
//        glTranslated(-2.4,1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutSolidSphere(1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(0,1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutSolidCone(1,1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(2.4,1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutSolidTorus(0.2,0.8,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(-2.4,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireSphere(1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(0,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireCone(1,1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(2.4,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireTorus(0.2,0.8,slices,stacks);
//    glPopMatrix();
//
//    glutSwapBuffers();
//}
//
//
//static void key(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//        case 27 :
//        case 'q':
//            exit(0);
//            break;
//
//        case '+':
//            slices++;
//            stacks++;
//            break;
//
//        case '-':
//            if (slices>3 && stacks>3)
//            {
//                slices--;
//                stacks--;
//            }
//            break;
//    }
//
//    glutPostRedisplay();
//}
//
//static void idle(void)
//{
//    glutPostRedisplay();
//}
//
//const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
//const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
//
//const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
//const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
//const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat high_shininess[] = { 100.0f };
//
///* Program entry point */
//
//int main(int argc, char *argv[])
//{
//    glutInit(&argc, argv);
//    glutInitWindowSize(640,480);
//    glutInitWindowPosition(10,10);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//
//    glutCreateWindow("GLUT Shapes");
//
//    glutReshapeFunc(resize);
//    glutDisplayFunc(display);
//    glutKeyboardFunc(key);
//    glutIdleFunc(idle);
//
//    glClearColor(1,1,1,1);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//
//    glEnable(GL_LIGHT0);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
//
//    glutMainLoop();
//
//    return EXIT_SUCCESS;
//}
