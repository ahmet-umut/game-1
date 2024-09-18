#include "agent.hh"
#include "task.hh"

#define noagents 2
Agent agents[noagents];

void select(float x, float y)
{
	Agent::selagent = nullptr;
	for (Agent& agent : agents)
	{
		if (x > agent.position.x-radius && x < agent.position.x+radius && y > agent.position.y-radius && y < agent.position.y+radius)
		{
			Agent::selagent = &agent;
			break;
		}
	}
}

int main() {
	// Open connection to the X server
	display = XOpenDisplay(nullptr);
	if (display == nullptr) {
		return -1;
	}

	// Create a simple window
	int screen = DefaultScreen(display);
	window = XCreateSimpleWindow(display, RootWindow(display, screen),0,0,
										800,600,
										0,BlackPixel(display, screen), 
										WhitePixel(display, screen));

	// Set window title
	XStoreName(display, window, "game");

	// Select input events for the window (e.g., key press, mouse click)
	XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);

	// Map (show) the window
	XMapWindow(display, window);

	// Create a graphics context for drawing
	gc = XCreateGC(display, window, 0, nullptr);

	// Set drawing color (black)
	XSetForeground(display, gc, BlackPixel(display, screen));

	// Event loop
	XEvent event;
	bool running = true;

	// Initialize the random number generator
	//srand(time(nullptr));

	for (Agent& agent : agents)	agent = Agent(0);
	agents[0].position = {400,300};
	agents[1].position = {400,305};

	while (0)
	{
		XNextEvent(display, &event);
		if (event.type==KeyPress)	break;
	}

	enum {debugmode, gamemode} mode = debugmode;
	short int x,y;
	while (running) {
		if (mode==debugmode || XPending(display))	//for every frame, handle up to one event || if in debug mode, handle exactly 1 event.
		{
			XNextEvent(display, &event);
			switch (event.type)
			{
				case Expose:
					/* code */
					break;
				case KeyPress:
					switch (event.xkey.keycode)
					{
					case 9:  // Escape key
						running = false;
						break;
					case 36:  // Enter key	for debug mode for step by step debugging
						cout << "debug step\n";
						goto debustep;
						break;
					case 40:  // 'd' key
						cout << "drawing agents\n";
						for (Agent& agent : agents)
						{
							agent.draw();
						}
						break;
					case 65:  // Space key
						mode = (mode == debugmode) ? gamemode : debugmode;
						cout << "Switched to " << (mode == debugmode ? "debug mode" : "game mode") << "\n";
						break;
					
					default:
						break;
					}
				case ButtonPress:
					switch (event.xbutton.button)
					{
					case 1:  // Left mouse button
						select(event.xbutton.x, event.xbutton.y);
						break;
					case 3:  // Right mouse button
						if (Agent::selagent)	cout << "Task created\n", Agent::selagent->task = new Task(*Agent::selagent, event.xbutton.x, event.xbutton.y);
						break;
					
					default:
						break;
					}
				case ButtonRelease:
					switch (event.xbutton.button)
					{
					case 1:  // Left mouse button
						break;
					
					default:
						break;
					}
				
				default:
					break;
			}
		}
		if (mode==debugmode)	continue;
		debustep:

		XClearWindow(display, window);
		for (Agent& agent : agents)
		{
			agent.draw();
		}

		#define msperframe 1000/60
		usleep(msperframe*1000);

		for (Agent& agent0 : agents)
		{
			agent0.execute();
		}
		for (Agent& agent0 : agents)
		{
			float distance;
			for (Agent& agent1 : agents)	if (&agent0!=&agent1)	if ((distance = agent0.distance(agent1)) < 2*radius)
			{
				cout << "Collision\n" << distance << '\n';
				Vector posdif01 = agent1.position - agent0.position, posdif10 = agent0.position - agent1.position;
				agent0.position += posdif10 / distance / (1 / (radius - distance/2));
				agent1.position += posdif01 / distance / (1 / (radius - distance/2));
			}
		}
	}

	// Cleanup
	XFreeGC(display, gc);
	XDestroyWindow(display, window);
	XCloseDisplay(display);

	return 0;
}
/*
g++ main.c++ -o main -lX11
./main
*/