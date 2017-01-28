#include "player.h"
#include <iostream>

/*
States - 
  1. PASSIVE - Default state of Player and when player is not in motion.
  2. ACTIVE - State when player is in motion
  3. DYING - State when player is has no health and is about to die.
  4. DEAD -  State when player is dead and player object is about to destroy. 

Decision making - 
  Controlled by user completely

*/

	Player::Player()
	{
		m_State = "PASSIVE";
		health = 5;
		shield = 0;
	}
	Player::~Player()
	{
	
	
	}

	void Player::Update( float deltaTime )
	{
		GameObjectBase::Update(deltaTime);

		//Check vitals
		if(health == 0)
			{
			m_State= "DYING";
			}

		if(shield < 1)
			{
				for(int i = 0 ; i < childObjects.size(); i++)
				{
				delete childObjects[i];
				}

				childObjects.clear();
			}




		if(m_State == "ACTIVE")
		{
			//When-ever player moves, End point is plotted
		
			delegator->setEndNode(this);

		}else if(m_State == "DYING")
		{
			position.y = 0.5f;

			if(rotation.z < 1.57f)
			{
				rotation.z+= 0.05f;
			}
			else
			{
				m_State = "DEAD";
		
		
			}
		}	
	
	}


	void Player::setHealth(int value)
	{
	
		health = value;
	}

	int Player::getHealth()
	{
	
		return health;
	}

	void Player::setShield(int value)
	{
	
		shield = value;
	}
	int Player::getShield()
	{
	
	
		return shield;
	}


	void Player::isBeingAttacked()
	{
		position.y += 0.5f;
		if(shield != 0)
		{
		
			shield--;
		}
		else if(health !=0)
		{
			health--;
		
		}else
		{
			//no shield or health... bro is dead meat....
			m_State = "DYING";
		
		
		}
	
		std::cout<<"Health is "<<health<<std::endl;
		std::cout<<"Shield is "<<shield<<std::endl;
	}


	void Player::gotPowerUp()
	{
		shield = 5;
	
	}

	bool Player::isShieldActive()
	{
		if(shield > 0)
		{
			return true;
		}else{
			return false;
		}
	
	}


	bool Player::isAlive()
	{
		if(m_State == "DEAD")
		{
			delegator->destoryObject(m_ID);
			return false;
		}else
		{
			return true;
		}

	}