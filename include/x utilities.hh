#pragma once
void xsetupwindow(const char* title, Display*& display, Window& window, GC& gc, int screenwidth, int screenheight)
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

    // Event loop (implementation may vary based on your requirements)
    XEvent event;
    bool running = true;
}