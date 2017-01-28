#ifndef _C_Game_OBJ_CH
#define _C_Game_OBJ_CH

/*
GameMediator - everything related to creation and updating values of objects

*/

#include "gameObject.h"
#include "Idelegator.h"
#include <vector>
#include <string>

class GameMediator
{
public:
	GameMediator();
	~GameMediator();

	unsigned int createObject(std::string ObjectType,std::wstring fileName, std::vector <GameObjectBase*> &objectList, Vector3D color = Vector3D(0.0f,0.0f,0.0f));


	virtual bool UpdateObjectPositionByID( Vector3D newPosition ,  GameObjectBase* &object);
	virtual bool UpdateObjectStateByID( std::string newState,  GameObjectBase* &object);
	virtual bool UpdateObjectRadiusByID( float radius  ,  GameObjectBase* &object);
	virtual bool UpdateObjectScaleByID( float newScale ,  GameObjectBase* &object);
	virtual bool UpdateObjectVelocityByID(  Vector3D newVelocity ,   GameObjectBase* &object);
	virtual bool UpdateObjectRotationByID(  Vector3D newRotation ,  GameObjectBase* &object );
	virtual bool UpdateObjectColourByID(  Vector3D newColour ,  GameObjectBase* &object );
	virtual bool UpdateModelColourByID(  Vector3D newColour ,  GameObjectBase* &object );
	virtual bool UpdateObjectRotateTo(std::string value,  GameObjectBase* &object );
	virtual bool ResetColourByID( GameObjectBase* &object);

		//sets Delegator
	void setDelegator(IDelegator* value);
	


private:
	std::vector <ModelData*> modelList;
	IDelegator* delegator;
	//unsigned int ID;
};

#endif