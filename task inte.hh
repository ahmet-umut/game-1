#pragma once
#include "comm.hh"
#include <memory>

class IAgent;
class ITask
{
public:
    Vector goal;
    IAgent*agent;
    bool active = false;

	ITask() {}
	ITask(IAgent&agent, float x, float y) : goal({x,y}), agent(&agent), active(true)	{}
    ITask(IAgent&agent, Vector&goal) : goal(goal), agent(&agent), active(true)	{}
    
    void operator|(Vector&goal)
    {
        this->goal = goal;
        active = true;
    }

    virtual void execute() = 0;
};