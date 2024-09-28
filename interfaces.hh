#include "comm.hh"

class ISoldier    // Interface for agents, needed to be used in Task
{
public:
	virtual float distance(Vector&vector) = 0;
	virtual float distance(ISoldier&agent) = 0;
	virtual void attack() = 0;

	Vector position, velocity;
	float direction;

	ISoldier() {}
	ISoldier(float velocity) : velocity({velocity,velocity}) {}
};

class ITask{};


/*
SELF NOTES

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
7	better AI
8	path finding
9	map obstacles and stuff like that
10	shields
11	better collision checking
12	main character logic
13	
14	horses
15	deformable and movable obstacles
16	castles and cities
17	siege weapons
18	team concept
19	battle concept
20	leader concept
21	auto-attack
*/