#define soldiercount 1<<0
#define obstaclecount 1<<1
#define polybolocount 1<<2

#include "soldier.hh"
#include "point obstacle.hh"
#include "line obstacle.hh"
#include "polybolo.hh"

deque<Soldier> soldiers;
deque<Obstacle&> obstacles;
deque<Polybolo> polybolos;

// Selects a soldier if the mouse is over it and clicked
void select(float x, float y)
{
	Soldier::selsoldier = nullptr;
	for (Soldier& soldier : soldiers)
	{
		if (soldier.isaround(x, y))
		{
			Soldier::selsoldier = &soldier;
			break;
		}
	}
}

void setupsoldiers()
{
	for (int i = 0; i < soldiercount; i++)	soldiers.emplace_back(rand()%2);
}
void setupobstacles()
{
	for (int i = 0; i < obstaclecount; i++)
	{
		switch (rand()%2)
		{
		case 0:
			obstacles.emplace_back(*new PointObstacle(Vector(rand()%800, rand()%600)));
			break;
		case 1:
			obstacles.emplace_back(*new LineObstacle(Vector(rand()%800, rand()%600), Vector(rand()%800, rand()%600)));
			break;
		}
	}
}
void setuppolybolos()
{
	deque<Polybolo>polybolos;
	for (unsigned char polybolo = 0; polybolo < polybolocount; polybolo++)
	{
		polybolos.push_back(Polybolo());
	}
}

enum gamemode {debug, game, army} mode = game;

void handlenextevent()
{
	XEvent event;
	if (mode==game || XPending(display))
	{
		XNextEvent(display, &event)
	}
}

void gameloop()
{
	bool running=true;
	while (running)
	{
		handleevent(mode);
		XClearWindow(display, window);
	}
}

#include "x utilities.hh"
int main()
{
	xsetupwindow("game", display, window, gc);
	
	//event loop
	XEvent event;	bool running = true;

	// Initialize the random number generator
	//srand(time(nullptr));

	setupsoldiers();
	setupobstacles();
	setuppolybolos();

	gameloop();	//returns when the game is over

	xcleanup(display, window, gc);
}