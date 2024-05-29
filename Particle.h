#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

struct Vector2 {
    float x;
    float y;

    // Constructor
    Vector2(float d, float d0) : x(d), y(d0) {}
};

const float k = 30.0f;

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
    Vector2 updateAcceleration(const std::vector<Particle>& particles) {
        float accX = 0.0f;
        float accY = 0.0f;
        const float epsilon = 1e-5f; // Small value to avoid division by zero

        for (int i = 0; i < particles.size(); i++) {
            const Particle& p = particles[i];
            if (&p == this) continue; // Avoid self-interaction

            float deltaX = pos.x - p.pos.x;
            float deltaY = pos.y - p.pos.y;
            float dist2 = deltaX * deltaX + deltaY * deltaY;

            if (dist2 < epsilon) continue; // Skip if the distance is too small

            float dist = sqrt(dist2);
            float dist3 = dist * dist2; // Equivalent to dist^3
            float force = k * charge * p.charge / dist3;
            accX += force * deltaX;
            accY += force * deltaY;
        }
//        cout << accX << endl;
//        cout << accY << endl;
        Vector2 acceleration(accX, accY);
        acc = acceleration;
        return acceleration;
    }

};

#endif // PARTICLE_H
