#include "../include/Polybolos.hh"
#include <iostream>
using namespace std;

bool Polybolos::is_around(double x, double y)
{
	Eigen::Vector2d point(x,y);
	return (point - position).norm() < 5;	//5 is the estimated radius of the polybolo
}
void Polybolos::draw(Display*display, Window window, GC gc)
{
	XRectangle rectangles[2];
	rectangles[0].x = position.x() - 5;
	rectangles[0].y = position.y() - 5;
	rectangles[0].width = 11;
	rectangles[0].height = 11;

	rectangles[1].x = position.x() + 11 * cos(direction);
	rectangles[1].y = position.y() + 11 * sin(direction);
	rectangles[1].width = 2;
	rectangles[1].height = 2;
	XDrawRectangles(display, window,gc, rectangles, 2);
}
void Polybolos::execute()
{
	//cout << "Executing Polybolos" << endl;
	// Execute the polybolo
}
Projectile Polybolos::fire()
{
	Projectile* projectile = new Projectile(position.x(), position.y(), direction);
	projectiles->insert({this, projectile});

	cout << "Polybolos::fire" << endl;
	
	return *projectile;
}
