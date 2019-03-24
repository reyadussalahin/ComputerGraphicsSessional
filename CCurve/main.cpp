#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#define PI (acos(-1))

using namespace std;

struct Point {
    double x, y;
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

void draw_line(Point s, Point e) {
    glBegin(GL_LINES);
    glVertex2i(s.x, s.y);
    glVertex2i(e.x, e.y);
    glEnd();
    glFlush();
}

void plot(Point p) {
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
    glEnd();
    glFlush();
}

Point translate(Point p, Point c) {
    return Point(p.x + c.x, p.y + c.y);
}

void print_point(Point p) {
    printf("%lf %lf\n", p.x, p.y);
}

double to_radian(double x) {
    return (PI * x) / 180.0;
}

void c_curve(double x, double y, double len, double alpha, int n) {
    if(n > 0) {
        len = len / sqrt(2.0);
        c_curve(x, y, len, alpha + 45, n-1);
        x = x + len * cos(to_radian(alpha+45));
        y = y + len * sin(to_radian(alpha+45));
        c_curve(x, y, len, alpha - 45, n-1);
    }
    else {
        Point a = Point(x, y);
        Point b = Point(x + len * cos(to_radian(alpha)), y + len * sin(to_radian(alpha)));
        draw_line(a, b);
    }
}

void display(void) {
    Point p = Point(-50, 0);
    double len = 100;
    double alpha = 0.0;
    int n = 3;
    c_curve(p.x, p.y, len, alpha, n);
    draw_line(Point(0, 80), Point(0, -80));
    draw_line(Point(80, 0), Point(-80, 0));
}

void init() {
    glClearColor(0.7, 0.7, 0.7, 0.7);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Circle...............");

    init();
//    glPointSize(2.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
