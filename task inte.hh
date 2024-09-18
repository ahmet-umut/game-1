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

    virtual void execute() = 0;
};