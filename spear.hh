#include "weapon.hh"

class Spear: public Weapon
{
public:
    static inline const unsigned char length = 10;
    Spear()
    {
        position = {rand()%800, rand()%600};
        direction = rand()%1000/1000.0*2*M_PIf;	//random direction
    }
    Vector tip()
    {
        return position + Vector::fromPolar(length, direction);
    }
};