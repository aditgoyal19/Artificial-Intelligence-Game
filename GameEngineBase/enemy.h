#ifndef _ENEMY_H 
#define _ENEMY_H

#include "gameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();

	void Update( float deltaTime );

	//sets if Enemy is a boss 
	void setIsBoss();

	//sets if Enemy Has a boss 
	void setBossId(int value);

	//fetches Boss Id
	int getBossId();

private:
	std::vector <GameObjectBase*> nodes;
	int nodeIndex;
	int age;
	bool isBoss;
	int bossId ;  // if bossId = 0 then enemy has no boss 
	float Yoffset;
};

#endif