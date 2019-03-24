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

void draw_triangle(Point a, Point b, Point c) {
    glBegin(GL_TRIANGLES);
    glVertex2i(a.x, a.y);
    glVertex2i(b.x, b.y);
    glVertex2i(c.x, c.y);
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

Point mid_point(Point p1, Point p2) {
    return Point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
}

void gasket(Point a, Point b, Point c, int n) {
    if(n > 0) {
        Point ab = mid_point(a, b);
        Point bc = mid_point(b, c);
        Point ca = mid_point(c, a);

        gasket(a, ab, ca, n-1);
        gasket(b, bc, ab, n-1);
        gasket(c, ca, bc, n-1);
    }
    else {
        draw_triangle(a, b, c);
    }
}

void display(void) {
    draw_line(Point(0, 80), Point(0, -80));
    draw_line(Point(80, 0), Point(-80, 0));
    Point a = Point(-25, 0);
    Point b = Point(0, -25);
    Point c = Point(25, 0);
    int n = 2;
//    draw_triangle(a, b, c);
    gasket(a, b, c, n);
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
