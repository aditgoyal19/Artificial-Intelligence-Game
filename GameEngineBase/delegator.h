#ifndef _DELEGATOR_CH
#define _DELEGATOR_CH

#include "gameObject.h"
#include "audioManager.h"
#include "fileDataLoader.h"
#include "mediator.h"
#include "movementManager.h"
#include "pathfinder.h"
#include "collisionTest.h"
#include "Idelegator.h"
#include <vector>
#include <string>


class Delegator : public IDelegator
{
public:
	Delegator();
	~Delegator();

	//To create Nodes for AI
	void createNodes();

	//To create scene from external file for single player 
	void createScene();

	//Create  Scene for multiple players (here )
	void createSceneWithMulPlayer();


	//To create Game Object and return its ID
	unsigned int createObject(std::string ObjectType,std::string fileName, Vector3D color = Vector3D(0.0f,0.0f,0.0f));


	//To update something in object (use vecAttrib to update vector and param to update float)
	void updateObject(std::string UpdateType, Vector3D vecAttrib,unsigned int ID, float param = 1.0f, std::string value = "DEFAULT");

	//update node info
	void updateNode(std::string UpdateType, Vector3D vecAttrib,unsigned int ID, float param = 1.0f);

	//Reset orignal values
	void resetObject(std::string UpdateType,unsigned int ID);

	//To fetch max extent (for model boundary based calculations)
	float getActualMaxExtent(unsigned int ID);

	std::wstring ASCII_to_Unicode( std::string ASCIIstring );

	//Fetch list of game objects created.
	std::vector <GameObjectBase*> getSceneList();

		//Fetch list of nodes created.
	std::vector <GameObjectBase*> getNodeList();

	//Update position, orientation , Object specific changes over deltaTime
	void simulation(float deltaTime);
	void simulatePlayer(float deltaTime);

	//Fetch player id 
	GLuint getPlayerId();

	//Fetch Boss id
	GLuint getBossId();

	//Fetch list of player objects
	std::vector <GLuint> getMyPieces();

	//Fetch List index
	GLuint getMyPiecesIndex();

	void setMyPiecesIndex(GLuint value);


	//For Pathfiding.....................................................
	 std::vector<GameObjectBase*> getShortestPath(GameObjectBase* obj) ;
	 void setEndNode(GameObjectBase* obj); 
	 GameObjectBase* getClosestNode(GameObjectBase* obj);
	 Vector3D getDistanceFromPlayer(Vector3D pos);
	  Vector3D getDistanceFromBoss(Vector3D pos);
	  Vector3D getPlayerPos();
	   Vector3D getBossPos();
	 void simulatePathfinding();
	 bool getHasEndPtchanged();
	  void setHasEndPtchanged(bool);

	   bool destoryObject(unsigned int playerid);
	   bool attackPlayer();
	    bool equipPlayer(GameObjectBase* obj);
		bool getShieldStatus();
		//.......For audio
		bool initAudio();
		bool switchSound(int index);
		bool stopSound(int index);
		bool playSample(int index);


		//.....For Steering behaviour
		bool isBossAlive();
		bool isPlayerAlive();
		bool isMinionsAround(GLuint bossId);


		//For animation (Hierarchical Matrix stack)
        void removeFromSceneList(GameObjectBase* obj);

		//Just for fun
		void enemiesFlee(float deltaTime);
private:
	std::vector <GameObjectBase*> sceneList;
	std::vector <GameObjectBase*> nodeList;
	std::vector <GLuint> myPieces; 
	GLuint myPiecesIndex ;
	GLuint played_id;
	GLuint boss_id;
	bool boss_alive;
	bool player_alive;
	//static int gameObjCount = 0;
	FileDataLoader* file;
	GameMediator* mediator ;
	MovementManager* movement;
	Collision* collision;
	Pathfinder* pathfinder;
	Audio* fmod;
	bool hasEndPtChanged;
};

#endif