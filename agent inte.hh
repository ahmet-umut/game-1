#pragma once
#include "comm.hh"
#include <math.h>

class ITask;
class IAgent
{
public:
    inline static IAgent*selagent = nullptr;
	Vector position, velocity;	float direction;	//direction is in radians
	float weaponpo=0;
	ITask*task = nullptr;
    
    IAgent() {}
	IAgent(float velocity) : velocity({velocity,velocity})
	{
		position.x = rand()%800;
		position.y = rand()%600;
	}
	IAgent(float positiox, float positioy) : position({positiox,positioy})
	{
		velocity.x = (rand()%100 - 50)/10;
		velocity.y = (rand()%100 - 50)/10;
	}
	IAgent(float positiox, float positioy, float velocitx, float velocity) : position({positiox,positioy}), velocity({velocitx,velocity})	{}

    virtual void draw() = 0;
    virtual void execute() = 0;
    virtual float distance(IAgent&agent)
    {
        return (agent.position + -position).length();
    }
	virtual void attack()
	{
		weaponpo+=10;
	}
	virtual void assign(float x, float y)=0;
};
