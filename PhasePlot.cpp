//
// Created by Reet Sinha on 5/31/24.
//

#include "PhasePlot.h"
#include<cmath>


const float PhasePlot::windowX = 1000.0f;
const float PhasePlot::windowY = 1000.0f;
const float PhasePlot::fps = 60;
const int PhasePlot::callbackPing = int(1000.0f/fps);
const float PhasePlot::deltaTime = float(callbackPing)/1000.0f;
const float PhasePlot::cos30 = sqrt(3)/2.0f;
const float scale = 100.0f;
const float arrowScale = 10.0f;
const float e = exp(1.0);


void PhasePlot::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = int(-windowX / 2.0f); i < int(windowX / 2.0f); i += 20) {
        for (int j = int(-windowY / 2.0f); j < int(windowY / 2.0f); j += 20) {
            Vector2 pos = Vector2(float(i)/scale,float(j)/scale);
            Vector2 phase = phaseAtPoint(pos);
            float mag = phase.magnitude();
            float adjustedMagnitude =20.0f*(mag/(mag+1));
            drawArrow(pos, phase.normalize(),adjustedMagnitude);
        }
    }
    glutSwapBuffers();
}


PhasePlot::PhasePlot(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(static_cast<int>(windowX), static_cast<int>(windowY));
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Phase Plot");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(callbackPing, update, 0);
}

void PhasePlot::start() {
    glutMainLoop();
}
void PhasePlot::init(){
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

void PhasePlot::drawArrow(const Vector2& pos, const Vector2& normalized, float length) {
    const float arrowHeadSize = length * 0.5f;
    const Vector2 scaledUp = Vector2(pos.x * scale, pos.y * scale);

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
    float normalizedLength = length/20.0f;

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

Vector2 PhasePlot::phaseAtPoint(Vector2 pos) {
    float xChangeRate = pos.y - 0.5f*pos.x;
    float yChangeRate = sin(pos.x);
    return Vector2(xChangeRate, yChangeRate);

}

void PhasePlot::update(int value) {
    glutPostRedisplay();
    glutTimerFunc(callbackPing, update, 0);
}

