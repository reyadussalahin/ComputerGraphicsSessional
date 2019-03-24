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
//#include<bits/stdc++.h>

using namespace std;



struct Point {
    int x, y;
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};



//void swap_int(int *a, int *b) {
//    int t = *a;
//    *a = *b;
//    *b = t;
//}

//void plot(int x, int y) {
//    glBegin(GL_POINTS);
//    glVertex2i(x, y);
//    glEnd();
//    glFlush();
//}


double range_min, range_max;

void draw_line(Point s, Point e) {
    glBegin(GL_LINES);
    glVertex2i(s.x, s.y);
    glVertex2i(e.x, e.y);
    glEnd();
    glFlush();
}

void plot(Point p) {
    glBegin(GL_POINTS);
    if(range_min <= p.x && p.x <= range_max) glVertex2i(p.x, p.y);
    glEnd();
    glFlush();
}

Point first(Point p) {
    return Point(p.x, p.y);
}

Point second(Point p) {
    return Point(-1 * p.x, p.y);
}

Point third(Point p) {
    return Point(-1 * p.x, -1 * p.y);
}

Point fourth(Point p) {
    return Point(p.x, -1 * p.y);
}

Point translate(Point p, Point c) {
    return Point(p.x + c.x, p.y + c.y);
}

void solve() {
    int r = 50;
    Point c = Point(0, 0);
    double range = r / 2.0;
    range_min = -range;
    range_max = range;

    int p = 1 - r;
    int x = 0, y = r;

    while(x <= y) {
        x++;
        if (p < 0) {
            p += 2 * (x + 1) + 1;
        } else {
            y--;
            p += 2 * (x + 1) + 1 - 2 * (y - 1);
        }
        Point p = Point(x, y);
        plot(translate(first(p), c));
        plot(translate(second(p), c));
        plot(translate(third(p), c));
        plot(translate(fourth(p), c));

        Point _p = Point(y, x);
        plot(translate(first(_p), c));
        plot(translate(second(_p), c));
        plot(translate(third(_p), c));
        plot(translate(fourth(_p), c));
    }

//    int yy = r+25;
//    draw_line(Point(0, yy), Point(0, -yy));
//    draw_line(Point(yy, 0), Point(-yy, 0));
}

void display(void) {
    solve();
}

void init() {
    glClearColor(0.7, 0.7, 0.7, 0.7);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char *argv[]) {
//    solve();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Circle...............");

    init();
//    glPointSize(2.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
