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

enum gamestate {running, halt, runonce, end};
gamestate state = running;

void handlenextevent()
{
	XEvent event;
	if (XPending(display))
	{
		XNextEvent(display, &event);
		switch (event.type)
		{
		case KeyPress:
			switch (event.xkey.keycode)
			{
			case 9:  // Escape key
				state=end;
				break;
			case 36:  // Enter key	for debug mode for step by step debugging
				cout << "debug step\n";
				state=runonce;
				break;
			case 40:  // 'd' key
				cout << "drawing soldiers\n";
				for (Soldier& soldier : soldiers)
				{
					soldier.draw();
				}
				break;
			case 38:	//a
				/* mode = (mode==army) ? (cout<<"arrmymode off", game) : (cout<<"arrmymode on", army);	cout<<endl; */
				break;
			case 65:  // Space keyd
				switch (state)
				{
				case running:
					state=halt;
					cout << "halted the game";
					break;
				
				default:
					state=running;
					cout << "continuing the game";
					break;
				}
				break;
			}
			break;
		case ButtonPress:
			switch (event.xbutton.button)
			{
			case 1:  // Left mouse button
				select(event.xbutton.x, event.xbutton.y);
				break;
			}
			break;
		}
	}
}

void gameloop()
{
	while (1)
	{
		handlenextevent();
		switch (state)
		{
		case halt:
			continue;
		case runonce:
			state=halt;
			break;
		case end:
			return;
		}
		cout << "game tick";
		sleep(1);
		//XClearWindow(display, window);
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