//
// Created by Reet Sinha on 5/31/24.
//

#ifndef PARTICLEPROJECT_PHASEPLOT_H
#define PARTICLEPROJECT_PHASEPLOT_H

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include "Vector2.h"
using std::vector;

class PhasePlot {
public:
    PhasePlot(int argc, char** argv);
    static void start();
    static void display();
    static void update(int value);
private:
    static void init();
    static void drawArrow(const Vector2& pos, const Vector2& normalized, float length);
    static Vector2 phaseAtPoint(Vector2 pos);

    static const float windowX;
    static const float windowY;
    static const float fps;
    static const int callbackPing;
    static const float deltaTime;
    static const float cos30;



};


#endif //PARTICLEPROJECT_PHASEPLOT_H
