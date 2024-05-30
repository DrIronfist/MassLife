#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <cmath>
#include <algorithm>

struct Vector2 {
    float x;
    float y;

    // Constructor
    Vector2(float d, float d0) : x(d), y(d0) {}
};

float magnitude(const Vector2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Vector2 subtractMagnitude(const Vector2& v, float amount) {
    float mag = magnitude(v);

    // Calculate the new magnitude after subtracting the amount
    float newMag = mag - amount;
    if (newMag < 0) newMag = 0; // Ensure magnitude doesn't go negative
    // Normalize the vector to get its direction and multiply by the new magnitude
    return Vector2(v.x * (newMag / mag), v.y * (newMag / mag));
}

const float k = 30;
const float kFriction = 0;
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
        float velMag = magnitude(vel);
        if (velMag > 0) {
            accX -= vel.x / velMag * kFriction + vel.x * kDrag;
            accY -= vel.y / velMag * kFriction + vel.y * kDrag;
        }
        const float epsilon = 1e-5f; // Small value to avoid division by zero

        for (const Particle& p : particles) {
            if (&p == this) continue; // Avoid self-interaction

            float deltaX = pos.x - p.pos.x;
            float deltaY = pos.y - p.pos.y;
            float dist2 = deltaX * deltaX + deltaY * deltaY;

            if (dist2 < epsilon) continue; // Skip if the distance is too small

            float dist = sqrt(dist2);
            float dist3 = dist * dist2; // Equivalent to dist^3
            float force = k * charge * p.charge / dist3;
            force = std::min(force, 10.0f); // Cap the force to avoid excessive acceleration

            accX += force * deltaX;
            accY += force * deltaY;
        }

        acc = Vector2(accX, accY);
        return acc;
    }
};

#endif // PARTICLE_H
