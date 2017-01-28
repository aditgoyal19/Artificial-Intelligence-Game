#include "enemy.h"

/*
States - 
  1.IDLE - Default state of Enemy.
  2.FOLLOW - In this state , enemy uses pathfinding to reach player.
  3.ATTACK - In this state , enemy selfdistructs and damages player.

Decision making - 
  1 . Find path only when player is within 2 units (state changes from IDLE to FOLLOW)
  2 . Pounce on player to attack him if its too close (0.8f) 

*/


	Enemy::Enemy()
	{
		m_State = "IDLE";
		isBoss = false;
		bossId = 0;
		Yoffset = 0.4f;
	}
	Enemy::~Enemy()
	{
	
	
	}

	void Enemy::Update( float deltaTime )
	{
		
		GameObjectBase::Update(deltaTime);

		Vector3D distanceFromPlayer = delegator->getDistanceFromPlayer(this->getPosition());
		float distPlayer = distanceFromPlayer.Magnitude();

		Vector3D distanceFromBoss = delegator->getDistanceFromBoss(this->getPosition());
		float distBoss = distanceFromBoss.Magnitude();

		if(distPlayer < 0.8f)
		{
			if((isBoss && !delegator->isMinionsAround(m_ID)) || (!isBoss))
			{
				
				m_State = "ATTACK";
			

			}
				
			

		}
		// Fuzzy logic 1
		if (isBoss && (distPlayer < 1.28f))
		{
			if ((!delegator->isMinionsAround(m_ID)))
			{

				m_State = "ATTACK";


			}

		}
		if(m_State == "IDLE")
		{
			
			if(isBoss)
			{
				if(distPlayer < 5.0f)  //player is just 5.0 units away ... boss can sense him
			    {
					nodes = delegator->getShortestPath(this);
					nodeIndex = 0;

					if(nodes.size() > 1){
						m_State = "FOLLOW";
					}
				}
			
			
			
			}else{

				if(distBoss < 2.0f && (bossId != 0))  //player is just 2.0 units away ... enemy can sense him
			    {
			
						m_State = "FOLLOWBOSS";
					
				}



				if(distPlayer < 2.0f)  //player is just 2.0 units away ... enemy can sense him
			    {
				nodes = delegator->getShortestPath(this);
				nodeIndex = 0;

					if(nodes.size() > 1){
						m_State = "FOLLOW";
					}
				}	
		
			}
		
		
		}

		if(m_State == "FOLLOW")
		{
			/*if(delegator->getHasEndPtchanged())
			{
				nodes = delegator->getShortestPath(this);
				nodeIndex = 0;
			
			}*/
			//Fuzzy logic 2 
			if(isBoss && delegator->isMinionsAround(m_ID) && (distPlayer < 2.0f))
			{
				Yoffset = 1.0f;
				m_State = "IDLE";
			
			}
			else if (isBoss && !delegator->isMinionsAround(m_ID) && (distPlayer > 2.0f))
			{
			
			    Yoffset = 0.4f;
				m_State = "IDLE";
			}

			Vector3D nodePos(nodes[nodeIndex]->getPosition().x,Yoffset,nodes[nodeIndex]->getPosition().z) ;
			Vector3D distance = nodePos - position;
			
			velocity = distance * 5.0f;




			float dist = distance.Magnitude();

			if(dist < 0.05f)
			{
				nodeIndex++;
				age++;
			}

			if(nodeIndex == nodes.size())
			{
			//You have reached enemy node
				velocity = Vector3D();

				
				
					m_State = "IDLE";
				
			
			}
		
		
		}

		if(m_State == "FOLLOWBOSS")
		{
			
			if(delegator->isBossAlive()){

				if(distPlayer < 2.0f)  //player is just 2.0 units away ... enemy can sense him
			    {
				nodes = delegator->getShortestPath(this);
				nodeIndex = 0;

					if(nodes.size() > 1){
						m_State = "FOLLOW";
					}
				}


			Vector3D bossPos = delegator->getBossPos();
			Vector3D distance = bossPos - position;
			
			velocity = distance * 1.0f;




			float dist = distance.Magnitude();

			if(dist < 1.0f)
			{
					velocity = Vector3D();
					m_State = "IDLE";
			}
			}
			else
			{
					m_State = "IDLE";
			}
		
		}


		if(m_State == "ATTACK")
		{
			if(distPlayer < 0.6f){
			delegator->attackPlayer();
			delegator->destoryObject(m_ID);
			}
			else
			{
				m_State = "IDLE";
			}
		}
		
	
	}


	void Enemy::setIsBoss()
	{
		isBoss = true;
	
	
	}

	void Enemy::setBossId(int value)
	{
	
		bossId = value;
	}

	int Enemy::getBossId()
	{
	
		return bossId;
	
	}