#ifndef _GameObject_HG_
#define _GameObject_HG_

#include "gameObjectBase.h"
#include "Idelegator.h"



class GameObject : public GameObjectBase
{
public:
	GameObject();		// Default constructor 
	virtual ~GameObject();  
	
	
	 

	//sets Delegator
	void setDelegator(IDelegator* value);
	


protected:
	
	GameObject* nearestNode;


	IDelegator* delegator;

};

#endif
