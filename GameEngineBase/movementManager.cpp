#include "movementManager.h"

MovementManager::MovementManager()
{


}
MovementManager::~MovementManager()
{

}

void MovementManager::move(float deltaTime, GameObjectBase* &obj)
{
	//using Euler's forward integration , we calculate position based on velocity
	
	Vector3D newPos = obj->getPosition() + obj->getVelocity() * deltaTime;
	obj->setPosition(newPos);

	

}

void MovementManager::movePlayer(float deltaTime, GameObjectBase* &obj)
{
	//If object is sphere apply gravity
	if(obj->getName() == "Player")
	{
		Vector3D newPos = obj->getPosition();
		newPos.y -= 0.5f * deltaTime;
		obj->setPosition(newPos);
	
	}

}