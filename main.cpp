
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <chrono>
#include "Particle.h"
#include <vector>
#include <random>
using namespace std;

float windowX = 640.0f;
float windowY = 480.0f;
float circleX = 0;
float circleY = 0;
float vx = 2;
float vy = 3;
float fps = 60.0f;
int callbackPing = int(1000.0f/fps);
float deltaTime = float(callbackPing)/1000.0f;
float timeElapsed = 0;
vector<Particle> particles;

void init(){
    glClearColor(32.0f/255.0f, 36.0f/255.0f, 47.0f/255.0f, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glOrtho(-windowX/2.0f, windowX/2.0f, -windowY/2.0f, windowY/2.0f, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Clears the current window and draws a triangle.
void display() {

    // Set every pixel in the frame buffer to the current clear color.
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    for(int i = 0; i < particles.size(); i++){
        glBegin(GL_POLYGON);
        Particle p = particles.at(i);
        float radius = p.radius;
        int segments = int(radius*2*M_PI);
        for(int j = 0; j < segments; j++){
            float theta = 2.0f * M_PI * float(j)/float(segments);
            float x = p.pos.x + radius * cos(theta);
            float y = p.pos.y + radius * sin(theta);
            glVertex2f(x,y);
        }
        glEnd();
    }



    glutSwapBuffers();
}

void update(int value){
    timeElapsed += deltaTime;
    for(int i = 0; i < particles.size(); i++){
        Particle& p = particles[i];
        particles[i].updateAcceleration(particles);
        particles[i].vel.x += particles[i].acc.x * deltaTime;
        particles[i].vel.y += particles[i].acc.y * deltaTime;
        particles[i].pos.x += particles[i].vel.x * deltaTime;
        particles[i].pos.y += particles[i].vel.y * deltaTime;
        if (p.pos.x + p.radius > windowX / 2.0f || p.pos.x - p.radius < -windowX / 2.0f){
            // Check for collision with window borders and reverse velocity if necessary
            if (p.pos.x + p.radius > windowX / 2.0f || p.pos.x - p.radius < -windowX / 2.0f) {
                p.vel.x *= -1;
            }
            if (p.pos.y + p.radius > windowY / 2.0f || p.pos.y - p.radius < -windowY / 2.0f) {
                p.vel.y *= -1;
            }
        }

    }
    glutPostRedisplay();
    glutTimerFunc(callbackPing,update,0);

}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
    // Use a single buffered window in RGB mode (as opposed to a double-buffered
    // window or color-index mode).
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);

    for(int i = 0; i <1; i++){
        particles.push_back(Particle((dis(gen)-0.5f)*windowX/2.0f,(dis(gen)-0.5f)*windowY/2.0f,5,(dis(gen)-0.5f)*10));
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

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
