module;
#include <math.h>
export module vector;
#define min(a,s) ((a)<(s) ? (a):(s))
#define max(a,s) ((a)>(s) ? (a):(s))
export class Vector
{
public:
    float x, y;
    Vector() {}
    Vector(float x, float y) : x(x), y(y) {}

    static Vector fromPolar(float length, float angle)
    {
        return {length*cosf(angle), length*sinf(angle)};
    }

    Vector operator+(const Vector&vector)
    {
        return {x+vector.x, y+vector.y};
    }
    Vector operator-()
    {
        return {-x, -y};
    }
    Vector operator*(const float&scalar)
    {
        return {x*scalar, y*scalar};
    }
    Vector operator/(const float&scalar)
    {
        return {x/scalar, y/scalar};
    }

    float length()
    {
        return sqrtf(x*x + y*y);
    }
};