#include "obstacle.hh"
class LineObstacle: public Obstacle
{
public:
	LineSegment lineSegment;

	LineObstacle(Vector point1, Vector point2) : lineSegment(point1, point2 +- point1)
	{
		type=line;
	}

	bool isintersecting(Soldier& soldier)
	{
		Vector middle = lineSegment.start + lineSegment.delta / 2;
		Vector intersec;
		short int v1 = lineSegment.delta.x;
		short int v2 = lineSegment.delta.y;
		short int v3 = middle.y - middle.x * v2 / v1;
		short int v4 = soldier.position.y + soldier.position.x * v1 / v2;
		intersec.x = (v4 - v3) * v1 * v2 / (float)(v1 * v1 + v2 * v2);
		intersec.y = intersec.x * v2 / v1 + v3;

		if (soldier.isaround(lineSegment.start) || soldier.isaround(lineSegment.end())) return true;
		if (soldier.isaround(intersec) && ((intersec.x < lineSegment.start.x && intersec.x > lineSegment.end().x) || (intersec.x > lineSegment.start.x && intersec.x < lineSegment.end().x))) return true;
		return false;
	}
	Vector correction(Soldier& soldier)
	{
		Vector intersec;
		Vector middle = lineSegment.start + lineSegment.delta / 2;
		short int v1 = lineSegment.delta.x;
		short int v2 = lineSegment.delta.y;
		short int v3 = middle.y - middle.x * v2 / v1;
		short int v4 = soldier.position.y + soldier.position.x * v1 / v2;
		intersec.x = (v4 - v3) * v1 * v2 / (float)(v1 * v1 + v2 * v2);
		intersec.y = intersec.x * v2 / v1 + v3;

		if (!(intersec.x < lineSegment.start.x && intersec.x > lineSegment.end().x) || (intersec.x > lineSegment.start.x && intersec.x < lineSegment.end().x))
		{
			Vector posdif = soldier.position + -intersec;
			return posdif / posdif.length() * (2*Soldier::radius - posdif.length());
		}
		else
		{
			Vector posdif = soldier.position + -lineSegment.start;
			return posdif / posdif.length() * (2*Soldier::radius - posdif.length());
		}
	}
};