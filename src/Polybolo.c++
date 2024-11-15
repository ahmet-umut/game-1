#include "../include/Polybolo.hh"
#include <iostream>
using namespace std;

Polybolo::Polybolo(double x, double y)
{
	position = Eigen::Vector2d(x, y);
	//direction = rand()%1000/1000.0*2*M_PIf;	//random direction
}
void Polybolo::draw(Display*display, Window window, GC gc)
{
	XRectangle rectangles[2];
	rectangles[0] = {.x = position.x()-5, .y = position.y()-5, .width = 10, .height = 10};
	XDrawRectangles(display, window,gc, rectangles,1);
}
void Polybolo::execute()
{
	cout << "Executing Polybolo" << endl;
	// Execute the polybolo
}