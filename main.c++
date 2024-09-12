#include <X11/Xlib.h>
#include <unistd.h>  // For usleep()

#include <iostream>
using namespace std;

int main() {
	// Open connection to the X server
	Display *display = XOpenDisplay(nullptr);
	if (display == nullptr) {
		return -1;
	}

	// Create a simple window
	int screen = DefaultScreen(display);
	Window window = XCreateSimpleWindow(display, RootWindow(display, screen),0,0,
										800,600,
										0,BlackPixel(display, screen), 
										WhitePixel(display, screen));

	// Select input events for the window (e.g., key press, mouse click)
	XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);

	// Map (show) the window
	XMapWindow(display, window);

	// Create a graphics context for drawing
	GC gc = XCreateGC(display, window, 0, nullptr);

	// Set drawing color (black)
	XSetForeground(display, gc, BlackPixel(display, screen));
	XFillRectangle(display, window, gc, 50, 50, 200, 100);

	// Event loop
	XEvent event;
	bool running = true;

	short int x,y;
	while (running) {
		// Wait for an event
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
			case 36:  // Enter key
				XFillRectangle(display, window, gc, 50, 50, 200, 100);
				break;
			
			default:
				break;
			}
		case ButtonPress:
			switch (event.xbutton.button)
			{
			case 1:  // Left mouse button
				x = event.xbutton.x, y = event.xbutton.y;
				break;
			
			default:
				break;
			}
		case ButtonRelease:
			switch (event.xbutton.button)
			{
			case 1:  // Left mouse button
				XDrawRectangle(display, window, gc, x,y, event.xbutton.x-x, event.xbutton.y-y);
				break;
			
			default:
				break;
			}
		
		default:
			break;
		}

		// Slow down the loop a bit to avoid excessive CPU usage
		usleep(100000);
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