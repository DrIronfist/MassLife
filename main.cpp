
#include <GLFW/glfw3.h>

#include <iostream>
#include <GLUT/glut.h>
const int windowWidth = 800;
const int windowHeight = 600;
const float radius = 100.0f;
const float centerX = windowWidth/2;
const float centerY = windowHeight/2;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_POINTS);
    for(float angle = 0; angle < 2* M_PI; angle += 0.001){
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glPointSize(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0, windowHeight);

}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Pixel Time");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
