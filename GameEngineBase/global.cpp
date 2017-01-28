#include "global.h"


 int g_screenWidth = 1400;
 int g_screenHeight = 900;
 int g_windowHandle = 0;
 unsigned int g_FrameCount = 0;

  CHRTimer g_simTimer;

  CShaderUniformVariables g_ShaderUniformVariables;

  GLuint g_ShaderProgram_ID = 0;
GLuint g_VertexShader_ID = 0;
GLuint g_FragmentShader_ID = 0;

clock_t g_LastTime = 0 ;

 CCamera* g_pCamera= 0;

 Delegator* boss = new Delegator();

bool isGameOn = false;
bool gameWin = false;