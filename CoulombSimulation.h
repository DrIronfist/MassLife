#ifndef COULOMB_SIMULATION_H
#define COULOMB_SIMULATION_H

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include "Particle.h"

class CoulombSimulation {
public:
    CoulombSimulation(int argc, char** argv);
    void start();

private:
    static void init();
    static void drawParticle(const Particle& p);
    static void display();
    static void update(int value);
    static void initializeParticles(int numParticles);

    static const float windowX = 640.0f;
    static const float windowY = 480.0f;
    static const float fps = 60.0f;
    static const int callbackPing = static_cast<int>(1000.0f / fps);
    static const float deltaTime = static_cast<float>(callbackPing) / 1000.0f;
    static std::vector<Particle> particles;
};

#endif // COULOMB_SIMULATION_H
