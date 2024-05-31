#define GL_SILENCE_DEPRECATION
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

using namespace std;

const float windowX = 1000.0f;
const float windowY = 1000.0f;
const float fps = 60.0f;
const int callbackPing = static_cast<int>(1000.0f / fps);
const float deltaTime = static_cast<float>(callbackPing) / 1000.0f;
const float cos30 = std::sqrt(3) / 2.0f;
float x = 0.0f;
float y = 0.0f;

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

void drawArrow(const Vector2& pos, const Vector2& normalized, float length) {
    const float arrowHeadSize = length * 0.5f;
    const Vector2 scaledUp = Vector2(pos.x*100.0f,pos.y*100.0f);

    const float endX = scaledUp.x + length * normalized.x;
    const float endY = scaledUp.y + length * normalized.y;

    const Vector2 leftIBasis(-cos30, 0.5f);
    const Vector2 leftJBasis(-0.5f, -cos30);
    const Vector2 rightIBasis(-cos30, -0.5f);
    const Vector2 rightJBasis(0.5f, -cos30);

    const Vector2 arrowVec(arrowHeadSize * normalized.x, arrowHeadSize * normalized.y);
    const Vector2 leftHeadPoint(
            endX + arrowVec.x * leftIBasis.x + arrowVec.y * leftJBasis.x,
            endY + arrowVec.x * leftIBasis.y + arrowVec.y * leftJBasis.y
    );
    const Vector2 rightHeadPoint(
            endX + arrowVec.x * rightIBasis.x + arrowVec.y * rightJBasis.x,
            endY + arrowVec.x * rightIBasis.y + arrowVec.y * rightJBasis.y
    );

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex2f(scaledUp.x, scaledUp.y);
    glVertex2f(endX, endY);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(endX, endY);
    glVertex2f(leftHeadPoint.x, leftHeadPoint.y);
    glVertex2f(rightHeadPoint.x, rightHeadPoint.y);
    glEnd();
}

Vector2 slopeAtDifferentialPoint(Vector2 pos){
    float slope = pos.y-2.0f*pos.x;
    return Vector2(1.0f,slope).normalize();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = int(-windowX/2.0f); i < int(windowX/2.0f); i+=20){
        for(int j = int(-windowY/2.0f); j < int(windowY/2.0f); j+=20){
            Vector2 posVector = Vector2(float(i/100.0f),float(j/100.0f));
            drawArrow(posVector,slopeAtDifferentialPoint(posVector),7);
        }
    }
    glBegin(GL_POLYGON);
    float radius = 10.0f;
    int segments = int(2.0f*radius*M_PI);
    for(int i = 0; i < segments; i++){
        glVertex2f(
                x*100.0f+radius*cos(2*M_PI*float(i)/float(segments)),
                y*100.0f+radius*sin(2*M_PI*float(i)/float(segments))
                );
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    Vector2 vel = slopeAtDifferentialPoint(Vector2(x,y));

    cout << vel.x << endl;

    x += vel.x * deltaTime;
    y += vel.y * deltaTime;
    glutPostRedisplay();
    glutTimerFunc(callbackPing, update, 0);
}




int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(static_cast<int>(windowX), static_cast<int>(windowY));
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Particle Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(callbackPing, update, 0);
    glutMainLoop();
    return 0;
}
