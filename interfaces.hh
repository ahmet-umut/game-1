#include "comm.hh"
#include "math.h"

class IAgent    // Interface for agents, needed to be used in Task
{
public:
    virtual float distance(Vector&vector) = 0;
    virtual float distance(IAgent&agent) = 0;
    virtual void attack() = 0;

	Vector position, velocity;
    float direction;

    IAgent() {}
    IAgent(float velocity) : velocity({velocity,velocity}) {}
};

class ITask{};


/*
Agent.assign(Task)
Agent.assign(x) for x in task type

getter
direct access
?

setter
direct access*
*/