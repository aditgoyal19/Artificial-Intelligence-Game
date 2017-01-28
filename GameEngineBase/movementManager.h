#ifndef _MOV_MNGR_CH
#define _MOV_MNGR_CH

#include "gameObject.h"


class MovementManager
{
public:
	MovementManager();
	~MovementManager();

	void move(float deltaTime, GameObjectBase* &obj);
	void movePlayer(float deltaTime, GameObjectBase* &obj);
private:

};

#endif