#ifndef _COLLIDE_H
#define _COLLIDE_H


#include "Physics.h"
#include "gameObject.h"
#include <vector>


class Collision
{
public:
	Collision();
	~Collision();


void CollisionCheckForSphere(std::vector< GameObjectBase* > vec_pGameObjects, int playerIndex);

// Called to check Sphere collisions
void SphereToEnvCollision(GameObject* sphere , GameObject* envObj, std::vector<Physics::Point> &listOfClosestPt);
void SphereToSphereCollision(GameObject* sphere1 , GameObject* sphere2, std::vector<Physics::Point> &listOfClosestPt);
//.......................

//Called to check if node is movable or not
void CollisionCheckForNode(GameObject* node, std::vector< GameObjectBase* > vec_pGameObjects);
void NodeToEnvCollision(GameObject* node , GameObject* envObj);
void NodeToSphereCollision(GameObject* node , GameObject* sphere2);

//.......................
//Collisions of Player
void CollisionCheckForPlayer(std::vector< GameObjectBase* > vec_pGameObjects, int playerIndex);

//...................................
//Collisions of Enemy 
void CollisionCheckForEnemy(std::vector< GameObjectBase* > vec_pGameObjects);
void EnemyToEnemyCollision(GameObject* sphere1 , GameObject* sphere2, std::vector<Physics::Point> &listOfClosestPt);


};


#endif