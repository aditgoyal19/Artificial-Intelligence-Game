#ifndef _SPHERE_GO
#define _SPHERE_GO

#include "gameObject.h"

class Sphere : public GameObject
{
public:
Sphere();
~Sphere();

float getRadius();
void setRadius(float value);
private:
	float radius;
};


#endif