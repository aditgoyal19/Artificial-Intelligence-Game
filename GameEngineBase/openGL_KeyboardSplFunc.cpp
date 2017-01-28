#include "global.h"
#include "master.h"


void keyboardPressCallback(unsigned char key, int x, int y)
{
	//Get id of player
	unsigned int playerId = boss->getPlayerId();
	boss->setHasEndPtchanged(true);
	switch( key )
	{
	case ' ':		// Space
		{
			//boss->updateObject("VELOCITY", Vector3D(0.0f, 0.0f, 0.0f),playerId);
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "StopMoving" ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;

	case 'p': case 'P':
		// View from above "birds eye view"
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 0.0f, 15.0f, 0.1f ); // NOOOOOOOO!

		break;

	case 'o': case 'O':
		// Follow the play-ah.
	//	::g_pCamera->Follow( ::g_Player_ID, 0.25f, 2.5f, 2.0f );
		break;	

	case 'w': case 'W':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 0.0f, 2.0f, 5.1f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 'b': case 'B':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 0.0f, 2.0f, -5.1f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 'l': case 'L':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 5.0f, 2.0f, 0.0f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 'r': case 'R':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( -5.0f, 2.0f, 0.0f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 's': case 'S':
		//::g_pCamera->eye.x += 0.1f;		// Right (+ve x)
		//::g_ourObjects[2].y -= 0.1f;	// Down
		//::g_ourObjects[2].velY -= 0.01f;	// Down
		//g_ourObjects[2].m_State = "GOING_DOWN";
		break;
	case 'a': case 'A':
		//::g_pCamera->eye.z -= 0.1f;		// Forward (-ve z)
		//::g_ourObjects[2].x -= 0.1f;	// Left
		//::g_ourObjects[2].velX -= 0.01f;	// Left
		//g_ourObjects[2].m_State = "GOING_LEFT";
		break;
	case 'd': case 'D':
		//::g_pCamera->eye.z += 0.1f;		// Back (-ve z)
		//::g_ourObjects[2].x += 0.1f;	// Right
		//::g_ourObjects[2].velX += 0.01f;	// Right
		//g_ourObjects[2].m_State = "GOING_RIGHT";
		break;

	case '+':
	//	::g_ShaderUniformVariables.Lights[0].constantAttenuation += 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].linearAttenuation += 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].quadraticAttenuation += 0.01f ; 
		break;

	case '-':
	//	::g_ShaderUniformVariables.Lights[0].constantAttenuation -= 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].linearAttenuation -= 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].quadraticAttenuation -= 0.01f ; 
		break;

	case 'i':
	//	::g_ShaderUniformVariables.Lights[0].position += glm::vec3(0.0f, 0.1f, 0.0f);	
		break;
	case 'k':
	//	::g_ShaderUniformVariables.Lights[0].position -= glm::vec3(0.0f, 0.1f, 0.0f);	
		break;

	case 'j':
	//	::g_ShaderUniformVariables.Lights[0].position -= glm::vec3(0.1f, 0.0f, 0.0f);	
		break;
	
	};

	return;
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
	//Get id of player
	Vector3D v=  boss->getPlayerPos();
	unsigned int playerId = boss->getBossId();
	boss->setHasEndPtchanged(false);
	switch( key )
	{
	case ' ':		// Space
		{
			//boss->updateObject("VELOCITY", Vector3D(0.0f, 0.0f, 0.0f),playerId);
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "StopMoving" ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;

	case 'p': case 'P':
		// View from above "birds eye view"
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 0.0f, 15.0f, 0.1f ); // NOOOOOOOO!

		break;

	case 'o': case 'O':
		// Follow the play-ah.
	//	::g_pCamera->Follow( ::g_Player_ID, 0.25f, 2.5f, 2.0f );
		break;	

	case 'w': case 'W':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 0.0f, 2.0f, 5.1f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 'b': case 'B':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 0.0f, 2.0f, -5.1f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 'l': case 'L':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( 5.0f, 2.0f, 0.0f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 'r': case 'R':
		//::g_pCamera->eye.x -= 0.1f;		// Move the camera "left" (-ve x)
		//::g_pCamera->target = Vector3D( 0.0f, 0.0f, 0.0f );// Origin
		//::g_pCamera->eye =  Vector3D( -5.0f, 2.0f, 0.0f ); // NOOOOOOOO!
		//::g_ourObjects[2].y += 0.1f;	// Up
		//g_ourObjects[2].velY += 0.01f;
		//g_ourObjects[2].m_State = "GOING_UP";
		break;
	case 's': case 'S':
		if(!isGameOn)
		{
		boss->switchSound(1);
		::g_pCamera->eye.z += 0.1f;		// Right (+ve x)
		isGameOn = true;
		}
		//::g_ourObjects[2].y -= 0.1f;	// Down
		//::g_ourObjects[2].velY -= 0.01f;	// Down
		//g_ourObjects[2].m_State = "GOING_DOWN";
		break;
case 'c': case 'C':
		//::g_pCamera->eye.x += 0.1f;		// Right (+ve x)
		//::g_ourObjects[2].y -= 0.1f;	// Down
		//::g_ourObjects[2].velY -= 0.01f;	// Down
		//g_ourObjects[2].m_State = "GOING_DOWN";
		break;
	case 'a': case 'A':
		//::g_pCamera->eye.z -= 0.1f;		// Forward (-ve z)
		//::g_ourObjects[2].x -= 0.1f;	// Left
		//::g_ourObjects[2].velX -= 0.01f;	// Left
		//g_ourObjects[2].m_State = "GOING_LEFT";
		break;
	case 'd': case 'D':
		//::g_pCamera->eye.z += 0.1f;		// Back (-ve z)
		//::g_ourObjects[2].x += 0.1f;	// Right
		//::g_ourObjects[2].velX += 0.01f;	// Right
		//g_ourObjects[2].m_State = "GOING_RIGHT";
		break;

	case '+':
		
		std::cout<<"x = "<<v.x<<" y= "<<v.y<<" z= "<<v.z<<std::endl;
	//	::g_ShaderUniformVariables.Lights[0].constantAttenuation += 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].linearAttenuation += 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].quadraticAttenuation += 0.01f ; 
		break;

	case '-':
	//	::g_ShaderUniformVariables.Lights[0].constantAttenuation -= 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].linearAttenuation -= 0.01f ; 
		//::g_ShaderUniformVariables.Lights[0].quadraticAttenuation -= 0.01f ; 
		break;

	case 'i':
	//	::g_ShaderUniformVariables.Lights[0].position += glm::vec3(0.0f, 0.1f, 0.0f);	
		break;
	case 'k':
	//	::g_ShaderUniformVariables.Lights[0].position -= glm::vec3(0.0f, 0.1f, 0.0f);	
		break;

	case 'j':
	//	::g_ShaderUniformVariables.Lights[0].position -= glm::vec3(0.1f, 0.0f, 0.0f);	
		break;
	
	};

	return;
}

void specialKeyPressCallback( int key, int x, int y )
{
	
	if(isGameOn)
	{
	//std::vector <unsigned int> playerlist = boss->getMyPieces();
	unsigned int index =  boss->getPlayerId();
	//unsigned int index =  boss->getBossId();

	switch ( key )
	{
	case GLUT_KEY_UP:
		//::g_ourObjects[2].z += 0.1f;		// Away (along z axis)
		// Sending a bunny a command
		{
			
			boss->updateObject("VELOCITY",Vector3D(0.0f, 0.0f, 1.0f), index);
				boss->updateObject("ROTATETO",Vector3D(0.0f, 3.14f, 0.0f), index, 1.0f, "UP");
			boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "ACTIVE");
			
			//boss->updateObject("VELOCITY", Vector3D(0.0f, 0.0f, 0.25f),playerId);
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Z" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewZAcc", 0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_DOWN:
		//::g_ourObjects[2].z -= 0.1f;		// Towards (along z axis)
		{
				boss->updateObject("VELOCITY",Vector3D(0.0f, 0.0f, -1.0f), index);
				boss->updateObject("ROTATETO",Vector3D(0.0f, 3.14f, 0.0f), index, 1.0f, "DOWN");
				boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "ACTIVE");
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Z" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewZVel", -0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_LEFT:
		{	boss->updateObject("VELOCITY",Vector3D(1.0f, 0.0f, 0.0f), index);
			boss->updateObject("ROTATETO",Vector3D(0.0f, 3.14f, 0.0f), index, 1.0f, "LEFT");
			boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "ACTIVE");
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", -0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_RIGHT:
		{
				boss->updateObject("VELOCITY",Vector3D(-1.0f, 0.0f, 0.0f), index);
				boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "ACTIVE");
				boss->updateObject("ROTATETO",Vector3D(0.0f, 3.14f, 0.0f), index, 1.0f, "RIGHT");
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", 0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_CTRL_L:
		{
			//boss->updateObject("COLOUR",Vector3D(0.1f, 0.1f, 0.5f), playerlist[index]);
			//boss->attackPlayer();
		}
			break;
	};

	boss->setMyPiecesIndex(index);
	
	}	
	

	return;
}

void specialKeyUpCallback( int key, int x, int y )
{
	if(isGameOn)
	{
	//std::vector <unsigned int> playerlist = boss->getMyPieces();
	//unsigned int index = boss->getBossId();
	unsigned int index = boss->getPlayerId();

	switch ( key )
	{
	case GLUT_KEY_UP:
		//::g_ourObjects[2].z += 0.1f;		// Away (along z axis)
		// Sending a bunny a command
		{
			
			boss->updateObject("VELOCITY",Vector3D(0.0f, 0.0f, 0.0f), index);
			boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "PASSIVE");
			
			//boss->updateObject("VELOCITY", Vector3D(0.0f, 0.0f, 0.25f),playerId);
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Z" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewZAcc", 0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_DOWN:
		//::g_ourObjects[2].z -= 0.1f;		// Towards (along z axis)
		{
				boss->updateObject("VELOCITY",Vector3D(0.0f, 0.0f, 0.0f), index);
					boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "PASSIVE");
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "Z" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewZVel", -0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_LEFT:
		{	boss->updateObject("VELOCITY",Vector3D(0.0f, 0.0f, 0.0f), index);
			boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "PASSIVE");
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", -0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_RIGHT:
		{
				boss->updateObject("VELOCITY",Vector3D(0.0f, 0.0f, 0.0f), index);
					boss->updateObject("STATE",Vector3D(0.0f, 0.0f, 0.5f), index, 1.0f, "PASSIVE");
			//CMessage theMessage;
			//theMessage.vecNVPairs.push_back( CNameValuePair( "ChangeDirection", "X" ) );
			//theMessage.vecNVPairs.push_back( CNameValuePair( "NewXVel", 0.25f ) );
			//::g_pFactoryMediator->SendMessageToObject( g_Player_ID, 0, theMessage );
		}
		break;
	case GLUT_KEY_CTRL_L:
		{
		//	boss->updateObject("COLOUR",Vector3D(0.1f, 0.1f, 0.5f), playerlist[index]);
		}
			break;
	};

	//boss->setMyPiecesIndex(index);
	}
		
	

	return;
}