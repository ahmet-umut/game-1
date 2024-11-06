In this game; I will continue on my previous -unfinished- game project (That was written in Python.), switching to C++.

# game details
Meeting the computer and the internet since I was born (2001), I have been playing browser and computer games since -or maybe even before- I know how to read! Since those young ages, I have always imagined making my own game where I can add any functionality I wanted. This 2d game is one of the milestones of my dream.

This is a 2d game, inspired from game series Total War, Age of Empires and Mount&Blade. I will be implementing some aspects of every series as time progresses. This game includes 2d agents (represented by circles). They can hold weapons in their hands (So far, there is only one weapon. Which is a spear. Whether the tip of the weapon is inside the agent is checked to decide if a soldier is hit with a spear.

There are also static obstacles (planning to add dynamic ones in the near future). One of the types of static obstacles is a line obstacle. The agents cannot pass thru it, they need to traverse around them. The obstacle class is defined as 2 vectors, each pointing to the endpoints of the line segment.

I am now in the way of designing a path finding algorithm for this continuous environment.

# development details
Using Xlib for visualization. I want to focus on the game mechanics rather than performance in this early stage, so decided to use Xlib -the library of the X Server. In the future I may switch the project to a hardware rendering solution.

## classes
### Vector
2d vector to remove redundancies. In my past games and simulations, I used to define x and y seperately for every suitable feature such as position and velocity. I decided to give a custom vector class a try to see its effects on implementation and -less important- performance.
I use this class to also measure distances (basically measuring the length of a position delta vector) and define positions of the agents' swords.

### IAgent
Base class for Agent. Defines a interface to be used in Task class. The reason I needed this is that I decided to include a Task member inside a Agent class. But then the Task objects also used some of the members and functions of the Agent class. This circular dependency can be solved in a lot of ways and I decided to use this solution.
I am using virtual functions to handle this circular dependency.

### ITask
Normally, a Base class for Task. However, it is empty because apparently I do not yet need a base class in the current scenario.

### Agent
The main class of the game. They are entities that exist in a 2d space. Each has a position, velocity and also a **weapon position** defining how _swung_ the weapon is (For now it is a 1 dimensional variable.).
They have a instance of a class named Tasks, I plan which to be the main way to control them.

### Task
2 types exist so far: go, attack.
#### go
Go to a global location.
#### attack
Go towards the agent you are assigned to attack if you are not close enough (maxerror), if you are close enough, turn a little towards the enemy and swing the spear.
