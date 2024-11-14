#include "entity.hh"
class Weapon: public Entity
{
public:
	Weapon(){}
	virtual Vector tip() = 0;
};