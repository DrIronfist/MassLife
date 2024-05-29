
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

float windowX = 640.0f;
float windowY = 480.0f;


void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowX, 0, windowY, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Clears the current window and draws a triangle.
void display() {

    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    float startX = windowX/2.0f+100;
    float startY = windowY/2.0f+100;
    float radius = 20.0f;
    int segments=int(radius*2*M_PI);
    for(int i = 0; i < segments; i++){
        float theta = 2.0*M_PI*float(i)/float(segments);
        float x = startX + radius*cos(theta);
        float y = startY + radius*sin(theta);
        glVertex2f(x,y);
    }

    glEnd();

    glutSwapBuffers();
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

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
    glutMainLoop();
    return 0;
}
