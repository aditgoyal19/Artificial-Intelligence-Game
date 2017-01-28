#include "global.h"

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "vertexType.h"		// For CVertex_fXYZ_fRGB, etc.
#include "gameObject.h"

// ***********************************************************************************
// ********************************* Function Prototype *********************************
void SetLightingUniforms(void);
void renderObjects(std::vector< GameObjectBase* > vec_pRenderedObjects, glm::mat4 matWorld , glm::mat4 matView, bool isChild = false);

// ********************************* TOP SECRET CODE *********************************
// ***********************************************************************************


void displayCallback(void)
{
	//++FrameCount;
	::g_FrameCount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//DrawCube();
 	// *********************************
	//float CubeAngle;				// Not needed, anymore

	clock_t Now = clock();

	if ( ::g_LastTime == 0 )	// if (LastTime == 0)
	{
		::g_LastTime = Now;		// LastTime = Now;
	}

	
	// *********************************
	glm::mat4 matView(1.0f);
	//matView = glm::lookAt( glm::vec3(0.0f, 2.0f, 4.0f),			// Camera (aka "Eye")
	//						glm::vec3(0.0f, 0.0f, 0.0f),		// At (aka "target")
	//						glm::vec3(0.0f, 1.0f, 0.0f) );		// Up
	matView = glm::lookAt( glm::vec3(g_pCamera->eye.x, g_pCamera->eye.y, g_pCamera->eye.z),			// Camera (aka "Eye")
							glm::vec3(g_pCamera->target.x, g_pCamera->target.y, g_pCamera->target.z),		// At (aka "target")
							glm::vec3(g_pCamera->up.x, g_pCamera->up.y, g_pCamera->up.z) );		// Up

	//ModelMatrix = IDENTITY_MATRIX;		/// aka "World" 
	glm::mat4 matWorld = glm::mat4(1.0f);		// aka "World" matrix



	
	
	renderObjects(boss->getSceneList(),matWorld  , matView);
    //renderObjects(boss->getNodeList(),matWorld  , matView);
	
	glBindVertexArray(0);
	// Detatch from the current shader program
	glUseProgram(0);


	// Now that everything is drawn, show the back buffer
	// (i.e. switch the 'back' framebuffer with the 'front'
	glutSwapBuffers();

	return;
}


// ***********************************************************************************
// ********************************* TOP SECRET CODE *********************************
void SetLightingUniforms(void)
{

	for (int index = 0; index < ::g_ShaderUniformVariables.MaxLights; index++ )
	{

		glUniform1i( ::g_ShaderUniformVariables.Lights[index].isEnabled_LocID, ::g_ShaderUniformVariables.Lights[index].isEnabled );
		glUniform1i( ::g_ShaderUniformVariables.Lights[index].isLocal_LocID, ::g_ShaderUniformVariables.Lights[index].isLocal );
		glUniform1i( ::g_ShaderUniformVariables.Lights[index].isSpot_LocID, ::g_ShaderUniformVariables.Lights[index].isSpot );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].ambient_LocID, ::g_ShaderUniformVariables.Lights[index].ambient.r, 
																		 ::g_ShaderUniformVariables.Lights[index].ambient.g,
																		 ::g_ShaderUniformVariables.Lights[index].ambient.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].color_LocID, ::g_ShaderUniformVariables.Lights[index].color.r, 
																	   ::g_ShaderUniformVariables.Lights[index].color.g,
																	   ::g_ShaderUniformVariables.Lights[index].color.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].position_LocID, ::g_ShaderUniformVariables.Lights[index].position.r, 
			                                                                  ::g_ShaderUniformVariables.Lights[index].position.g,
		                                                                      ::g_ShaderUniformVariables.Lights[index].position.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].halfVector_LocID, ::g_ShaderUniformVariables.Lights[index].halfVector.r, 
			                                                                    ::g_ShaderUniformVariables.Lights[index].halfVector.g,
		                                                                        ::g_ShaderUniformVariables.Lights[index].halfVector.b );

		glUniform3f( ::g_ShaderUniformVariables.Lights[index].coneDirection_LocID, ::g_ShaderUniformVariables.Lights[index].coneDirection.r, 
			                                                                       ::g_ShaderUniformVariables.Lights[index].coneDirection.g,
		                                                                           ::g_ShaderUniformVariables.Lights[index].coneDirection.b );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].spotCosCutoff_LocID, ::g_ShaderUniformVariables.Lights[index].spotCosCutoff );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].spotExponent_LocID, ::g_ShaderUniformVariables.Lights[index].spotExponent );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].constantAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].constantAttenuation );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].linearAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].linearAttenuation );

		glUniform1f( ::g_ShaderUniformVariables.Lights[index].quadraticAttenuation_LocID, ::g_ShaderUniformVariables.Lights[index].quadraticAttenuation );

	}
	return;
}
// ********************************* TOP SECRET CODE *********************************
// ***********************************************************************************
void renderObjects(std::vector< GameObjectBase* > vec_pRenderedObjects, glm::mat4 matWorld  , glm::mat4 matView ,bool isChild)
{


	for ( int index = 0; index != static_cast<int>( vec_pRenderedObjects.size() ); index++ )
	{

		
		
		if(!isChild)
			{
			matWorld = glm::mat4(1.0f);

			
			}
	
		

		matWorld = glm::translate( matWorld, glm::vec3( vec_pRenderedObjects[index]->getPosition().x, 
								              vec_pRenderedObjects[index]->getPosition().y, 
											  vec_pRenderedObjects[index]->getPosition().z) );
		
		
			

		matWorld = glm::rotate( matWorld, vec_pRenderedObjects[index]->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f) );
		matWorld = glm::rotate( matWorld, vec_pRenderedObjects[index]->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f) );
		matWorld = glm::rotate( matWorld, vec_pRenderedObjects[index]->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f) );


		matWorld = glm::scale( matWorld, glm::vec3( vec_pRenderedObjects[index]->getScale(), 
								         vec_pRenderedObjects[index]->getScale(), 
										 vec_pRenderedObjects[index]->getScale()) );

		
		
		// *** START of DRAW THE OBJECT FROM THE BUFFER ****
		// Add this line
		//glPolygonMode( GL_FRONT,  GL_LINE );
		/*
		if(isWireFrame){
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}else{
		glPolygonMode( GL_FRONT_AND_BACK ,  GL_LINE );
		}
*/
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		

		//glUseProgram(g_ShaderIds[0]);
		glUseProgram( g_ShaderProgram_ID );

		::g_SetShaderUniformVariables();

		// Also set the shininess, Strength, EyeDirection (i.e. camera)

		// Set the "EyeDirection" (aka the camera)
		::glUniform3f( ::g_ShaderUniformVariables.EyeDirection_LocationID, 
			           ::g_pCamera->eye.x, ::g_pCamera->eye.y, ::g_pCamera->eye.z );

		// Shininess and Strength...
		glUniform1f( ::g_ShaderUniformVariables.Shininess_LocationID, 
			         vec_pRenderedObjects[index]->getSpecularShininess() );

		glUniform1f( ::g_ShaderUniformVariables.Strength_LocationID, 
			         vec_pRenderedObjects[index]->getSpecularStrength() );

		SetLightingUniforms();
		// ********************************* TOP SECRET CODE *********************************
		// ***********************************************************************************


		ExitOnGLError("ERROR: Could not use the shader program");


		glUniformMatrix4fv( ::g_ShaderUniformVariables.matWorld_LocationID, 1, GL_FALSE, glm::value_ptr(matWorld) );
		glUniformMatrix4fv( ::g_ShaderUniformVariables.matView_LocationID, 1, GL_FALSE, glm::value_ptr(matView) );


		ExitOnGLError("ERROR: Could not set the shader uniforms");

		int numberOfIndicesToRender = 0;
		
		
		GLuint vertexBufferObjectID = vec_pRenderedObjects[index]->getVertexBufferId();
		GLuint vertexAttribBufferID = vec_pRenderedObjects[index]->getVertexAttribId();

		int numberOfElements = vec_pRenderedObjects[index]->GetNumberOfElements();
			


		
		glBindVertexArray( vertexBufferObjectID );					//  g_VertexPositionBufferID[1] );		// "Connects" to a vertex buffer
		glBindBuffer( GL_ARRAY_BUFFER, vertexAttribBufferID );		//  g_VertexColourBufferID[1] );		// Also buffer (with colours)
	
		numberOfIndicesToRender = numberOfElements * 3;			// g_numberOfTriangles[1] * 3; 
		

		glEnableVertexAttribArray(0);			// Position
		glEnableVertexAttribArray(1);			// Colour
		glEnableVertexAttribArray(2);			// Normal
		ExitOnGLError("ERROR: Could not enable vertex attributes");

		

		ExitOnGLError("ERROR: Could not set VAO attributes");


		
		glDrawElements(GL_TRIANGLES,  
			           numberOfIndicesToRender, 
					   GL_UNSIGNED_INT, (GLvoid*)0 );
		ExitOnGLError("ERROR: Could not draw the cube");
		// *** END of DRAW THE OBJECT FROM THE BUFFER ****

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//If GameObjects has child objects
		if(vec_pRenderedObjects[index]->hasChildObjects())
		{
		renderObjects( vec_pRenderedObjects[index]->getChildObjects(), matWorld  , matView, true);
		}
	

	}






}

// ***********************************************************************************