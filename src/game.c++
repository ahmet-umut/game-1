#include <iostream>
#include <unistd.h>	//for sleep and usleep
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
	gameloop();	//returns when the game is over
}