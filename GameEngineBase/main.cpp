#include "global.h"
#include "fileDataLoader.h"




void LoadShaders(void)
{
	
	// A "Shader Program" is a container to hold a "set" of shaders  (at least a vertex and a fragment shader, but possibly more)
	g_ShaderProgram_ID = glCreateProgram();	


	ExitOnGLError("ERROR: Could not create the shader program");

	g_VertexShader_ID =  FileDataLoader::LoadShader("shaders/OpenGLProgGuidMutipleLights.vertex.glsl", GL_VERTEX_SHADER);
	g_FragmentShader_ID = FileDataLoader::LoadShader("shaders/OpenGLProgGuidMutipleLights.fragment.glsl", GL_FRAGMENT_SHADER);


	// Now we associate these specific COMPILED shaders to the "program"...
	glAttachShader( g_ShaderProgram_ID, g_VertexShader_ID );
	glAttachShader( g_ShaderProgram_ID, g_FragmentShader_ID );

	glLinkProgram( g_ShaderProgram_ID );

	ExitOnGLError("ERROR: Could not link the shader program");


  return;
}




int main(int argc, char* argv[])
{

	::OpenGL_Initialize( argc, argv, 1200, 800 );


	LoadShaders();
	boss->createScene();
	boss->createNodes();
	boss->initAudio();
	//boss->simulatePathfinding();
	//Create object
	//boss->createObject("General","ply/RocketMain.ply");
	//boss->createSceneWithMulPlayer();

	//Camera 
	g_pCamera = new CCamera();
	// Camera expects an IMediator*, so cast it as that
	

	g_pCamera->eye.x = 0.0f;		// Centred (left and right)
	g_pCamera->eye.y = 10.0f;		// 2.0 units "above" the "ground"
	g_pCamera->eye.z = -6.9f;		// 4.0 units "back" from the origin

	//g_pCamera->target    Vector3D gets set to 0,0,0

	g_pCamera->up.x = 0.0f;
	g_pCamera->up.y = 1.0f;		
	::g_SetShaderUniformVariables();

	// Set up the basic lighting
	::g_ShaderUniformVariables.Lights[0].isEnabled = GL_TRUE;
	::g_ShaderUniformVariables.Lights[0].isLocal = GL_TRUE;		// Only directional lights AREN'T local
	::g_ShaderUniformVariables.Lights[0].isSpot = GL_FALSE;		// Local = TRUE, Spot = FALSE --- Point light

	::g_ShaderUniformVariables.Lights[0].color = glm::vec3(3.0f, 3.0f, 3.0f);		// White light
	::g_ShaderUniformVariables.Lights[0].ambient = glm::vec3(0.1f, 0.1f, 0.1f);	// White light
	::g_ShaderUniformVariables.Lights[0].position = glm::vec3(0.0f, 4.0f, 0.0f);	// Just above the origin
	//::g_ShaderUniformVariables.Lights[0].halfVector = glm::vec3(1.0f, 1.0f, 1.0f); // = normalize( lightDirection + EyeDirection ); Only used for directional light
	//::g_ShaderUniformVariables.Lights[0].coneDirection =glm::vec3(0.0f, 0.0f, 0.0f); // Only used for spot lights
	//::g_ShaderUniformVariables.Lights[0].spotCosCutoff =5.0f; // Only used for spot lights
	//::g_ShaderUniformVariables.Lights[0].spotExponent = 1.0f;// Only used for spot lights

	::g_ShaderUniformVariables.Lights[0].constantAttenuation = 0.1f;
	::g_ShaderUniformVariables.Lights[0].linearAttenuation = 0.1f;
	::g_ShaderUniformVariables.Lights[0].quadraticAttenuation = 0.08f;

	g_simTimer.Reset();
	g_simTimer.Start();		// Start "counting"


	std::cout<<"Press S to start playing"<<std::endl;
	glutMainLoop();
  
	exit(EXIT_SUCCESS);


return 0;
}

