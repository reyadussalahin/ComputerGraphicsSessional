#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

// grouped list of point variables
struct Point {
    GLint x;
    GLint y;
};

// grouped list of point variables
struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

void init() {
    glClearColor(0.0, 1.0, 0.0, 0.0); // specify clear values for the color buffers
    glColor3f(0.0, 0.0, 0.0);         //Sets the current color.
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);    // specify which matrix is the current matrix.
    //GL_PROJECTION Applies subsequent matrix operations to the projection matrix stack.
    glLoadIdentity();               // replace the current matrix with the identity matrix
    gluOrtho2D(0, 640, 0, 480);     //define a 2D orthographic projection matrix
}

Color getPixelColor(GLint x, GLint y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);  //read a block of pixels from the frame buffer
    return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
    glColor3f(color.r, color.g, color.b); //Sets the current color.
    glBegin(GL_POINTS);                 //delimit the vertices of a primitive or a group of like primitives
    glVertex2i(x, y);                   //Specifies a vertex.
    glEnd();
    glFlush();                          //force execution of GL commands in finite time
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
    Color color;
    color = getPixelColor(x, y);

    if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b) {
        setPixelColor(x, y, newColor);
        floodFill(x+1, y, oldColor, newColor);
        floodFill(x, y+1, oldColor, newColor);
        floodFill(x-1, y, oldColor, newColor);
        floodFill(x, y-1, oldColor, newColor);
    }
    return;
}

void onMouseClick(int button, int state, int x, int y) {
    Color newColor = {1.0f, 0.0f, 0.0f};
    Color oldColor = {0.0f, 1.0f, 0.0f};

    floodFill(320, 240, oldColor, newColor);
}

void draw_circle(Point pC, GLfloat radius) {
    GLfloat step = 1/radius;
    GLfloat x, y;

    for(GLfloat theta = 0; theta <= 360; theta += step) {
        x = pC.x + (radius * cos(theta));      //calculate the x component
        y = pC.y + (radius * sin(theta));      //calculate the x component
        glVertex2i(x, y);                   //Specifies a vertex.
    }
}

void display(void) {
    Point pt = {320, 240};
    GLfloat radius = 40;

    glClear(GL_COLOR_BUFFER_BIT); // clear buffers to preset values
    //GL_COLOR_BUFFER_BIT  Indicates the buffers currently enabled for color writing. GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
    glBegin(GL_POINTS);
    draw_circle(pt, radius);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                      //initialize the GLUT library.
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);  // sets the initial display mode. GLUT_SINGLE -Bit mask to select a single buffered window.
    //GLUT_RGBA-Bit mask to select an RGBA mode window
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);           //set the initial window position and size respectively
    glutCreateWindow("Flood Fill Algorithm");
    init();
    glutDisplayFunc(display);                   //sets the display callback for the current window
    glutMouseFunc(onMouseClick);
    glutMainLoop();                             //enters the GLUT event processing loop.
    return 0;
}
