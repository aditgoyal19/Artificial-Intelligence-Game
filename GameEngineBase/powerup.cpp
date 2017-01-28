#include "powerup.h"

PowerUp::PowerUp()
{
	m_State = "IDLE";

}
PowerUp::~PowerUp()
{


}


void PowerUp::Update( float deltaTime )
{
	


	if(m_State != "EQUIPED")
		{
				//Attach shield to Player
			Vector3D distanceFromPlayer = delegator->getDistanceFromPlayer(this->getPosition());
			float dist = distanceFromPlayer.Magnitude();
		
			if(dist < 0.4f)
			{
					m_State = "EQUIPED";
					scale = 0.004f;
					position = Vector3D(0.0f, 0.03f, 0.0f);
	     			delegator->equipPlayer(this);
					delegator->removeFromSceneList(this);

	
		
			}
		

		}else
		{
		rotation.y += 0.1f;
		
		}


}