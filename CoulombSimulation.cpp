#include "CoulombSimulation.h"
#include <cmath>
#include <iostream>
#include <random>

std::vector<Particle> CoulombSimulation::particles;

CoulombSimulation::CoulombSimulation(int argc, char** argv) {
    initializeParticles(10);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(static_cast<int>(windowX), static_cast<int>(windowY));
    glutInitWindowPosition(80, 80);
    glutCreateWindow("Coulomb Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(callbackPing, update, 0);
}

void CoulombSimulation::start() {
    glutMainLoop();
}

void CoulombSimulation::init() {
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

void CoulombSimulation::drawParticle(const Particle& p) {
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

void CoulombSimulation::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const Particle& p : particles) {
        drawParticle(p);
    }
    glutSwapBuffers();
}

void CoulombSimulation::update(int value) {
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

void CoulombSimulation::initializeParticles(int numParticles) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int i = 0; i < numParticles; ++i) {
        particles.emplace_back(
                (dis(gen) - 0.5f) * windowX,
                (dis(gen) - 0.5f) * windowY,
                5,
                (dis(gen) - 0.5f) * 20
        );
    }
}
