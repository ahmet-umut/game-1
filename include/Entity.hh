class Entity
{
public:
	float x, y;
	virtual void draw()=0;
	void attack();
};