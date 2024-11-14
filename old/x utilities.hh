#include "X11/Xlib.h"
void xsetupwindow(const char* title, Display*& display, Window& window, GC& gc)
{
	// Open connection to the X server
	display = XOpenDisplay(nullptr);
	if (display == nullptr) {
		return;
	}

	// Create a simple window
	int screen = DefaultScreen(display);
	window = XCreateSimpleWindow(display, RootWindow(display, screen),0,0,
									800,600,
									0,BlackPixel(display, screen), 
									WhitePixel(display, screen));

	// Set window title
	XStoreName(display, window, title);

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

	//for (Soldier& soldier : soldiers)	soldier.properts.team = rand()%2;	//random team assignment

	//was for a testing purpose
	//soldiers[0].position = {400,300};
	//soldiers[1].position = {400,305};
}

void xcleanup(Display*& display, Window& window, GC& gc)
{
	// Destroy the graphics context
	XFreeGC(display, gc);

	// Destroy the window
	XDestroyWindow(display, window);

	// Close the connection to the X server
	XCloseDisplay(display);
}