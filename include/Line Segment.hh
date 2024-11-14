#pragma once
#include <eigen3/Eigen/Dense>
class LineSegment
{
public:
    Eigen::Vector2d start, delta;
    LineSegment(Eigen::Vector2d start, Eigen::Vector2d delta);

    Eigen::Vector2d end();

    bool isIntersecting(LineSegment& lineSegment);
};