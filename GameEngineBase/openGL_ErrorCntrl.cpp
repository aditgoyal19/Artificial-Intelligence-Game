#include "global.h"
#include "master.h"


void ExitOnGLError(const char* error_message)
{
  const GLenum ErrorValue = glGetError();

  if (ErrorValue != GL_NO_ERROR)
  {
	//std::cout << gluErrorString(ErrorValue) << std::endl;
    exit(EXIT_FAILURE);
  }
}
