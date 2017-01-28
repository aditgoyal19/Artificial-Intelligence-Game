#ifndef _GAME_BASE_H
#define _GAME_BASE_H


#include <vector>
#include <string>
#include "Vector3D.h"
#include "modelData.h"

class GameObjectBase
{
public:
	GameObjectBase();
	~GameObjectBase();
	// Only called by the IFactory object
	//void setDelegator( IMediator* pMediator );

	virtual void Update( float deltaTime );

	// Used by the Mediator to send messages
//	virtual void receiveMessage( CMessage theMessage, unsigned int senderID );

	unsigned int getID(void);

	// std::vector<PLYVERTEX> scaleVertices( float scaleFactor );
	 void setModelData(ModelData* value);
	
	 float getMaxExtent();
	 GLuint getVertexBufferId();
	 GLuint getVertexAttribId();
	 GLuint getIndexBufferId();
	 int GetNumberOfElements();
	  std::vector<PLYVERTEX> getVerticies();
	std::vector<PLYELEMENT> getElements();
	 std::vector<PLYVERTEX> getVerticiesForSimulation();


	Vector3D getPosition();
	Vector3D getRotation();
	Vector3D getVelocity();
	Vector3D getAcceleration(); 
	float getScale(); 

	std::string getName();			// A helpful name
	std::wstring getPlyFileName();	// for rendering
	// ADDED on September 29th, 2014
	Vector3D getColour();				// We'll eventually use "material" instead of this (Material is more complex)
	
	  //Set old color 
   void setOldColor(Vector3D value);

   //Get old Color
   Vector3D getOldColor();

	// Specular component (Shininess)
	float getSpecularShininess();		// May way to make this a Vector3D, later (but need to update shader)
	float getSpecularStrength();


	void setPosition(Vector3D value);
	void setRotation(Vector3D value);
	void setRotateTo(std::string value);
	void setVelocity(Vector3D value);
	void setAcceleration(Vector3D value); 
	void setScale(float value); 

	void setName(std::string value);			// A helpful name
	void setPlyFileName(std::string value);	// for rendering
	void setColour(Vector3D value);				// We'll eventually use "material" instead of this (Material is more complex)

	// Specular component (Shininess)
	void setSpecularShininess(float value);		// May way to make this a Vector3D, later (but need to update shader)
	void setSpecularStrength(float value);

	void m_Init(void);	// Called by the constructor. Set's everything to default state

	std::string getState();
	void setState(std::string);


	//Added for Matrix stack
	bool hasChildObjects();

	void attachChildObject(GameObjectBase* obj);

	std::vector<GameObjectBase*> getChildObjects();

protected:
	// Used to figure out what "state" the object is in
	std::string m_State;
	float extent; 
	unsigned int m_ID;	// Unique ID value
	// This will "pick" the "next" ID when object is created
	static unsigned int m_nextID;
	  ModelData* data;
	 

	  Vector3D position;
	Vector3D rotation;
	std::string rotateTo;
	std::string prevRotateTo;
	Vector3D totalRot ;
	Vector3D velocity;
	Vector3D acceleration; 
	float scale; 

	std::string name;			// A helpful name
	std::string plyFileName;	// for rendering
	// ADDED on September 29th, 2014
	Vector3D colour;				// We'll eventually use "material" instead of this (Material is more complex)
	Vector3D oldColor;
	// Specular component (Shininess)
	float specularShininess;		// May way to make this a Vector3D, later (but need to update shader)
	float specularStrength;

	//Added for Matrix stack 
	std::vector<GameObjectBase*> childObjects;

};


#endif