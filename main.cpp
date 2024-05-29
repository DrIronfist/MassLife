
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
using namespace std;

float windowX = 640.0f;
float windowY = 480.0f;
float circleX = 0;
float circleY = 0;
float vx = 100;
float vy = 0;
float fps = 60.0f;
int callbackPing = int(1000.0f/fps);

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-windowX/2.0f, windowX/2.0f, -windowY/2.0f, windowY/2.0f, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Clears the current window and draws a triangle.
void display() {

    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    float radius = 20.0f;
    int segments=int(radius*2*M_PI);
    for(int i = 0; i < segments; i++){
        float theta = 2.0*M_PI*float(i)/float(segments);
        float x = circleX + radius*cos(theta);
        float y = circleY + radius*sin(theta);
        glVertex2f(x,y);
    }

    glEnd();

    glutSwapBuffers();
}

void update(int value){
    float deltaTime = float(callbackPing)/1000.0f;
//    cout << deltaTime << endl;
    circleX += vx*deltaTime;
    circleY += vy*deltaTime;
    glutPostRedisplay();

    glutTimerFunc(callbackPing,update,0);

}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
    // Use a single buffered window in RGB mode (as opposed to a double-buffered
    // window or color-index mode).
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Position window at (80,80)-(480,380) and give it a title.
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(windowX, windowY);
    glutCreateWindow("Circle Test");

    // Tell GLUT that whenever the main window needs to be repainted that it
    // should call the function display().
    init();
    glutDisplayFunc(display);

    glutTimerFunc(callbackPing,update,0);

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
    glutMainLoop();
    return 0;
}
