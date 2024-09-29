#include "comm.hh"

class IEntity
{
public:
	Vector position, velocity = {0,0};
	float direction;

	IEntity()
	{
		position = {rand()%800, rand()%600};
		//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
	}

	float distance(Vector&vector)
	{
		return (vector + -position).length();
	}
	float distance(IEntity&entity)
	{
		return (entity.position + -position).length();
	}

	virtual void attack() = 0;
};

class ITraject{};

/*	SELF NOTES

Agent.assign(Task)
Agent.assign(x) for x in task type

getter
direct access
	?

setter
direct access*

hitpoints	decremented
defence	attack	probabilities

	THINGS TO ADD
1	formation control
2	army concept
3	other soldier/agent types
4	high level game logic such as money for recruiting, etc.
5	campaign map
6	UI
	1	info text
	2	select team
7	better AI
8	path finding
9	map obstacles and stuff like that
10	shields
11	better collision checking
12	main character logic
13	tasks
14	horses
15	deformable and movable obstacles
16	castles and cities
17	siege weapons
18	team concept
19	battle concept
20	leader concept
21	auto-attack
22	readme
23	meta
*/