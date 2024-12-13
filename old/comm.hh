#pragma once
#include <math.h>

#include "xlib.hh"
#define xpoint XPoint

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
    xpoint toXpoint()
    {
        return {(short)x, (short)y};
    }
};

class LineSegment
{
public:
    Vector start, delta;
    LineSegment(Vector start, Vector delta) : start(start), delta(delta) {}

    Vector end() {
        return start + delta;
    }

    bool isIntersecting(LineSegment& lineSegment)
    {
        auto orientation = [](Vector p, Vector q, Vector r) {
            float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
            if (val == 0) return 0;  // collinear
            return (val > 0) ? 1 : 2; // clock or counterclock wise
        };

        auto onSegment = [](Vector p, Vector q, Vector r) {
            if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
                q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
                return true;
            return false;
        };

        Vector p1 = start, q1 = end();
        Vector p2 = lineSegment.start, q2 = lineSegment.end();

        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != o2 && o3 != o4)
            return true;

        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false;
    }
};

#include <unistd.h>  // For usleep()
#include <stdlib.h>  // For drand48() and rand()

#include <iostream>
using namespace std;

Display *display;	Window window;	GC gc;

#define bacolor 0x00FFFFFF
#define encolor 0x00000000
#define secolor 0x00FF0000

#include <deque>