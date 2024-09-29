#include "classes.hh"

#define nosoldiers 1<<0
#define noobstacles 1<<1
#define nopolybolos 1<<2

Soldier soldiers[nosoldiers];

void select(float x, float y)
{
	Soldier::selsoldier = nullptr;
	for (Soldier& soldier : soldiers)
	{
		if (x > soldier.position.x-radius && x < soldier.position.x+radius && y > soldier.position.y-radius && y < soldier.position.y+radius)
		{
			Soldier::selsoldier = &soldier;
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
	//XSetForeground(display, gc, BlackPixel(display, screen));	//commented out, because I choose the color when I draw.

	// Event loop
	XEvent event;
	bool running = true;

	// Initialize the random number generator
	//srand(time(nullptr));

	for (Soldier& soldier : soldiers)	soldier.properts.team = rand()%2;	//random team assignment

	//was for a testing purpose
	soldiers[0].position = {400,300};
	soldiers[1].position = {400,305};

	while (0)
	{
		XNextEvent(display, &event);
		if (event.type==KeyPress)	break;
	}

	deque<Lineobs>lineobss;	deque<Pointobs> pointobss;
	for (unsigned char obsti = 0; obsti < noobstacles; obsti++)
	{
		switch (rand()%2)
		{
		#define pushback push_back
		case 0:
			pointobss.pushback(Pointobs({rand()%800, rand()%600}));
			break;
		case 1:
			lineobss.pushback(Lineobs({rand()%800, rand()%600},{rand()%800, rand()%600}));
			break;
		
		default:
			break;
		}
	}

	deque<Polybolo>polybolos;
	for (unsigned char polybolo = 0; polybolo < nopolybolos; polybolo++)
	{
		polybolos.push_back(Polybolo());
	}

	enum {debugmode, gamemode, armymode} mode = gamemode;
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
						cout << "drawing soldiers\n";
						for (Soldier& soldier : soldiers)
						{
							soldier.draw();
						}
						break;
					case 38:	//a
						mode = (mode==armymode) ? (cout<<"arrmymode off", gamemode) : (cout<<"arrmymode on", armymode);	cout<<endl;
						break;
					case 65:  // Space key
						mode = (mode == debugmode) ? gamemode : debugmode;
						cout << "Switched to " << (mode == debugmode ? "debug mode" : "game mode") << "\n";
						break;

					case 39:  // 's' key
						for (Polybolo& polybolo : polybolos) {
							polybolo.attack();
						}
						break;
					
					default:
						break;
					}
				case ButtonPress:
					if (mode==debugmode)	cout << "button press" << event.xbutton.x << " " << event.xbutton.y << "\n";
					switch (event.xbutton.button)
					{
					case 1:  // Left mouse button
						select(event.xbutton.x, event.xbutton.y);
						break;
					case 2:  // Middle mouse button
						if (Soldier::selsoldier)	Soldier::selsoldier->attack();
						break;
					case 3:  // Right mouse button
						switch (mode)
						{
						case gamemode:
							if (Soldier::selsoldier)
							{
								//if the clicked area is inside in any soldier
								for (Soldier& soldier : soldiers)
									if (event.xbutton.x > soldier.position.x-radius && event.xbutton.x < soldier.position.x+radius && event.xbutton.y > soldier.position.y-radius && event.xbutton.y < soldier.position.y+radius)
									{
										Task *task = new Task(Soldier::selsoldier, &soldier);
										Soldier::selsoldier->assign(task);
										delete task;
										cout << "assigned attack task\n";
										goto endcase;
									}
								Task *task = new Task(Soldier::selsoldier, event.xbutton.x, event.xbutton.y);
								Soldier::selsoldier->assign(task);
								delete task;
								cout << "assigned go task\n";
							}
							endcase:
							break;
						case armymode:
							for (auto &&soldier : soldiers)
							{
								if (soldier.properts.team)
								{
									Task *task = new Task(&soldier, event.xbutton.x, event.xbutton.y);
									soldier.assign(task);
									delete task;
								}
							}
							
							break;
						
						default:
							break;
						}
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

		for (Polybolo& polybolo : polybolos)	polybolo.draw();
		
		for (Soldier& soldier0 : soldiers)
		{
			soldier0.draw();

			for (Trajecti& traject : trajects)
			{
				Vector trajetip = traject.position + Vector::fromPolar(trajectile_length, traject.direction);
				if (soldier0.isaround(trajetip))	soldier0.gethit();
			}
		}

		#define msperframe 1000/60
		usleep(msperframe*1000);

		XSetForeground(display, gc, secolor);
		for (auto &&obst : pointobss)
		{
			#define indicato 9
			for (unsigned char cursor = 0; cursor < indicato; cursor++)
			{
				XDrawPoint(display, window, gc, obst.position.x+cursor, obst.position.y);
				XDrawPoint(display, window, gc, obst.position.x-cursor, obst.position.y);
				XDrawPoint(display, window, gc, obst.position.x, obst.position.y+cursor);
				XDrawPoint(display, window, gc, obst.position.x, obst.position.y-cursor);
			}
		}
		for (auto &&obst : lineobss)
		{
			XDrawLine(display, window, gc, obst.point1.x, obst.point1.y, obst.point2.x, obst.point2.y);
		}
		
		for (Soldier& soldier : soldiers)
		{
			for (auto &&obst : pointobss)	if (obst.isinters(soldier))	soldier.position = soldier.position + obst.correction(soldier);	//cout<<"point inters\n";	//obstacle avoid
			for (auto &&obst : lineobss)	if (obst.isinters(soldier))	soldier.position = soldier.position + obst.correction(soldier);	//cout<<"line inters\n";	//obstacle avoid
		}

		for (Trajecti& traject : trajects)	traject.draw();
		for (Trajecti& traject : trajects)	if (!traject.execute())	for (auto it = trajects.begin(); it != trajects.end(); ++it)	if (&*it == &traject)	trajects.erase(it);
		cout << trajects.size() << endl;

		for (Soldier& soldier0 : soldiers)
		{
			soldier0.execute();

			//collision handling between soldiers
			float distance;
			for (Soldier& soldier1 : soldiers)	if (&soldier0!=&soldier1)	if ((distance = soldier0.distance(soldier1)) < 2*radius)
			{
				Vector posdif01 = soldier1.position +- soldier0.position;
				soldier0.position = soldier0.position +- posdif01 / distance * (radius - distance/2);
				soldier1.position = soldier1.position +  posdif01 / distance * (radius - distance/2);
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