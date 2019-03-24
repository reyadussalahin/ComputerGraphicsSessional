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

#include<windows.h>
#include<bits/stdc++.h>
#include<GL/glut.h>

float FILLcolor[3] = {0.9,0.0,0.0};
float FILLcolor1[3] = {0.1,0.0,0.0};
float FILLcolor2[3] = {0.0,0.90,0.90};

float BORDERcolor[3] = {0.0,0.0,0.0};
float BORDERcolor1[3] = {1.0,0.0,0.0};
float BORDERcolor2[3] = {0.0,1.0,1.0};

void setPixel(int pointx, int pointy, float f[3]) { //
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);
}


void drawPolygon(int x1, int y1, int x2, int y2) {
    glColor3f(0.0, 0.0, 0.0);/// Border Color
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

bool checkColor1(float interiorColor[3]) {
    if(interiorColor[0]!= BORDERcolor[0] && (interiorColor[1])!= BORDERcolor[1] && (interiorColor[2])!= BORDERcolor[2])
        return 1;
    if(interiorColor[0]!= BORDERcolor1[0] && (interiorColor[1])!= BORDERcolor1[1] && (interiorColor[2])!= BORDERcolor1[2])
        return 1;
    if(interiorColor[0]!=BORDERcolor2[0] && (interiorColor[1])!=BORDERcolor2[1] && (interiorColor[2])!=BORDERcolor2[2])
        return 1;
    return 0;
}

int WindWidth = 700, WindHeight = 500;

void display() {
    glClearColor(0.1,0.8,0.9, .95);
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(250, 200, 350, 300);
    glFlush();
}

void FloodFill(int x,int y,float fillColor[3],float borderColor[3]) {
    float interiorColor[3];
    getPixel(x,y,interiorColor);
    if( checkColor1(interiorColor) && (interiorColor[0]!=fillColor[0] && (interiorColor[1])!=fillColor[1] && (interiorColor[2])!=fillColor[2])) {
        setPixel(x,y,fillColor);
        FloodFill(x+1,y,fillColor,borderColor);
        FloodFill(x-1,y,fillColor,borderColor);
        FloodFill(x,y+1,fillColor,borderColor);
        FloodFill(x,y-1,fillColor,borderColor);
    }
}

void mouse(int button, int click, int x, int y) {
    if(button==GLUT_LEFT_BUTTON && click == GLUT_DOWN) {
        int xi = x;
        int yi = (WindHeight-y);
        FloodFill(xi,yi,FILLcolor,BORDERcolor);
    }
}

void init() {
    glViewport(0,0,WindWidth,WindHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)WindWidth,0.0,(GLdouble)WindHeight);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WindWidth,WindHeight);
    glutCreateWindow("Exp-7 : Boundary Fill Algorithm");
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
