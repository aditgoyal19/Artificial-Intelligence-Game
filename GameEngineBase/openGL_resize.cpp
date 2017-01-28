#include "global.h"
#include "master.h"

void resizeCallback(int Width, int Height)
{
	::g_screenWidth = Width;	// CurrentWidth = Width;
	::g_screenHeight = Height;	// CurrentHeight = Height;

	glViewport(0, 0, ::g_screenWidth, ::g_screenHeight);

	::g_ShaderUniformVariables.matProjection = glm::mat4(1.0f);
	::g_ShaderUniformVariables.matProjection = glm::perspective( glm::radians(45.0f), (float)::g_screenWidth / ::g_screenHeight, 0.1f, 100.f);


	glUseProgram( g_ShaderProgram_ID );

	glUniformMatrix4fv( ::g_ShaderUniformVariables.matProjection_LocationID, 1, GL_FALSE, glm::value_ptr(::g_ShaderUniformVariables.matProjection));

	glUseProgram(0);

	return;
}