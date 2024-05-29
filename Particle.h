#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <cmath>

struct Vector2 {
    float x;
    float y;

    // Constructor
    Vector2(float d, float d0) : x(d), y(d0) {}
};

const float k = 3.0f;

class Particle {
public:
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    float radius;
    float charge;

    // Constructor
    Particle(float x, float y, float radius_val, float charge_val)
            : pos(x, y), vel(0, 0), acc(0, 0), radius(radius_val), charge(charge_val) {}

    // Function to update acceleration
    Vector2 updateAcceleration(std::vector<Particle> particles) {
        float accX = 0.0f;
        float accY = 0.0f;
        for (int i = 0; i < particles.size(); i++) {
            Particle p = particles.at(i);
            float deltaX = pos.x - p.pos.x;
            float deltaY = pos.y - p.pos.y;
            float dist = sqrt(deltaX * deltaX + deltaY * deltaY);
            accX += k * charge * p.charge * (pos.x - p.pos.x) / pow(dist, 3);
            accY += k * charge * p.charge * (pos.y - p.pos.y) / pow(dist, 3);
        }
        Vector2 acceleration(accX, accY);
        acc = acceleration;
        return acceleration;
    }
};

#endif // PARTICLE_H
