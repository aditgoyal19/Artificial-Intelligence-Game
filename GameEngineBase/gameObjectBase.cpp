#include "gameObjectBase.h"


static const unsigned int FIRSTGAMEOBJECTID = 1000;
unsigned int GameObjectBase::m_nextID = FIRSTGAMEOBJECTID;


// Called by the constructors
void GameObjectBase::m_Init(void)
{
	// Assign ID here
	this->m_ID = this->m_nextID;   
	this->m_nextID++;	// Increment

	this->scale = 1.0f;

	this->name = "no name";
	this->plyFileName = "";
	this->prevRotateTo = "";
	this->rotateTo = "";
	this->specularShininess = 1.0f;		// "Meh" shiny
	this->specularStrength = 1.0f;		// Not shiny

	return;
}



GameObjectBase::GameObjectBase()
{
	this->m_Init();

//	this->m_pMediator = 0;	

	return;
}
GameObjectBase::~GameObjectBase()
{


}


void GameObjectBase::Update( float deltaTime )
{
	//If it has child objects update them also
	for(int i = 0 ; i < childObjects.size(); i++)
	{
		childObjects[i]->Update(deltaTime);
	
	}


	// Code to handle to handle rotation

	if(prevRotateTo == "" || prevRotateTo == "LEFT")
	{
		
		if(rotateTo == "LEFT")
		{
			//already facing left
		}
		else if(rotateTo == "RIGHT")
		{
			if(rotation.y < (totalRot.y + 3.14f))
			{
				rotation.y += 0.2f;
			}
		
		}
		else if(rotateTo == "UP")
		{
			if(rotation.y > (totalRot.y -1.57f))
			{
				rotation.y -= 0.2f;
			}
		
		
		}else if(rotateTo == "DOWN")
		{
			if(rotation.y < (totalRot.y + 1.57f))
			{
				rotation.y += 0.2f;
			}
		
		}
	
	
	}
	else if(prevRotateTo == "RIGHT")
	{
		if(rotateTo == "LEFT")
		{
			if(rotation.y < (totalRot.y + 3.14f))
			{
				rotation.y += 0.2f;
			}
		}
		else if(rotateTo == "RIGHT")
		{
			//Nothing
		
		}
		else if(rotateTo == "UP")
		{
			if(rotation.y < (totalRot.y + 1.57f))
			{
				rotation.y += 0.2f;
			}
		
		
		}else if(rotateTo == "DOWN")
		{
			if(rotation.y > (totalRot.y -1.57f))
			{
				rotation.y -= 0.2f;
			}
		
		}
	
	
	
	}else if(prevRotateTo == "UP")
	{
		if(rotateTo == "LEFT")
		{
			if(rotation.y < (totalRot.y + 1.57f))
			{
				rotation.y += 0.2f;
			}

		
		}
		else if(rotateTo == "RIGHT")
		{
			if(rotation.y > (totalRot.y -1.57f))
			{
				rotation.y -= 0.2f;
			}
		
		
		}
		else if(rotateTo == "UP")
		{
			//Nothing
		
		
		}else if(rotateTo == "DOWN")
		{
		
			if(rotation.y < (totalRot.y + 3.14f))
			{
				rotation.y += 0.2f;
			}
		}
	
	
	
	
	
	
	
	}else if(prevRotateTo == "DOWN")
	{
		if(rotateTo == "LEFT")
		{
			

		if(rotation.y > (totalRot.y -1.57f))
			{
				rotation.y -= 0.2f;
			}
		
		}
		else if(rotateTo == "RIGHT")
		{
			if(rotation.y < (totalRot.y + 1.57f))
			{
				rotation.y += 0.2f;
			}
		
		}
		else if(rotateTo == "UP")
		{
			
		if(rotation.y < (totalRot.y + 3.14f))
			{
				rotation.y += 0.2f;
			}
		
		}else if(rotateTo == "DOWN")
		{
		//Nothing
			
		}
	
	}


	return;
}

unsigned int GameObjectBase::getID(void)
{
	return this->m_ID;
}

float GameObjectBase::getMaxExtent()
{
	return data->getMaxExtent();

}

std::vector<PLYVERTEX> GameObjectBase::getVerticiesForSimulation()
{

	std::vector<PLYVERTEX> vertices = this->data->getVerticies();
	std::vector<PLYVERTEX>::iterator itVertex = vertices.begin();
	for ( ; itVertex != vertices.end(); itVertex++ )
	{
		itVertex->pos *= scale;
		itVertex->pos += this->position;
		
	}
	//this->calcualteExtents();
	return vertices;
}

void GameObjectBase::setModelData(ModelData* value)
{
	data = value;

}

 GLuint GameObjectBase::getVertexBufferId()
 {
	 return data->getVertexBufferID();
 }
	
 GLuint GameObjectBase::getVertexAttribId()
{
	 
		 return data->getVertexAttribID();
}
	 
 GLuint GameObjectBase::getIndexBufferId()
{
	 
		 return data->getIndexID();
}

 std::vector<PLYVERTEX> GameObjectBase::getVerticies()
{
	  
		  return data->getVerticies();
}
	
 std::vector<PLYELEMENT> GameObjectBase::getElements()
{
	
		return data->getElements();
}

int GameObjectBase::GetNumberOfElements()
{
	
		return data->GetNumberOfElements();
}

Vector3D GameObjectBase::getPosition()
{

	return position;
}

Vector3D GameObjectBase::getRotation()
{

	return rotation;
}
Vector3D GameObjectBase::getVelocity()
{

	return velocity;
}
Vector3D GameObjectBase::getAcceleration()
{


	return acceleration;
}
float GameObjectBase::getScale()
{

	return scale;
}

std::string GameObjectBase::getName()
{
	
		return name;
}
	std::wstring GameObjectBase::getPlyFileName()
	{
	
		return data->getFileName();
	}
	
	Vector3D GameObjectBase::getColour()
	{
	
		return colour;
	}

	// Specular component (Shininess)
	float GameObjectBase::getSpecularShininess()
	{
	
		return specularShininess;
	}
	float GameObjectBase::getSpecularStrength()
	{
	
		return specularStrength;
	}


	void GameObjectBase::setPosition(Vector3D value)
	{
		position = value;
	}
	void GameObjectBase::setRotation(Vector3D value)
	{
	
		rotation = value;
	}
	void GameObjectBase::setVelocity(Vector3D value)
	{
	
		velocity = value;
	}
	void GameObjectBase::setAcceleration(Vector3D value)
	{
	
		acceleration = value;
	}
	void GameObjectBase::setScale(float value)
	{
	
		scale = value;
	}

	void GameObjectBase::setName(std::string value)
	{
	
		name = value;
	}
	
	void GameObjectBase::setPlyFileName(std::string value)
	{
	
		plyFileName = value;
	}
	// ADDED on September 29th, 2014
	void GameObjectBase::setColour(Vector3D value)
	{
	
		colour = value;
	}

	// Specular component (Shininess)
	void GameObjectBase::setSpecularShininess(float value)
	{
	
		specularShininess = value;
	}
	void GameObjectBase::setSpecularStrength(float value)
	{
	
	
		specularStrength = value;
	}


	   //Set old color 
   void GameObjectBase::setOldColor(Vector3D value)
   {
   
	   oldColor = value;
   }

   //Get old Color
   Vector3D GameObjectBase::getOldColor()
   {
   
	   return oldColor;
   }


   std::string GameObjectBase::getState()
   {
   
	   return m_State;
   }


	void GameObjectBase::setState(std::string value)
	{
	
		m_State = value;
	
	}

	void GameObjectBase::setRotateTo(std::string value)
	{
		prevRotateTo = rotateTo;
		totalRot = rotation;
		rotateTo = value;
	}


	//Added for matrix stack
	bool GameObjectBase::hasChildObjects()
	{
		if(childObjects.size() > 0)
			return true;
		else
			return false;
	}


	void GameObjectBase::attachChildObject(GameObjectBase* obj)
	{
		childObjects.push_back(obj);
	
	}


	std::vector<GameObjectBase*> GameObjectBase::getChildObjects()
	{
	
		return childObjects;
	
	}