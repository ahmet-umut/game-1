#pragma once
#include <math.h>
class Vector
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

#include <X11/Xlib.h>
#include <unistd.h>  // For usleep()
#include <stdlib.h>  // For drand48() and rand()

#include <iostream>
using namespace std;

Display *display;	Window window;	GC gc;

#define bacolor 0x00FFFFFF
#define agcolor 0x00000000
#define secolor 0x00FF0000