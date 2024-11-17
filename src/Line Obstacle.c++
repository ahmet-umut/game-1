#include "../include/Line Obstacle.hh"
#include <eigen3/Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
void LineObstacle::draw(Display*display, Window window, GC gc)
{
	XSetForeground(display, gc, 0);
	XDrawLine(display, window, gc, lineSegment.start.x(), lineSegment.start.y(), (lineSegment.start + lineSegment.delta).x(), (lineSegment.start + lineSegment.delta).y());
}
LineObstacle::LineObstacle()
{
	cout << "LineObstacle::LineObstacle(), default initiation" << endl;
	type = line;
}
LineObstacle::LineObstacle(double x1, double y1, double x2, double y2) : lineSegment(Vector2d(x1,y1), Vector2d(x2,y2))
{
	type = line;
}
bool LineObstacle::is_intersecting(Soldier& soldier)
{
	Vector2d middle = lineSegment.start + lineSegment.delta / 2;
	Vector2d intersec;
	short int v1 = lineSegment.delta.x();
	short int v2 = lineSegment.delta.y();
	short int v3 = middle.y() - middle.x() * v2 / v1;
	short int v4 = soldier.position.y() + soldier.position.x() * v1 / v2;
	intersec.x() = (v4 - v3) * v1 * v2 / (float)(v1 * v1 + v2 * v2);
	intersec.y() = intersec.x() * v2 / v1 + v3;

	((Soldier*)(&soldier))->is_around(intersec);
	((Combatant*)(&soldier))->is_around(intersec);

	if (soldier.is_around(lineSegment.start) || soldier.is_around(lineSegment.end())) return true;
	if (soldier.is_around(intersec) && ((intersec.x() < lineSegment.start.x() && intersec.x() > lineSegment.end().x()) || (intersec.x() > lineSegment.start.x() && intersec.x() < lineSegment.end().x()))) return true;
	return false;
}
Vector2d LineObstacle::correction(Soldier& soldier)
{
	cout << "LineObstacle::correction" << endl;
	return Vector2d(0,0);
}