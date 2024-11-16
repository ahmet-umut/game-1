#include "../include/functions.hh"

using std::deque;
gamestate handle_next_event(gamestate state, Display* display, deque<Soldier>& soldiers, bool* side_effect)
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
			case 9:  // Escape key
				state = end;
				printf("ending the game\n");
				break;
			case 36:  // Enter key
				if (side_effect)
					*side_effect = true;
				break;
			}
			break;
		case ButtonPress:
			switch (event.xbutton.button)
			{
			case 1:  // Left mouse button
				for (auto& soldier : soldiers)
				{
					if (soldier.is_around(event.xbutton.x, event.xbutton.y))
					{
						soldier.select();
						break;
					}
				}
				break;
			}
			break;
		}
	}
	return state;
}