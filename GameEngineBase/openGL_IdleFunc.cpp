#include "global.h" 
#include "master.h"


static const float g_MAXIMUM_TIME_STEP = 0.1f;		// 10th of a second or 100ms 



void idleFunction(void)
{
	// Update the "simulation" at this point.
	// 1. Get elapsed time
	g_simTimer.Stop();
	float deltaTime = ::g_simTimer.GetElapsedSeconds();
	// Is the number TOO big (we're in a break point or something?)
	if ( deltaTime > g_MAXIMUM_TIME_STEP )
	{	// Yup, so clamp it to a new value
		deltaTime = g_MAXIMUM_TIME_STEP;
	}
	g_simTimer.Start();


	if(gameWin){
	boss->enemiesFlee(deltaTime);
	}
	if(isGameOn)
	{
	boss->simulation(deltaTime);
	
	
	::g_pCamera->Update( deltaTime );

	
		Vector3D pos = boss->getDistanceFromPlayer(Vector3D(4.5f,0.2f,5.01f));

		if(pos.Magnitude() < 0.5f)
		{
		    boss->playSample(0);
			boss->stopSound(1);
			std::cout<<"Congrats you have finished the Level"<<std::endl;

			boss->enemiesFlee(deltaTime);
			isGameOn = false;
			gameWin = true;
		}

		if(!boss->isPlayerAlive())
		{
			boss->playSample(1);
			boss->stopSound(1);
			std::cout<<"Game Over......"<<std::endl;
			isGameOn = false;
		}
	
	}

	boss->simulatePlayer(deltaTime);


	glutPostRedisplay();
	return;
}

void timerFunction(int Value)
{
  if (0 != Value) 
  {


	std::stringstream ss;
	ss << WINDOW_TITLE_PREFIX << ": " 
		<< ::g_FrameCount * 4 << " Frames Per Second @ "
		<< ::g_screenWidth << " x"				// << CurrentWidth << " x "
		<< ::g_screenHeight;					// << CurrentHeight;

    glutSetWindowTitle(ss.str().c_str());
    //glutSetWindowTitle(TempString);
    //free(TempString);
  }

  ::g_FrameCount = 0;	// FrameCount = 0;
  glutTimerFunc(250, timerFunction, 1);

  return;
}