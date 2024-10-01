#include "obstacle.hh"
class PointObstacle: public Obstacle
{
public:
	Vector position;
	PointObstacle(Vector position) : position(position)
	{
		type=point;
	}
	bool isintersecting(Soldier& soldier)
	{
		return (soldier.position + -position).length() < 2*Soldier::radius;
	}
	Vector correction(Soldier& soldier)
	{
		Vector posdif = soldier.position + -position;
		return posdif / posdif.length() * (2*Soldier::radius - posdif.length());
	}
};