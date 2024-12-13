module;
#include "../../include/xlib.hh"
export module x_utilities;

export void xsetupwindow(const char* title, Display*& display, Window& window, GC& gc, int screenwidth, int screenheight)
{
    // Open connection to the X server
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        return;
    }

    // Create a simple window
    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0,
                                  screenwidth, screenheight,
                                  0, BlackPixel(display, screen), 
                                  WhitePixel(display, screen));

    // Set window title
    XStoreName(display, window, title);

    // Select input events for the window (e.g., key press, mouse click)
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

    // Map (show) the window
    XMapWindow(display, window);

    // Create a graphics context for drawing
    gc = XCreateGC(display, window, 0, nullptr);
}

export void xcleanup(Display*& display, Window& window, GC& gc)
{
	// Destroy the graphics context
	XFreeGC(display, gc);

	// Destroy the window
	XDestroyWindow(display, window);

	// Close the connection to the X server
	XCloseDisplay(display);
} 