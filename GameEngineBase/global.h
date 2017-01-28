#ifndef _GLOBAL_GH
#define _GLOBAL_GH

#include <string>
#include "CHRTimer.h"
#include "shaderUniformVariables.h"
#include "camera.h" 
#include <time.h>
#include "delegator.h"


//used to define global variables 


extern int g_screenWidth ,g_screenHeight, g_windowHandle ; 
extern unsigned int g_FrameCount ;

static const std::string g_WindowTitleDefault = "OpenGL Game";
#define WINDOW_TITLE_PREFIX "Game Window"


//Function called to initialize everything
bool OpenGL_Initialize(int argc, char* argv[], int screenWidth, int screenHeight);

// OpenGL callbacks
void resizeCallback(int Width, int Height);		
void displayCallback(void);						
void timerFunction(int);
void idleFunction(void);
void closeCallback(void);						
void keyboardPressCallback(unsigned char key, int x, int y);	
void keyboardUpCallback(unsigned char key, int x, int y);	
void specialKeyPressCallback( int key, int x, int y );
void specialKeyUpCallback( int key, int x, int y );
void drawText(const char *text, int length , float x, float y);
//Error checking
void ExitOnGLError(const char* error_message);


//Timer 
extern CHRTimer g_simTimer;

//Shader variables
extern CShaderUniformVariables g_ShaderUniformVariables;

//Shader program info
extern GLuint g_ShaderProgram_ID , g_VertexShader_ID , g_FragmentShader_ID;

//Time
extern clock_t g_LastTime ;


//Camera object
extern CCamera* g_pCamera;


//Delegator
extern Delegator* boss;

//Game Status
extern bool isGameOn;
extern bool gameWin;


#endif