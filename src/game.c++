#include <iostream>
#include <unistd.h>	//for sleep and usleep

void setup_obstacles()
{
	using namespace std;
	cout << "setting up obstacles" << endl;
	//for (int i = 0; i < obstaclecount; i++)
	//{
	//	switch (rand()%2)
	//	{
	//	case 0:
	//		obstacles.emplace_back(*new PointObstacle(Vector(rand()%800, rand()%600)));
	//		break;
	//	case 1:
	//		obstacles.emplace_back(*new LineObstacle(Vector(rand()%800, rand()%600), Vector(rand()%800, rand()%600)));
	//		break;
	//	}
	//}
}

void gameloop()
{
	using namespace std;
	while (1)
	{
		sleep(1);
		cout << "game tick" << endl;
	}
}

int main()
{
	setup_obstacles();
	gameloop();	//returns when the game is over
}