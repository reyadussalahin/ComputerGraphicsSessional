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

using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) {
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
    printf("%d %d\n", p.x, p.y);
}

vector<Point> helper(Point a, Point b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    int p = 2 * dy - dx;
    vector<Point> buf;

    int x = a.x, y = a.y;
    while(x <= b.x) {
        x++;
        if(p < 0) {
            buf.push_back(Point(x, y));
            p = p + 2 * dy;
        }
        else {
            y++;
            buf.push_back(Point(x, y));
            p = p + 2 * dy - 2 * dx;
        }
    }
    return buf;
}

void solve(Point p1, Point p2) {
    if(p1.x > p2.x) swap(p1, p2);
    Point a = Point(0, 0);
    Point b = Point(p2.x - p1.x, p2.y - p1.y);

    if(b.y < 0) {
        b.y *= -1;
        if(b.y <= b.x && b.y > 0) {
            vector<Point> v = helper(a, b);
            for(int i=0; i<(int)v.size(); i++) {
                Point q = Point(v[i].x, -1 * v[i].y);
                Point t = translate(q, p1);
                plot(t);
            }
        }
        if(b.y > b.x) {
            swap(b.x, b.y);
            vector<Point> v = helper(a, b);
            for(int i=0; i<(int)v.size(); i++) {
                Point q = Point(v[i].y, -1 * v[i].x);
                Point t = translate(q, p1);
                plot(t);
            }
        }
    }
    else {
        if(b.y <= b.x && b.y > 0) {
            vector<Point> v = helper(a, b);
            for(int i=0; i<(int)v.size(); i++) {
                Point q = v[i];
                Point t = translate(q, p1);
                plot(t);
            }
        }
        if(b.y > b.x) {
            swap(b.x, b.y);
            vector<Point> v = helper(a, b);
            for(int i=0; i<(int)v.size(); i++) {
                Point q = Point(v[i].y, v[i].x);
                Point t = translate(q, p1);
                plot(t);
            }
        }
    }
}

void display(void) {
    Point p1 = Point(-6, 6);
    Point p2 = Point(-75, -25);
    draw_line(Point(0, 100), Point(0, -100));
    draw_line(Point(100, 0), Point(-100, 0));
    solve(p1, p2);
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Circle...............");

    init();
//    glPointSize(2.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
