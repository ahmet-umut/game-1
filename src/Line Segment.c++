#include "../include/Line Segment.hh"
#define min(a,s) ((a)<(s) ? (a):(s))
#define max(a,s) ((a)>(s) ? (a):(s))

LineSegment::LineSegment(Eigen::Vector2d start, Eigen::Vector2d delta) : start(start), delta(delta) {}

Eigen::Vector2d LineSegment::end()
{
    return start + delta;
}

bool LineSegment::isIntersecting(LineSegment& lineSegment)
{
    auto orientation = [](Eigen::Vector2d p, Eigen::Vector2d q, Eigen::Vector2d r) {
        float val = (q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());
        if (val == 0) return 0;  // collinear
        return (val > 0) ? 1 : 2; // clock or counterclock wise
    };

    auto onSegment = [](Eigen::Vector2d p, Eigen::Vector2d q, Eigen::Vector2d r) {
        if (q.x() <= max(p.x(), r.x()) && q.x() >= min(p.x(), r.x()) &&
            q.y() <= max(p.y(), r.y()) && q.y() >= min(p.y(), r.y()))
            return true;
        return false;
    };

    Eigen::Vector2d p1 = start, q1 = end();
    Eigen::Vector2d p2 = lineSegment.start, q2 = lineSegment.end();

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