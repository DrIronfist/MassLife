#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include "Particle.h"

using namespace std;

const float windowX = 640.0f;
const float windowY = 480.0f;
const float fps = 60.0f;
const int callbackPing = static_cast<int>(1000.0f / fps);
const float deltaTime = static_cast<float>(callbackPing) / 1000.0f;
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

void drawParticle(const Particle& p) {
    float colorInterp = (p.charge + 10) / 20.0f; // Normalize charge to 0-1 range
    glColor3f(1.0f - colorInterp, 0.0f, colorInterp); // Interpolate between red and blue

    glBegin(GL_POLYGON);
    float radius = p.radius;
    int segments = static_cast<int>(radius * 2 * M_PI);
    for (int j = 0; j < segments; j++) {
        float theta = 2.0f * M_PI * static_cast<float>(j) / static_cast<float>(segments);
        float x = p.pos.x + radius * cos(theta);
        float y = p.pos.y + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const Particle& p : particles) {
        drawParticle(p);
    }
    glutSwapBuffers();
}

void update(int value) {
    for (Particle& p : particles) {
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

void initializeParticles(int numParticles) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int i = 0; i < numParticles; ++i) {
        particles.emplace_back(
                (dis(gen) - 0.5f) * windowX,
                (dis(gen) - 0.5f) * windowY,
                5,
                (dis(gen) - 0.5f) * 20
        );
    }
}

int main(int argc, char** argv) {
    initializeParticles(10);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(static_cast<int>(windowX), static_cast<int>(windowY));
    glutInitWindowPosition(80, 80);
    glutCreateWindow("Particle Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(callbackPing, update, 0);
    glutMainLoop();
    return 0;
}
