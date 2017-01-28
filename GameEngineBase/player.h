#ifndef _PLAYER_H 
#define _PLAYER_H

#include "gameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update( float deltaTime );


	//
	void setHealth(int value);
	int getHealth();

	void setShield(int value);
	int getShield();

	void isBeingAttacked();
	void gotPowerUp();

	bool isShieldActive();
	bool isAlive();


private:
	int health ;
	int shield ; 

};

#endif
