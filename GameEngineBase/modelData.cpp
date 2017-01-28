#include "modelData.h"
#include "Vector3D.h"
#include <sstream>
#include <math.h>
#include <algorithm>
#include <fstream>
#include "vertexType.h"
#include "global.h"

const float PI = 3.141592653589793238462643383279502884197f;	


ModelData::ModelData()
{

	this->m_minX = this->m_maxX = this->m_deltaX = 0.0f;
	this->m_minY = this->m_maxY = this->m_deltaY = 0.0f;
	this->m_minZ = this->m_maxZ = this->m_deltaZ = 0.0f;
	this->m_centreX = this->m_centreY = this->m_centreZ = 0.0f;
	//
	this->m_ID = statNextID++;
	//
	this->m_numberOfVertices = 0;
	this->m_numberOfElements = 0;
	
	// Added March 14, 2012
	this->m_bHadNormalsInFile = false;
	this->m_bHadTextureCoordinatesInFile = false;
	this->m_totalProperties = INT_MAX;
	this->m_x_propertyIndex = INT_MAX;
	this->m_y_propertyIndex = INT_MAX;
	this->m_z_propertyIndex = INT_MAX;
	this->m_normx_propertyIndex = INT_MAX;
	this->m_normy_propertyIndex = INT_MAX;
	this->m_normz_propertyIndex = INT_MAX;
	this->m_red_propertyIndex = INT_MAX;
	this->m_green_propertyIndex = INT_MAX;
	this->m_blue_propertyIndex = INT_MAX;
	this->m_tex0u_propertyIndex = INT_MAX;
	this->m_tex0v_propertyIndex = INT_MAX;
	this->m_tex1u_propertyIndex = INT_MAX;
	this->m_tex1v_propertyIndex = INT_MAX;

}



ModelData::ModelData( const ModelData &rhs )	// Copy constructor
{
	this->m_verticies = rhs.m_verticies;
	this->m_elements = rhs.m_elements;

	this->m_minX = rhs.m_minX;
	this->m_minY = rhs.m_minY;
	this->m_minZ = rhs.m_minZ;

	this->m_maxX = rhs.m_maxX;
	this->m_maxY = rhs.m_maxY;
	this->m_maxZ = rhs.m_maxZ;

	this->m_deltaX = rhs.m_deltaX;
	this->m_deltaY = rhs.m_deltaY;
	this->m_deltaZ = rhs.m_deltaZ;

	this->m_centreX = rhs.m_centreX;
	this->m_centreY = rhs.m_centreY;
	this->m_centreZ = rhs.m_centreZ;

	this->m_maxExtent = 0.0f;

	this->m_totalProperties = rhs.m_totalProperties;
	this->m_x_propertyIndex = rhs.m_x_propertyIndex;
	this->m_y_propertyIndex = rhs.m_y_propertyIndex;
	this->m_z_propertyIndex = rhs.m_z_propertyIndex;
	this->m_normx_propertyIndex = rhs.m_normx_propertyIndex;
	this->m_normy_propertyIndex = rhs.m_normy_propertyIndex;
	this->m_normz_propertyIndex = rhs.m_normz_propertyIndex;
	this->m_red_propertyIndex = rhs.m_red_propertyIndex;
	this->m_green_propertyIndex = rhs.m_green_propertyIndex;
	this->m_blue_propertyIndex = rhs.m_blue_propertyIndex;

	// Added March 14, 2012
	this->m_bHadTextureCoordinatesInFile = rhs.m_bHadTextureCoordinatesInFile;
	this->m_bHadNormalsInFile = rhs.m_bHadNormalsInFile;
	this->m_tex0u_propertyIndex = rhs.m_tex0u_propertyIndex;
	this->m_tex0v_propertyIndex = rhs.m_tex0v_propertyIndex;
	this->m_tex1u_propertyIndex = rhs.m_tex1u_propertyIndex;
	this->m_tex1v_propertyIndex = rhs.m_tex1v_propertyIndex;
	// End of Added
}

//static 
unsigned int ModelData::statNextID = 1;


bool ModelData::OpenPLYFile(std::wstring fileName, std::wstring &error)
{
	error = L"OK";
	std::wifstream thePlyFile(fileName.c_str());
	
	if (!thePlyFile.is_open())
	{
		error = L"Can't open the file. Sorry it didn't work out.";
		return false;
	}

	std::wstring tempString;
	this->m_numberOfVertices = 0;
	this->m_numberOfElements = 0;

	try
	{
		bool bItsABunnyFile = true;
		// ply
		thePlyFile >> tempString;	if ( tempString != L"ply")		{ bItsABunnyFile = false; error = L"No a ply file."; throw; }
		// format ascii 1.0
		thePlyFile >> tempString;	if ( tempString != L"format")	{ bItsABunnyFile = false; throw; }
		thePlyFile >> tempString;	if ( tempString != L"ascii")	{ bItsABunnyFile = false; error = L"Must be an ASCII ply file."; throw; }
		thePlyFile >> tempString;	if ( tempString != L"1.0")		{ bItsABunnyFile = false; throw; }

		// Find the number of verticies...
		// Item after "vertex" is number of verticies
		while ( thePlyFile >> tempString )
		{
			if ( tempString == L"vertex" )	break;
		}			
		thePlyFile >> this->m_numberOfVertices;	// 453

		// Read the properties and note the index locations of them...
		int currentIndex = 0;
		while ( true )
		{
			thePlyFile >> tempString; 
			if ( tempString == L"element" ) { break; /* on to next part of file */ }
			// property float x
			if ( tempString == L"property") 
			{
				thePlyFile >> tempString; 
				if ( ( tempString == L"float") | ( tempString == L"uchar") )	
				{	// Figure out which index to set
					thePlyFile >> tempString;
					this->m_setIndexBasedOnPropertyName( currentIndex, tempString );
				}
				else 
				{ 
					error = L"expected property type missing"; throw; 
				} // if ( tempString == L"float")	
			}
			else
			{ 
				error = L"expected property"; throw; 
			} // if ( tempString == L"property") 
			currentIndex++;
		}
		this->m_totalProperties = currentIndex;
		// 
		thePlyFile >> tempString;	if ( tempString != L"face")	{ bItsABunnyFile = false; error = L"expected element face."; throw; }
		thePlyFile >> this->m_numberOfElements;	

		while ( thePlyFile >> tempString )
		{ 
			if ( tempString == L"end_header" )	break;
		}

		// Now the real work begins...
		//... a bunch of vertices...
		//-0.0312216 0.126304 0.00514924 0.850855 0.5 
		for (int vertexCount = 0; vertexCount != this->m_numberOfVertices; vertexCount++)
		{
			PLYVERTEX tempVertex;
			// Place the data into the array...
			// Read through the properties and place them into the appropriate part of the vertex...
			for (int curPropIndex = 0; curPropIndex != this->m_totalProperties; curPropIndex++)
			{
				std::wstring tempString;
				thePlyFile >> tempString;
				// Load this item based on index
				this->m_placeItemInAppropriateVertexLocation( tempString, curPropIndex, tempVertex );
			}
			
			this->m_verticies.push_back(tempVertex);
		}
		
		this->calcualteExtents();

		// Now read the elements (the triangles...)
		//... a bunch of elements that refer to the verticies
		//3 435 423 430 
		for (int elementCount = 0; elementCount != this->m_numberOfElements; elementCount++)
		{
			PLYELEMENT tempElement;
			thePlyFile >> tempString;	// 3 
			thePlyFile >> tempElement.vertex_1;
			thePlyFile >> tempElement.vertex_2;
			thePlyFile >> tempElement.vertex_3;
			this->m_elements.push_back( tempElement );
		}
	}
	catch (...)
	{
		error = L"Something went wrong while reading the file.";
		return false;
	}

	



	
	return true;
}

void ModelData::setFileName(std::wstring name)
{


	this->fileName = name;

}

void ModelData::calcualteExtents(void)
{
	this->m_minX = this->m_verticies.begin()->pos.x;
	this->m_maxX = this->m_verticies.begin()->pos.z;
	this->m_minY = this->m_verticies.begin()->pos.y;
	this->m_maxY = this->m_verticies.begin()->pos.y;
	this->m_minZ = this->m_verticies.begin()->pos.z;
	this->m_maxZ = this->m_verticies.begin()->pos.z;

	this->m_deltaX = this->m_maxX - this->m_minX;
	this->m_deltaY = this->m_maxY - this->m_minY;
	this->m_deltaZ = this->m_maxZ - this->m_minZ;

	this->m_maxExtent = this->m_deltaX;
	if ( this->m_deltaY > this->m_maxExtent )	this->m_maxExtent = this->m_deltaY;
	if ( this->m_deltaZ > this->m_maxExtent )	this->m_maxExtent = this->m_deltaZ;

	std::vector<PLYVERTEX>::iterator itVertex = this->m_verticies.begin();
	for ( ; itVertex != this->m_verticies.end(); itVertex++ )
	{
		// Check bounding box limits...
		if ( itVertex->pos.x < this->m_minX )	this->m_minX = itVertex->pos.x;
		if ( itVertex->pos.x > this->m_maxX )	this->m_maxX = itVertex->pos.x;
		if ( itVertex->pos.y < this->m_minY )	this->m_minY = itVertex->pos.y;
		if ( itVertex->pos.y > this->m_maxY )	this->m_maxY = itVertex->pos.y;
		if ( itVertex->pos.z < this->m_minZ )	this->m_minZ = itVertex->pos.z;
		if ( itVertex->pos.z > this->m_maxZ )	this->m_maxZ = itVertex->pos.z;
		this->m_deltaX = this->m_maxX - this->m_minX;
		this->m_deltaY = this->m_maxY - this->m_minY;
		this->m_deltaZ = this->m_maxZ - this->m_minZ;
		// 
		if ( this->m_deltaX > this->m_maxExtent )	this->m_maxExtent = this->m_deltaX;
		if ( this->m_deltaY > this->m_maxExtent )	this->m_maxExtent = this->m_deltaY;
		if ( this->m_deltaZ > this->m_maxExtent )	this->m_maxExtent = this->m_deltaZ;
	}
	return;
}


void ModelData::scaleVertices( float scaleFactor )
{
	std::vector<PLYVERTEX>::iterator itVertex = this->m_verticies.begin();
	for ( ; itVertex != this->m_verticies.end(); itVertex++ )
	{
		itVertex->pos.x *= scaleFactor;
		itVertex->pos.y *= scaleFactor;
		itVertex->pos.z *= scaleFactor;
	}
	this->calcualteExtents();
	return;
}

ModelData::~ModelData()
{

	return;
}

unsigned int ModelData::GetID( void ) 
{
	return this->m_ID;
}

void ModelData::normalize(void)
{
	// The first part of this is the same as the 'rock-n-roll' versions,
	//	but instead of just overwriting the vertices at each face, the
	//	normalized normal is ADDED to the existing normal at that face.
	// Once we are all done, we go through each vertex an normalize them.
	// What this effectively does is get the AVERAGE of all the normals 
	//	of the faces around each vertes.
	// It's only slightly more complicated, and is more 'proper.'
	// LONG WAY version
	std::vector<PLYELEMENT>::iterator itVecFace;
	for ( itVecFace = this->m_elements.begin(); itVecFace != this->m_elements.end(); itVecFace++)
	{	
		// Get the three corners (verticies) of the triangle
		Vector3D vectorA, vectorB, vectorC;
		vectorA.x = this->m_verticies.at( itVecFace->vertex_1 ).pos.x;
		vectorA.y = this->m_verticies.at( itVecFace->vertex_1 ).pos.y;
		vectorA.z = this->m_verticies.at( itVecFace->vertex_1 ).pos.z;
		vectorB.x = this->m_verticies.at( itVecFace->vertex_2 ).pos.x;
		vectorB.y = this->m_verticies.at( itVecFace->vertex_2 ).pos.y;
		vectorB.z = this->m_verticies.at( itVecFace->vertex_2 ).pos.z;
		vectorC.x = this->m_verticies.at( itVecFace->vertex_3 ).pos.x;
		vectorC.y = this->m_verticies.at( itVecFace->vertex_3 ).pos.y;
		vectorC.z = this->m_verticies.at( itVecFace->vertex_3 ).pos.z;
		// calculate the vectors for the cross...
		Vector3D vecAB;
			
		vecAB = vectorB - vectorA;
		

		Vector3D vecBC;

		vecBC = vectorC - vectorB;

		Vector3D normal = normal.CrossProduct( vecAB, vecBC);
	
		normal.Normalize();

		// Load the normals onto the verticies
		// NOTE: We are ADDING instead of OVERWRITING...
		this->m_verticies.at( itVecFace->vertex_1 ).nx += normal.x;  //****
		this->m_verticies.at( itVecFace->vertex_1 ).ny += normal.y;  //****
		this->m_verticies.at( itVecFace->vertex_1 ).nz += normal.z;  //****
		this->m_verticies.at( itVecFace->vertex_2 ).nx += normal.x;  //****
		this->m_verticies.at( itVecFace->vertex_2 ).ny += normal.y;  //****
		this->m_verticies.at( itVecFace->vertex_2 ).nz += normal.z;  //****
		this->m_verticies.at( itVecFace->vertex_3 ).nx += normal.x;  //****
		this->m_verticies.at( itVecFace->vertex_3 ).ny += normal.y;  //****
		this->m_verticies.at( itVecFace->vertex_3 ).nz += normal.z;  //****
	}
	// Now go through all the vertices and normalize (average) them...
	std::vector<PLYVERTEX>::iterator itVert;
	for ( itVert = this->m_verticies.begin(); itVert != this->m_verticies.end(); itVert++)
	{	
		Vector3D v;
		v.Normalize( itVert->nx, itVert->ny, itVert->nz );
	}
}

void ModelData::GenTextureCoordsSpherical( enumTEXCOORDBIAS uBias, enumTEXCOORDBIAS vBias, bool basedOnNormals, float scale, bool fast )
{
	// determine the 'remaining' coordinate...
	bool xUsed = false;
	bool yUsed = false;
	bool zUsed = false;
	if ( uBias == POSITIVE_X || vBias == POSITIVE_X )	xUsed = true;
	if ( uBias == POSITIVE_Y || vBias == POSITIVE_Y )	yUsed = true;
	if ( uBias == POSITIVE_Z || vBias == POSITIVE_Z )	yUsed = true;
	
	std::vector<PLYVERTEX>::iterator itVert;
	for ( itVert = this->m_verticies.begin(); itVert != this->m_verticies.end(); itVert++ )
	{
		Vector3D xyz;
		if ( basedOnNormals )
		{
			if ( uBias == POSITIVE_X )		xyz.x = itVert->nx;
			else if ( uBias == POSITIVE_Y )	xyz.x = itVert->ny;
			else if ( uBias == POSITIVE_Z )	xyz.x = itVert->nz;

			if ( vBias == POSITIVE_X )		xyz.y = itVert->nx;
			else if ( vBias == POSITIVE_Y )	xyz.y = itVert->ny;
			else if ( vBias == POSITIVE_Z )	xyz.y = itVert->nz;

			// Fill in the remaining coordinate...
			if ( !xUsed )	xyz.z = itVert->nx;
			if ( !yUsed )	xyz.z = itVert->ny;
			if ( !zUsed )	xyz.z = itVert->nz;
		}
		else
		{
			if ( uBias == POSITIVE_X )		xyz.x = itVert->pos.x;
			else if ( uBias == POSITIVE_Y )	xyz.x = itVert->pos.y;
			else if ( uBias == POSITIVE_Z )	xyz.x = itVert->pos.z;

			if ( vBias == POSITIVE_X )		xyz.y = itVert->pos.x;
			else if ( vBias == POSITIVE_Y )	xyz.y = itVert->pos.y;
			else if ( vBias == POSITIVE_Z )	xyz.y = itVert->pos.z;

			// Fill in the remaining coordinate...
			if ( !xUsed )	xyz.z = itVert->pos.x;
			if ( !yUsed )	xyz.z = itVert->pos.y;
			if ( !zUsed )	xyz.z = itVert->pos.z;
		}

		xyz.Normalize();

		if ( fast )
		{
			itVert->tex0u = ( ( xyz.x / 2.0f) + 0.5f ) * scale;
			itVert->tex0v = ( ( xyz.y / 2.0f) + 0.5f ) * scale;
		}
		else
		{
			itVert->tex0u = ( ( asin(xyz.x) / PI ) + 0.5f ) * scale;
			itVert->tex0v = ( ( asin(xyz.y) / PI ) + 0.5f ) * scale;
		}
		itVert->tex1u = itVert->tex0u;
		itVert->tex1v = itVert->tex0v;
	}
}

PLYVERTEX ModelData::getVertex_at(std::vector<PLYVERTEX>::size_type index)
{
	PLYVERTEX x = this->m_verticies.at( index );
	return x;
}

PLYELEMENT ModelData::getElement_at(std::vector<PLYELEMENT>::size_type index)
{
	PLYELEMENT x = this->m_elements.at( index );
	return x;
}


void ModelData::m_setIndexBasedOnPropertyName(int curIndex, std::wstring propName)
{
	if ( propName == L"x")  { this->m_x_propertyIndex = curIndex; return; }
	if ( propName == L"y")	{ this->m_y_propertyIndex = curIndex; return; }
	if ( propName == L"z")	{ this->m_z_propertyIndex = curIndex; return; }

	// Added: March 14, 2012
	if ( propName == L"nx" ) { this->m_normx_propertyIndex = curIndex; this->m_bHadNormalsInFile = true; return; }
	if ( propName == L"ny" ) { this->m_normy_propertyIndex = curIndex; this->m_bHadNormalsInFile = true; return; }
	if ( propName == L"nz" ) { this->m_normz_propertyIndex = curIndex; this->m_bHadNormalsInFile = true; return; }
	// End of Added

	if ( propName == L"r")	{ this->m_red_propertyIndex = curIndex; return; }
	if ( propName == L"red")	{ this->m_red_propertyIndex = curIndex; return; }
	if ( propName == L"g")	{ this->m_green_propertyIndex = curIndex; return; }
	if ( propName == L"green")	{ this->m_green_propertyIndex = curIndex; return; }
	if ( propName == L"b")	{ this->m_blue_propertyIndex = curIndex; return; }
	if ( propName == L"blue")	{ this->m_blue_propertyIndex = curIndex; return; }
	
	// Added: March 14, 2012
	// Textures... note: ply only defines one texture coord...
	if ( propName == L"u" )	{ this->m_tex0u_propertyIndex = curIndex; this->m_bHadTextureCoordinatesInFile = true; return; }
	if ( propName == L"v" ) { this->m_tex0v_propertyIndex = curIndex; this->m_bHadTextureCoordinatesInFile = true; return; }
	// ...so these ones aren't in any 'normal' ply file
	if ( propName == L"tex0u" ) { this->m_tex0u_propertyIndex = curIndex; this->m_bHadTextureCoordinatesInFile = true; return; }
	if ( propName == L"tex0v" ) { this->m_tex0v_propertyIndex = curIndex; this->m_bHadTextureCoordinatesInFile = true; return; }
	if ( propName == L"tex1u" ) { this->m_tex1u_propertyIndex = curIndex; this->m_bHadTextureCoordinatesInFile = true; return; }
	if ( propName == L"tex1v" ) { this->m_tex1v_propertyIndex = curIndex; this->m_bHadTextureCoordinatesInFile = true; return; }
	// End of Added



}

bool ModelData::m_placeItemInAppropriateVertexLocation( std::wstring tempString, int propertyIndex, PLYVERTEX &tempVertex )
{
	// Convert val to float
	std::wstringstream ss;	
	ss << tempString;
	float valAsFloat = 0.0f;
	ss >> valAsFloat;
	if ( propertyIndex == this->m_x_propertyIndex) { tempVertex.pos.x = valAsFloat; return true;}
	if ( propertyIndex == this->m_y_propertyIndex) { tempVertex.pos.y = valAsFloat; return true; }
	if ( propertyIndex == this->m_z_propertyIndex) { tempVertex.pos.z = valAsFloat; return true; }
	if ( propertyIndex == this->m_red_propertyIndex) { tempVertex.red = valAsFloat; return true; }
	if ( propertyIndex == this->m_green_propertyIndex) { tempVertex.green = valAsFloat; return true; }
	if ( propertyIndex == this->m_blue_propertyIndex) { tempVertex.blue = valAsFloat; return true; }
	
	// Added March 14, 2012
	if ( propertyIndex == this->m_normx_propertyIndex ) { tempVertex.nx = valAsFloat; return true; }
	if ( propertyIndex == this->m_normy_propertyIndex ) { tempVertex.ny = valAsFloat; return true; }
	if ( propertyIndex == this->m_normz_propertyIndex ) { tempVertex.nz = valAsFloat; return true; }
	if ( propertyIndex == this->m_tex0u_propertyIndex ) { tempVertex.tex0u = valAsFloat; return true; }
	if ( propertyIndex == this->m_tex0v_propertyIndex ) { tempVertex.tex0v = valAsFloat; return true; }
	if ( propertyIndex == this->m_tex1u_propertyIndex ) { tempVertex.tex1u = valAsFloat; return true; }
	if ( propertyIndex == this->m_tex1v_propertyIndex ) { tempVertex.tex1v = valAsFloat; return true; }
	// End of Added

	// Didn't find a match
	return false;
}

// Added March 14, 2012
bool ModelData::bHadTextureCoordinatesInFile(void)
{
	return this->m_bHadTextureCoordinatesInFile;
}

bool ModelData::bHadNormalsInFile(void)
{
	return this->m_bHadNormalsInFile;
}


void ModelData::normlizeExistingNomrals(void)
{
	// Now go through all the vertices and normalize (average) them...
	std::vector<PLYVERTEX>::iterator itVert;
	for ( itVert = this->m_verticies.begin(); itVert != this->m_verticies.end(); itVert++)
	{	
		Vector3D normal( itVert->nx, itVert->ny, itVert->nz );
		normal.Normalize();
		itVert->nx = normal.x;
		itVert->ny = normal.y;
		itVert->nz = normal.z;
	}
}
// End of Added
int ModelData::GetNumberOfVerticies(void)
{
	return this->m_numberOfVertices;
}

int ModelData::GetNumberOfElements(void)
{
	return this->m_numberOfElements;
}

float ModelData::getMaxX(void)
{
	return this->m_maxX;
}

float ModelData::getMinX(void)
{
	return this->m_minX;
}

float ModelData::getDeltaX(void)
{
	return this->m_deltaX;
}

float ModelData::getMaxY(void)
{
	return this->m_maxY;
}

float ModelData::getMinY(void)
{
	return this->m_minY;
}

float ModelData::getDeltaY(void)
{
	return this->m_deltaY;
}

float ModelData::getMaxZ(void)
{
	return this->m_maxZ;
}

float ModelData::getMinZ(void)
{
	return this->m_minZ;
}

float ModelData::getDeltaZ(void)
{
	return this->m_deltaZ;
}

float ModelData::getMaxExtent(void)
{
	return this->m_maxExtent;
}


std::vector<PLYVERTEX> ModelData::getVerticies()
{
	return m_verticies ; 
}

std::vector<PLYELEMENT> ModelData::getElements()
{
	return m_elements;

}




	void ModelData::setNumberOfVerticies(int value)
	{
		m_numberOfVertices = value;
	}
	void  ModelData::setNumberOfElements(int value)
	{
		m_numberOfElements = value;
	}

	 void ModelData::setVerticies(std::vector<PLYVERTEX> value)
	 {
		 m_verticies = value;
	 }
	void ModelData::setElements(std::vector<PLYELEMENT> value)
	{
		m_elements = value;
	
	}


	 

   GLuint ModelData::getVertexBufferID()
   {
   
	   return vertexBufferID;
   }
	GLuint ModelData::getVertexAttribID()
	{
	
		return vertexAtrribID;
	}
	GLuint ModelData::getIndexID()
	{
	
		return indexID;
	}

 void ModelData::assignBuffer()
 {
    if ( !this->bHadNormalsInFile() )
	{
		this->normalize();
	}

	CVertex_fXYZW* p_arrayVertPositions = new CVertex_fXYZW[ m_numberOfVertices ];
	CVertex_fXYZW* p_arrayVertColours = new CVertex_fXYZW[ m_numberOfVertices ];
	CVertex_fXYZW* p_arrayVertNormals = new CVertex_fXYZW[ m_numberOfVertices ];

	// Copy the data from the bunny vector to this array
	for ( int vertIndex = 0; vertIndex != m_numberOfVertices; vertIndex++ )
	{
		PLYVERTEX tempVertex = this->getVertex_at( vertIndex );		

		p_arrayVertPositions[vertIndex].x = tempVertex.pos.x;
		p_arrayVertPositions[vertIndex].y = tempVertex.pos.y;
		p_arrayVertPositions[vertIndex].z = tempVertex.pos.z;
		p_arrayVertPositions[vertIndex].w = 1.0f;

		p_arrayVertColours[vertIndex].x =  color.x;	//tempVertex.red;		// Red
		p_arrayVertColours[vertIndex].y = color.y;	// 0.75f;	//tempVertex.green;		// Green
		p_arrayVertColours[vertIndex].z = color.z;// 0.65f;	//tempVertex.blue;		// Blue
		p_arrayVertColours[vertIndex].w = 1.0f;				// Alpha

		p_arrayVertNormals[vertIndex].x = tempVertex.nx;	
		p_arrayVertNormals[vertIndex].y = tempVertex.ny;	
		p_arrayVertNormals[vertIndex].z = tempVertex.nz;	
		p_arrayVertNormals[vertIndex].w = 1.0f;	

		// Normal information soon to be added
	}
 

	// Get an ID (aka "name") for the two-part vertex buffer
	glGenVertexArrays(1, &vertexBufferID );
	glBindVertexArray( vertexBufferID );
	ExitOnGLError("ERROR: Could not generate the VAO");
  
	// "Bind" them, which means they are ready to be loaded with data
	glGenBuffers(1, &vertexAtrribID );
	glBindBuffer(GL_ARRAY_BUFFER, vertexAtrribID);	
	ExitOnGLError("ERROR: Could not bind the VAO");

	int totalBufferSize = sizeof(CVertex_fXYZW) * m_numberOfVertices				/* Position */
		                  + sizeof(CVertex_fXYZW) * m_numberOfVertices				/* Colour */
						  + sizeof(CVertex_fXYZW) * m_numberOfVertices;				/* Normal */
	// Don't copy the data right now, so pass NULL
	glBufferData(GL_ARRAY_BUFFER, totalBufferSize, NULL, GL_STATIC_DRAW);
	// Now copy the data
	unsigned int offsetToPositions = 0;
	unsigned int offsetToColours = offsetToPositions + sizeof(CVertex_fXYZW) * m_numberOfVertices;
	unsigned int offsetToNormals = offsetToColours + sizeof(CVertex_fXYZW) * m_numberOfVertices;

	glBufferSubData( GL_ARRAY_BUFFER, offsetToPositions, sizeof(CVertex_fXYZW) * m_numberOfVertices, p_arrayVertPositions );
	glBufferSubData( GL_ARRAY_BUFFER, offsetToColours, sizeof(CVertex_fXYZW) * m_numberOfVertices, p_arrayVertColours );
	glBufferSubData( GL_ARRAY_BUFFER, offsetToNormals, sizeof(CVertex_fXYZW) * m_numberOfVertices, p_arrayVertNormals );
	ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>( offsetToPositions ) );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>( offsetToColours ) );
	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<GLvoid*>( offsetToNormals ) );
	ExitOnGLError("ERROR: Could not bind the VBO to the VAO");


	glEnableVertexAttribArray(0);			// Position
	glEnableVertexAttribArray(1);			// Colour
	glEnableVertexAttribArray(2);			// Normal;			// *** ADDED
	ExitOnGLError("ERROR: Could not enable vertex attributes");



	//INDEX BUFFER 

	int numberOfIndices = m_numberOfElements * 3;

	GLuint* p_Indices = new GLuint[ numberOfIndices ];

	for ( int triIndex = 0; triIndex < m_numberOfElements; triIndex++ )	// Step by three
	{
		//CTriangle tempTri = vecTriangles[triIndex];
		PLYELEMENT tempTri = this->getElement_at(triIndex);
	  
		int index1 = (triIndex * 3);
		int index2 = (triIndex * 3) + 1;
		int index3 = (triIndex * 3) + 2;

		
		p_Indices[index1] = (GLuint)tempTri.vertex_1;
		p_Indices[index2] = (GLuint)tempTri.vertex_2;
		p_Indices[index3] = (GLuint)tempTri.vertex_3;
		
	}

	
	glGenBuffers(1, &indexID );			// Get an ID (aka "name")

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);		
	ExitOnGLError("ERROR: Could not set VAO attributes");

	// Figure out how many "system units" (i.e. "bytes") the index buffer is
	// Or, how many bytes is GLuint (on this system) X number of indices
	int bytesInIndexArray = numberOfIndices * sizeof(GLuint);
	// Copy the data from the CPU RAM to the Video card RAM
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesInIndexArray, p_Indices, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the IBO to the VAO");




	// Release the "connection" to any vertex buffers
	// Release the binding on all buffers
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);		
	
	delete [] p_arrayVertPositions;
	delete [] p_arrayVertColours;
	delete [] p_arrayVertNormals;
	delete [] p_Indices;


	ExitOnGLError("ERROR: Could not set VAO attributes");


	

 
 }


  //check fileName
   std::wstring ModelData::getFileName()
   {
	   return fileName;
   }

   //check scale
   float ModelData::getScale()
   {
	   return scale;
   }


     void ModelData::setColor(Vector3D value)
	 {
	 
		 color = value;
	 }


	 //Get Color
   Vector3D ModelData::getColor()
   {
   
	   return color;
   }


   
  