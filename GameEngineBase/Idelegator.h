#ifndef _IDEL_H
#define _IDEL_H

#include "gameObjectBase.h"
#include <vector>

class IDelegator
{
public:
	~IDelegator(){};
	virtual std::vector<GameObjectBase*> getShortestPath(GameObjectBase* obj) =0;
	virtual void setEndNode(GameObjectBase* obj) = 0;
	virtual Vector3D getDistanceFromPlayer(Vector3D pos) = 0;
	virtual Vector3D getDistanceFromBoss(Vector3D pos) = 0;
	virtual  bool getHasEndPtchanged() = 0;
	virtual bool destoryObject(unsigned int playerid)= 0;
	virtual bool attackPlayer() = 0 ;
	virtual bool equipPlayer(GameObjectBase* obj) = 0;
	virtual bool getShieldStatus() =0;
	virtual  Vector3D getPlayerPos() = 0;
	virtual  Vector3D getBossPos() = 0;
	virtual bool isBossAlive() = 0;
	virtual bool isPlayerAlive() = 0;
	virtual bool isMinionsAround(GLuint bossId) = 0;

	//Fetch player id 
	virtual GLuint getPlayerId() = 0;

	//Fetch Boss id
	virtual GLuint getBossId() = 0;

	//Added for matrix stack
	virtual void removeFromSceneList(GameObjectBase* obj) =0;
};

#endif