module;
#include "../../include/gamestate.hh"
#include "../../include/xlib.hh"
export module handle_next_event;
#include <stdio.h>

using namespace std;
export gamestate handle_next_event(gamestate state, Display* display)
{
	printf("handling next event\n");
	if (XPending(display))
	{
		XEvent event;
		XNextEvent(display, &event);
		switch (event.type)
		{
		case KeyPress:
			switch (event.xkey.keycode)
			{
			case 38:	//a
				/* mode = (mode==army) ? (cout<<"arrmymode off", game) : (cout<<"arrmymode on", army);	cout<<endl; */
				break;
			case 65:  // Space key
				switch (state)
				{
				case running:
					state = halt;
					printf("halted the game\n");
					break;

				default:
					state = running;
					printf("continuing the game\n");
					break;
				}
				break;
			}
			break;
		case ButtonPress:
			switch (event.xbutton.button)
			{
			case 1:  // Left mouse button
				//select(event.xbutton.x, event.xbutton.y);
				break;
			}
			break;
		}
	}
	return state;
}