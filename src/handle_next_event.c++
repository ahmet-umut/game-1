#include "../include/functions.hh"
#include "../include/Polybolos.hh"

using std::deque;
gamestate handle_next_event(gamestate state, Display* display, deque<Soldier>& soldiers, deque<Polybolos>& polyboli, bool* side_effect)
{
	//printf("handling next event\n");
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
				Combatant::selected_combatant = nullptr;
				for (auto& soldier : soldiers)	if (Combatant::selected_combatant = soldier.select({event.xbutton.x, event.xbutton.y}))	goto caseend;
				for (auto& polybolos : polyboli)	if (Combatant::selected_combatant = polybolos.select({event.xbutton.x, event.xbutton.y}))	goto caseend;
				caseend:
				break;
			case 3:  // Right mouse button
				Combatant*combatant = Combatant::selected_combatant;
				if (combatant)
				{
					Combatant* target = nullptr;
					for (auto& soldier : soldiers)	if (target = soldier.select({event.xbutton.x, event.xbutton.y}))	goto after_select;
					for (auto& polybolos : polyboli)	if (target = polybolos.select({event.xbutton.x, event.xbutton.y}))	goto after_select;
					after_select:
					if (target)
					{
						combatant->task.target = target;
						combatant->task.state = Task::attack;
						printf("attacking\n");
					}
					else
					{
						combatant->task.location = {event.xbutton.x, event.xbutton.y};
						combatant->task.state = Task::go;
					}
					break;
				}
				break;
			}
			break;
		}
	}
	return state;
}