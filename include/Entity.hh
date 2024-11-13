#include <X11/Xlib.h>
class Entity
{
public:
	float x, y;
	virtual void draw(Display*, Window , GC )=0;
	void attack();
};