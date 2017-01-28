#include "mediator.h"

#include "sphere.h"
#include "terrain.h"
#include "node.h"
#include "player.h"
#include "enemy.h"
#include "powerup.h"
#include "Vector3D.h"

#include <iostream>

	GameMediator::GameMediator()
	{
	
	 return;
	}

	GameMediator::~GameMediator()
	{
	
	
	return;
	}

	unsigned int GameMediator::createObject(std::string ObjectType,std::wstring fileName, std::vector <GameObjectBase*> &objectList, Vector3D color)
	{
		GameObjectBase* newObject ;
		unsigned int id ;
		bool isNew = true;
		//Check type of object
		if(ObjectType == "Sphere")
		{
			newObject = new Sphere();
			newObject->setName(ObjectType);
		}
		else if(ObjectType == "Enemy")
		{
			newObject = new Enemy();
			newObject->setName(ObjectType);

		
		}
		else if(ObjectType == "Boss")
		{
			newObject = new Enemy();
			newObject->setName("Enemy");
			((Enemy*)newObject)->setIsBoss();     

		
		}
		else if(ObjectType == "Minion")
		{
			newObject = new Enemy();
			newObject->setName("Enemy");
			((Enemy*)newObject)->setBossId(delegator->getBossId());  

		
		}
		else if(ObjectType == "Player")
		{
			newObject = new Player();
			newObject->setName(ObjectType);

		
		}
		else if(ObjectType == "Node")
		{
			newObject = new Node();
			newObject->setName(ObjectType);

		
		}
		else if(ObjectType == "PowerUp")
		{
			newObject = new PowerUp();
			newObject->setName(ObjectType);

		
		}
		else if(ObjectType == "Terrain")
		{
			newObject = new Terrain();
			newObject->setName(ObjectType);

		
		}
		else
		{
			newObject = new GameObject();
			newObject->setName(ObjectType);
		}
			//Object created now check if the model exists... (use filename and scale to compare)
			for(int i = 0 ; i < modelList.size(); i++)
			{
				if(modelList[i]->getFileName() == fileName ){
				//cool so that file is already added . lets check if color is same
					
					if(modelList[i]->getColor() == color)
					{
						newObject->setModelData(modelList[i]);
						isNew = false;
						break;
					}else
					{
						//Model is same but color is different
						ModelData* data =  new ModelData();
						data->setNumberOfElements(modelList[i]->GetNumberOfElements());
						data->setNumberOfVerticies(modelList[i]->GetNumberOfVerticies());
					
						data->setVerticies(modelList[i]->getVerticies());
						data->setElements(modelList[i]->getElements());
						data->calcualteExtents();
						data->setColor(color);
						data->setFileName(fileName);
						data->assignBuffer();

						newObject->setModelData(data);
						modelList.push_back(data);
						isNew = false;
						break;
					
					}


				
				}
			}
				if(isNew)
				{
				//Create new modelData
					ModelData* data = new ModelData();
					std::wstring error;
					if(data->OpenPLYFile(fileName,error))
					{
						data->setColor(color);
						data->assignBuffer();
						data->setFileName(fileName);
					}
					
					newObject->setModelData(data);
				
					modelList.push_back(data);
				}

			
				id = newObject->getID();
				objectList.push_back(newObject);
		
		return id;
		}

	bool GameMediator::UpdateObjectColourByID(  Vector3D newColour ,  GameObjectBase* &object )
{

	object->setColour(newColour);
	
	

	return true;
}

bool GameMediator::UpdateModelColourByID(  Vector3D newColour ,  GameObjectBase* &object )
{

	object->setColour(newColour);
	
	for(int i = 0 ; i < modelList.size(); i++)
			{
				if(modelList[i]->getFileName() == object->getPlyFileName() ){
				//cool so that file is already added . lets check if color is same
					
					if(modelList[i]->getColor() == newColour)
					{
						//Model with new colour found , so attach it
						object->setModelData(modelList[i]);
						break;
					}else
					{
						//Unable to find this colour ...so create copy of existing model with this color
						ModelData* data =  new ModelData();
						data->setNumberOfElements(modelList[i]->GetNumberOfElements());
						data->setNumberOfVerticies(modelList[i]->GetNumberOfVerticies());
					
						data->setVerticies(modelList[i]->getVerticies());
						data->setElements(modelList[i]->getElements());
						data->calcualteExtents();
						data->setColor(newColour);
						data->setFileName(object->getPlyFileName());
						data->assignBuffer();

						object->setModelData(data);
						modelList.push_back(data);
						break;
					}


				
				}
			}

	return true;
}

bool GameMediator::ResetColourByID( GameObjectBase* &object)
{
	UpdateModelColourByID( object->getOldColor() ,  object );

return true;
}

	
	bool GameMediator::UpdateObjectPositionByID( Vector3D newPosition , GameObjectBase* &object)
{
	
	
	object->setPosition(newPosition);
	return true;
}

bool GameMediator::UpdateObjectRotationByID(  Vector3D newRotation , GameObjectBase* &object )
{
	
	// Found it
	object->setRotation(newRotation);
	return true;
}

bool GameMediator::UpdateObjectRotateTo(std::string value,  GameObjectBase* &object )
{

	object->setRotateTo(value);
	return true;

}

bool GameMediator::UpdateObjectStateByID( std::string newState,  GameObjectBase* &object)
{
	object->setState(newState);

	return true;
}


bool GameMediator::UpdateObjectScaleByID( float newScale , GameObjectBase* &object )
{
	
	// Found it

	float extent = object->getMaxExtent();
	object->setScale(newScale/extent);
	//pTheGO->scaleVertices(newScale);
	return true;
}

bool GameMediator::UpdateObjectRadiusByID( float newRadius , GameObjectBase* &object)
{
	
	((Sphere*)object)->setRadius(newRadius);
	return true;
}

bool GameMediator::UpdateObjectVelocityByID( Vector3D newVelocity , GameObjectBase* &object)
{

	// Found it
	object->setVelocity(newVelocity);
	return true;
}
	

void GameMediator::setDelegator(IDelegator* value)
{
		
	delegator = value;

}	
		
	
