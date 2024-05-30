#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include "Particle.h"
#include <vector>
#include <random>
using namespace std;

float windowX = 640.0f;
float windowY = 480.0f;
float fps = 60.0f;
int callbackPing = int(1000.0f / fps);
float deltaTime = float(callbackPing) / 1000.0f;
float timeElapsed = 0;
vector<Particle> particles;

void init() {
    glClearColor(32.0f / 255.0f, 36.0f / 255.0f, 47.0f / 255.0f, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glOrtho(-windowX / 2.0f, windowX / 2.0f, -windowY / 2.0f, windowY / 2.0f, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (Particle &p : particles) {
        float colorInterp = (p.charge + 10) / 20.0f; // normalize charge to 0-1 range
        glColor3f(1.0f - colorInterp, 0.0f, colorInterp); // interpolate between red and blue

        glBegin(GL_POLYGON);
        float radius = p.radius;
        int segments = int(radius * 2 * M_PI);
        for (int j = 0; j < segments; j++) {
            float theta = 2.0 * M_PI * float(j) / float(segments);
            float x = p.pos.x + radius * cos(theta);
            float y = p.pos.y + radius * sin(theta);
            glVertex2f(x, y);
        }
        glEnd();
    }

    glutSwapBuffers();
}

void update(int value) {
    timeElapsed += deltaTime;
    for (Particle &p : particles) {
        p.updateAcceleration(particles);
        p.vel.x += p.acc.x * deltaTime;
        p.vel.y += p.acc.y * deltaTime;
        p.pos.x += p.vel.x * deltaTime;
        p.pos.y += p.vel.y * deltaTime;

        if (p.pos.x - p.radius <= -windowX / 2.0f || p.pos.x + p.radius >= windowX / 2.0f) {
            p.vel.x *= -1;
        }
        if (p.pos.y - p.radius <= -windowY / 2.0f || p.pos.y + p.radius >= windowY / 2.0f) {
            p.vel.y *= -1;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(callbackPing, update, 0);
}

int main(int argc, char** argv) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int i = 0; i < 100; i++) {
        particles.push_back(Particle((dis(gen) - 0.5f) * windowX, (dis(gen) - 0.5f) * windowY, 5, (dis(gen) - 0.5f) * 20));
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(windowX, windowY);
    glutCreateWindow("Particle Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(callbackPing, update, 0);
    glutMainLoop();
    return 0;
}
