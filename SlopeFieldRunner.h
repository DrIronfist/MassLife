//
// Created by Reet Sinha on 5/30/24.
//

#ifndef PARTICLEPROJECT_SLOPEFIELDRUNNER_H
#define PARTICLEPROJECT_SLOPEFIELDRUNNER_H

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include "Particle.h"

class SlopeFieldRunner{
public:
    SlopeFieldRunner(int argc, char** argv);
    void start();
    static void display();
    static void update(int value);

private:
    static void init();
    static void drawArrow(const Vector2& pos, const Vector2& normalized, float length);
    static Vector2 slopeAtDifferentialPoint(Vector2 pos);

    static const float windowX;
    static const float windowY;
    static const float fps;
    static const int callbackPing;
    static const float deltaTime;
    static const float cos30;
    static float x;
    static float y;
};






#endif //PARTICLEPROJECT_SLOPEFIELDRUNNER_H
