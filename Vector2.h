#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

struct Vector2 {
    float x;
    float y;

    // Constructor
    Vector2(float d = 0.0f, float d0 = 0.0f) : x(d), y(d0) {}

    // Magnitude of the vector
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Subtract magnitude from the vector
    Vector2 subtractMagnitude(float amount) const {
        float mag = magnitude();
        if (mag == 0) return *this;

        float newMag = mag - amount;
        return Vector2(x * (newMag / mag), y * (newMag / mag));
    }

    // Normalize the vector
    Vector2 normalize() const {
        float mag = magnitude();
        if (mag == 0) return *this;
        return Vector2(x / mag, y / mag);
    }
};

#endif // VECTOR2_H
