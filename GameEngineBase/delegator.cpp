#include "delegator.h"
#include <sstream>

#include "player.h"
#include "enemy.h"

Delegator::Delegator()
{
	mediator = new GameMediator();
	mediator->setDelegator(this);
	movement = new MovementManager();
	file = new FileDataLoader();
	collision = new Collision();
	fmod = new Audio();
	//pathfinder = new Pathfinder();
	myPiecesIndex = 0;

	boss_alive = true;
	player_alive = true;
}

Delegator::~Delegator()
{
	for(int i= 0 ; i < sceneList.size(); i++)
		delete sceneList[i];
	
	sceneList.clear();

	for(int i= 0 ; i < nodeList.size(); i++)
		delete nodeList[i];
	
	nodeList.clear();



	delete	mediator ;
	delete movement ;
	delete file ;
	delete collision;
	delete fmod;


}
//To create entire scene
void Delegator::createScene()
{
	file->loadSceneFromFileWithSinglePlayer(mediator, sceneList, played_id, boss_id);

	//Set delegator
	for(int i= 0; i< sceneList.size(); i++)
	{
		((GameObject*)sceneList[i])->setDelegator(this);
	
	}

}

void Delegator::createSceneWithMulPlayer()
{
	file->loadSceneFromFileWithMultiPlayer(mediator, sceneList, myPieces);

}

//Fetch list of player objects
	std::vector <GLuint> Delegator::getMyPieces()
	{
	
		return myPieces;
	}


	//To create Game Objects
unsigned int Delegator::createObject(std::string ObjectType, std::string fileName , Vector3D color)
{
	unsigned int id=	mediator->createObject(ObjectType,ASCII_to_Unicode(fileName), sceneList, color);
	((GameObject*)sceneList.back())->setDelegator(this);
 return id;
}

//To create Node grid
void Delegator::createNodes()
{
	
	std::wstring fileName = L"ply/sphere.ply";
	std::string ObjectType = "Node";
	Vector3D color(1.0f,1.0f,1.0f) ;
	float maxExtent = 0.0f;
	bool bw = true;

	int i = 0;
	int j = 0;

	for(float z = -4.3; z < 5.1;)
	{
		j=0;
		for(float x = -4.4; x < 4.7;)
		{   
				
				unsigned int id =0;
			
				id =mediator->createObject(ObjectType,fileName, nodeList, color);
			//	played_id = id;
				updateNode("POSITION", Vector3D(x,0.4f,z),id);
		

			updateNode("SCALE", Vector3D(0.0f,0.0f,0.0f),id, 0.2);
		    maxExtent = 0.2;//getActualMaxExtent(id);
		
			x += 3*(maxExtent);
			////std::cout<< " j = "<<j<<std::endl; 

			
			collision->CollisionCheckForNode((GameObject*)nodeList.back(), sceneList);
			Pathfinder::nodeGrid[i][j] = (Node*)nodeList.back();

			//Check if node is movable 



			j++;
		}
	
		z+= 3*(maxExtent);
	
		i++;
	}
		//std::cout<< " i and j "<<i<<" "<<j<<std::endl; 
}



std::vector <GameObjectBase*> Delegator::getNodeList()
{

	return nodeList;
}

void Delegator::simulation(float deltaTime)
{
	for(int index =0 ; index < sceneList.size() ; index++)
	{
		movement->move(deltaTime,sceneList[index] );
	
		sceneList[index]->Update(deltaTime);
		


	}

	collision->CollisionCheckForEnemy(sceneList);

}

void Delegator::simulatePlayer(float deltaTime)
{
	for(int index =0 ; index < sceneList.size() ; index++)
	{
		movement->movePlayer(deltaTime,sceneList[index] );

		if(sceneList[index]->getName()=="Player")
		{
			collision->CollisionCheckForPlayer(sceneList, index);	
		}
	
		
	}

}
void Delegator::updateObject(std::string UpdateType, Vector3D vecAttrib,unsigned int ID, float param, std::string state)
{
	//Find that object
	GameObjectBase* obj ;
	bool IdFound = false;
	for(int i = 0 ; i < sceneList.size(); i ++)
	{
		if(sceneList[i]->getID() == ID){
			obj = sceneList[i];
			obj->setOldColor(sceneList[i]->getColour());
			IdFound = true;
		}
	}

	if(IdFound){
	if(UpdateType == "POSITION")
	{
		mediator->UpdateObjectPositionByID(vecAttrib,obj );
	}
	else if(UpdateType == "ROTATION")
	{
		mediator->UpdateObjectRotationByID(vecAttrib,obj);
	}
	else if(UpdateType == "VELOCITY")
	{
		mediator->UpdateObjectVelocityByID(vecAttrib,obj);
	
	}else if(UpdateType == "SCALE")
	{
		mediator->UpdateObjectScaleByID(param, obj);
	}else if(UpdateType == "COLOUR")
	{
		
		mediator->UpdateModelColourByID(vecAttrib, obj);
	}else if(UpdateType == "STATE")
	{
		if(state != "DEFAULT"){
		mediator->UpdateObjectStateByID(state, obj);
		}
	}else if(UpdateType == "ROTATETO")
	{
	
		mediator->UpdateObjectRotateTo(state, obj);
	}
	
	}
	
}

void Delegator::updateNode(std::string UpdateType, Vector3D vecAttrib,unsigned int ID, float param)
{
	//Find that object
	GameObjectBase* obj ;
	bool IdFound = false;
	for(int i = 0 ; i < nodeList.size(); i ++)
	{
		if(nodeList[i]->getID() == ID){
			obj = nodeList[i];
			obj->setOldColor(nodeList[i]->getColour());
			IdFound = true;
		}
	}

	if(IdFound){
	if(UpdateType == "POSITION")
	{
		mediator->UpdateObjectPositionByID(vecAttrib,obj );
	}
	else if(UpdateType == "ROTATION")
	{
		mediator->UpdateObjectRotationByID(vecAttrib,obj);
	}
	else if(UpdateType == "VELOCITY")
	{
		mediator->UpdateObjectVelocityByID(vecAttrib,obj);
	
	}else if(UpdateType == "SCALE")
	{
		mediator->UpdateObjectScaleByID(param, obj);
	}else if(UpdateType == "COLOUR")
	{
		
		mediator->UpdateModelColourByID(vecAttrib, obj);
	}
	
	}
	
}

void Delegator::resetObject(std::string UpdateType,unsigned int ID){

	//Find that object
	GameObjectBase* obj ;
	bool IdFound = false;
	for(int i = 0 ; i < sceneList.size(); i ++)
	{
		if(sceneList[i]->getID() == ID){
			obj = sceneList[i];
			IdFound = true;
		}
	}

	if(IdFound){
	if(UpdateType == "POSITION")
	{
		//mediator->UpdateObjectPositionByID(vecAttrib,obj );
	}
	else if(UpdateType == "ROTATION")
	{
		//mediator->UpdateObjectRotationByID(vecAttrib,obj);
	}
	else if(UpdateType == "VELOCITY")
	{
		//mediator->UpdateObjectVelocityByID(vecAttrib,obj);
	
	}else if(UpdateType == "SCALE")
	{
		//mediator->UpdateObjectScaleByID(param, obj);
	}else if(UpdateType == "COLOUR")
	{
		
		mediator->ResetColourByID(obj);
	}
	
	}

}


float Delegator::getActualMaxExtent(unsigned int ID)
{
	GameObjectBase* obj ;
	float maxExtent = 0.0f;
	bool IdFound = false;
	for(int i = 0 ; i < sceneList.size(); i ++)
	{
		if(sceneList[i]->getID() == ID){
			obj = sceneList[i];
			IdFound = true;
			maxExtent = obj->getMaxExtent();
			float scale = obj->getScale();
			maxExtent *= scale;
		}
	}


	return maxExtent;
}


//Fetch list of game objects created.
std::vector <GameObjectBase*> Delegator::getSceneList()
{

	return sceneList;
}


// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
// But this is "good enough" for now
std::wstring Delegator::ASCII_to_Unicode( std::string ASCIIstring )
{
	std::wstringstream ssReturnUNICODE;
	for ( std::string::iterator itChar = ASCIIstring.begin(); itChar != ASCIIstring.end(); itChar++ )
	{
		wchar_t theChar = static_cast<wchar_t>( *itChar );
		ssReturnUNICODE << theChar;
	}
	return ssReturnUNICODE.str();
}


//Fetch player id 
	GLuint Delegator::getPlayerId()
	{
		return played_id;
	
	}


	//Fetch List index
	GLuint Delegator::getMyPiecesIndex()
	{
		return myPiecesIndex;
	}

	void Delegator::setMyPiecesIndex(GLuint value)
	{
		myPiecesIndex =value;
		
	}

	//.......................For pathfinding ..........................................................................
	 std::vector<GameObjectBase*> Delegator::getShortestPath(GameObjectBase* obj)
	 {
		 GameObjectBase* startNode = getClosestNode(obj);

		 //Create object of pathfinder
		 Pathfinder* path = new Pathfinder();
		 bool reCalculate = false;

		 std::vector<GameObjectBase*> returnPath ;

		 //do
		// {
		 int endNode = 999; 
		 path->searchPath((Node*)startNode, endNode);


		 
		 if(endNode < 999){
		 returnPath = path->getPath(endNode,reCalculate);
		 }
		
		// }while (reCalculate); 


			 return returnPath;
		
		
	 }


	  void Delegator::setEndNode(GameObjectBase* obj)
	  {
		Node* node = (Node*)getClosestNode(obj);
	  
		//std::cout << node->getNodeID() << std::endl; 
		 Pathfinder::setEndNode((Node*)node);
	  }


	   GameObjectBase* Delegator::getClosestNode(GameObjectBase* obj)
	   {
			float distance = 99.0f;
			Vector3D dist;
			GameObjectBase* closestNode = new GameObjectBase();
			for(int i=0; i< nodeList.size(); i++)
			{
				if(((Node*)nodeList[i])->getIsMovable()){
				dist = obj->getPosition() - nodeList[i]->getPosition();

				if(dist.Magnitude() < distance)
				{
					distance = dist.Magnitude();
					closestNode = nodeList[i];
				}
			
				}
			}

			return closestNode;
	   }
	   //..................................................................................................................



	   //.................... Distance from Player .........................................................................


	   Vector3D Delegator::getDistanceFromPlayer(Vector3D pos)
	   {
		   //Find player pos
		   GameObjectBase* obj = new GameObjectBase();
		   bool IdFound = false;
	      for(int i = 0 ; i < sceneList.size(); i ++)
		  {
		       if(sceneList[i]->getID() == played_id){
			       obj = sceneList[i];
			       IdFound = true;
				   break;
		       }
	      }

		  

		  Vector3D playerPos = obj->getPosition();
	   
		  Vector3D distVec = playerPos - pos;

		  return distVec;
	   
	   }


	     Vector3D Delegator::getDistanceFromBoss(Vector3D pos)
	   {
		   //Find player pos
		   GameObjectBase* obj = new GameObjectBase();
		   bool IdFound = false;
	      for(int i = 0 ; i < sceneList.size(); i ++)
		  {
		       if(sceneList[i]->getID() == boss_id){
			       obj = sceneList[i];
			       IdFound = true;
				   break;
		       }
	      }

		  

		  Vector3D playerPos = obj->getPosition();
	   
		  Vector3D distVec = playerPos - pos;

		  return distVec;
	   
	   }

	     Vector3D Delegator::getPlayerPos()
			{
			  //Find player pos
		   GameObjectBase* obj = new GameObjectBase();
		   bool IdFound = false;
	      for(int i = 0 ; i < sceneList.size(); i ++)
		  {
			  if(sceneList[i]->getID() == played_id){ //played_id){
			       obj = sceneList[i];
			       IdFound = true;
				   break;
		       }
	      }

		  

		  Vector3D playerPos = obj->getPosition();

		  return playerPos;
			
			
			}


		   Vector3D Delegator::getBossPos()
			{
			  //Find player pos
		   GameObjectBase* obj = new GameObjectBase();
		   bool IdFound = false;
	      for(int i = 0 ; i < sceneList.size(); i ++)
		  {
			  if(sceneList[i]->getID() == boss_id){ //played_id){
			       obj = sceneList[i];
			       IdFound = true;
				   break;
		       }
	      }

		  

		  Vector3D playerPos = obj->getPosition();

		  return playerPos;
			
			
			}

	   void Delegator::simulatePathfinding()
	   {
		   Pathfinder::setEndNode(Pathfinder::nodeGrid[23][23]);
		   std::vector<GameObjectBase*> path = getShortestPath(Pathfinder::nodeGrid[0][0]);
	   }
	   //..................................................................................................................

	    bool Delegator::getHasEndPtchanged()
		{
		
			return hasEndPtChanged;
		}


		  void Delegator::setHasEndPtchanged(bool val)
		  {
			hasEndPtChanged =val;
		  }



		   bool Delegator::destoryObject(unsigned int objectId)
		   {
				  GameObjectBase* obj = new GameObjectBase();
				 bool IdFound = false;

				 if(objectId == boss_id)
				 {
					boss_alive = false;
				 }else if(objectId == played_id)
				 {
				 
					 player_alive = false;
				 }


				 for(int i = 0 ; i < sceneList.size(); i ++)
		         {
		             if(sceneList[i]->getID() == objectId){
			           obj = sceneList[i];
			           IdFound = true;
				       break;
		             }
	             }


				 if(IdFound)
				 {
				 	removeFromSceneList(obj);

					delete obj;
				 
				 
				 }

			return true;
		   }

		  bool Delegator::attackPlayer()
		 {
				  Player* obj = new Player();
				 bool IdFound = false;
				 for(int i = 0 ; i < sceneList.size(); i ++)
		         {
					 if(sceneList[i]->getID() == played_id){
			           obj = (Player*)sceneList[i];
			           IdFound = true;
				       break;
		             }
	           }

				 if(IdFound)
				 {
					 fmod->playSample(3);
					 obj->isBeingAttacked();
				 
				 }



			return true;
		 }


		  bool Delegator::equipPlayer(GameObjectBase* child)
		 {
				  Player* obj = new Player();
				 bool IdFound = false;
				 for(int i = 0 ; i < sceneList.size(); i ++)
		         {
					 if(sceneList[i]->getID() == played_id){
			           obj = (Player*)sceneList[i];
			           IdFound = true;
				       break;
		             }
	           }

				 if(IdFound)
				 {
					 if(!obj->isShieldActive())
					 {
					 fmod->playSample(4);
					 obj->gotPowerUp();
					 obj->attachChildObject(child);
					 }
				 }



			return true;
		 }


		  bool Delegator::getShieldStatus()
		  {

			  bool shield = false;
			  	  Player* obj = new Player();
				 bool IdFound = false;
				 for(int i = 0 ; i < sceneList.size(); i ++)
		         {
					 if(sceneList[i]->getID() == played_id){
			           obj = (Player*)sceneList[i];
			           IdFound = true;
				       break;
		             }
	           }

				 if(IdFound)
				 {
					 if(obj->isShieldActive())
					 {
						 shield = true;
					 }
				 }

				 return shield;

		  }


		  bool Delegator::isPlayerAlive()
		  {
		   bool alive = false;
			  	  Player* obj = new Player();
				 bool IdFound = false;
				 for(int i = 0 ; i < sceneList.size(); i ++)
		         {
					 if(sceneList[i]->getID() == played_id){
			           obj = (Player*)sceneList[i];
			           IdFound = true;
				       break;
		             }
	           }

				 if(IdFound)
				 {
					 if(obj->isAlive())
					 {
						 alive = true;
					 }
				 }

				 return alive;


		  
		  }


	bool Delegator::initAudio()
	{
		file->loadSoundsForFMOD(fmod);
		fmod->initFMOD();
		std::cout<<"Audios initialized "<<std::endl;
		//
		fmod->switchStream(0);
	
	
	return true;
	}

	bool Delegator::switchSound(int index)
	{
		fmod->switchStream(index);
	
	return true;
	}

	bool Delegator::playSample(int index)
	{
		fmod->playSample(index);
	
	return true;
	
	}

	bool Delegator::stopSound(int index)
	{
		fmod->pauseStream(index);
	
	return true;
	}


	GLuint Delegator::getBossId()
	{
	
		return boss_id;
	}

	bool Delegator::isBossAlive()
	{
		return boss_alive;
	
	}

	bool Delegator::isMinionsAround(GLuint bossId)
	{
		int minionCount = 0 ;
		
		for(int i= 0 ; i < sceneList.size() ; i++)
		{
			if(((Enemy*)sceneList[i])->getBossId() == bossId)
			{
				Vector3D distFromboss = this->getDistanceFromBoss(sceneList[i]->getPosition());
				if(distFromboss.Magnitude() < 2.0f)
				{
				 minionCount++;
				}
			}
		
		}

		return (minionCount > 0);
	}

	void Delegator::removeFromSceneList(GameObjectBase* obj)
	{
	std::vector<GameObjectBase*>::iterator position = std::find(sceneList.begin(), sceneList.end(), obj);
									if (position != sceneList.end()) // == vector.end() means the element was not found
											sceneList.erase(position);
	
	
	}


	void Delegator::enemiesFlee(float deltaTime)
	{
		for(int i = 0 ; i < sceneList.size(); i++)
		{
			if(sceneList[i]->getName() == "Enemy")
			{
				Vector3D vel = sceneList[i]->getVelocity();
				sceneList[i]->setVelocity(Vector3D(vel.x, vel.y + 0.5f, vel.z));

				movement->move(deltaTime,sceneList[i] );
			}
		
		}

	}