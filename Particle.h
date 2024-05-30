#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <algorithm>
#include "Vector2.h"

const float k = 30.0f;
const float kFriction = 0.0f;
const float kDrag = 0.0f;

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
        float velMag = vel.magnitude();

        if (velMag > 0) {
            accX -= vel.x / velMag * kFriction + vel.x * kDrag;
            accY -= vel.y / velMag * kFriction + vel.y * kDrag;
        }

        const float epsilon = 1e-5f; // Small value to avoid division by zero

        for (const auto& p : particles) {
            if (&p == this) continue; // Avoid self-interaction

            float deltaX = pos.x - p.pos.x;
            float deltaY = pos.y - p.pos.y;
            float dist2 = deltaX * deltaX + deltaY * deltaY;

            if (dist2 < epsilon) continue; // Skip if the distance is too small

            float dist = std::sqrt(dist2);
            float dist3 = dist * dist2; // Equivalent to dist^3
            float force = k * charge * p.charge / dist3;
            force = std::min(force, 10.0f);

            accX += force * deltaX;
            accY += force * deltaY;
        }

        acc = Vector2(accX, accY);
        return acc;
    }
};

#endif // PARTICLE_H
