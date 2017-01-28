#ifndef _MODEL_DATA_CH
#define _MODEL_DATA_CH

#include <vector>
#include <string>
#include <glew.h>
#include "plyInfo.h"
//Stores all data of a model

class ModelData
{
public:
	ModelData();
	~ModelData();

	ModelData( const ModelData &rhs );	// Copy constructor
	ModelData& operator=( const ModelData &rhs );

	enum enumTEXCOORDBIAS
	{
		POSITIVE_X, POSITIVE_Y, POSITIVE_Z
	};


	// error returns the reason for failure
	bool OpenPLYFile(std::wstring fileName, std::wstring &error);
	bool SaveGDPFile(std::wstring fileName, bool bOverwrite, std::wstring &error);
	bool OpenGDPFile(std::wstring fileName, std::wstring &error);	// GDP model format (basically a binary PLY version)
	// reads only the header information (number of vertices, etc.)
	bool ReadPLYFileHeader(std::wstring fileName, std::wstring &error);
	bool ReadGDPFileHeader(std::wstring fileName, std::wstring &error);
	

	PLYVERTEX getVertex_at(std::vector<PLYVERTEX>::size_type index);
	PLYELEMENT getElement_at(std::vector<PLYELEMENT>::size_type index);
	float getMaxX(void); float getMinX(void); float getDeltaX(void);
	float getMaxY(void); float getMinY(void); float getDeltaY(void);
	float getMaxZ(void); float getMinZ(void); float getDeltaZ(void);
	float getMaxExtent(void);
	// *********************
	
	void normalize(void);
	void normalizeDirectXVersion(void);

	
	void GenTextureCoordsSpherical( enumTEXCOORDBIAS uBias, enumTEXCOORDBIAS vBias, bool basedOnNormals, float scale, bool fast );
	
	unsigned int GetID(void);
	// Added: March 14, 2012
	bool bHadTextureCoordinatesInFile(void);
	bool bHadNormalsInFile(void);
	// Added: June 8, 2013
	void normlizeExistingNomrals(void);	
	// End of Added

	void scaleVertices( float scaleFactor );
	void calcualteExtents(void);

    std::vector<PLYVERTEX> getVerticies();
	std::vector<PLYELEMENT> getElements();

		int GetNumberOfVerticies(void);
	int GetNumberOfElements(void);

		void setNumberOfVerticies(int value);
	void  setNumberOfElements(int value);

	 void setVerticies(std::vector<PLYVERTEX>);
	void setElements(std::vector<PLYELEMENT>);

	void setFileName(std::wstring name);
	
   std::wstring  getFileName();
   float getScale();

   

   GLuint getVertexBufferID();
	GLuint getVertexAttribID();
	GLuint getIndexID();

   //Assign buffers to Model
   void assignBuffer();

   //Set color 
   void setColor(Vector3D value);

   //Get Color
   Vector3D getColor();


   


private:
	std::vector<PLYVERTEX> m_verticies;
	std::vector<PLYELEMENT> m_elements;
	float m_minX, m_maxX, m_deltaX;
	float m_minY, m_maxY, m_deltaY;
	float m_minZ, m_maxZ, m_deltaZ;
	// *********************
	float m_centreX, m_centreY, m_centreZ;
	float m_maxExtent;

	int m_numberOfVertices;
	int m_numberOfElements;

	int m_totalProperties;
	int m_x_propertyIndex;
	int m_y_propertyIndex;
	int m_z_propertyIndex;
	int m_normx_propertyIndex;
	int m_normy_propertyIndex;
	int m_normz_propertyIndex;
	int m_red_propertyIndex;
	int m_green_propertyIndex;
	int m_blue_propertyIndex;

	// Added: March 14, 2012
	bool m_bHadTextureCoordinatesInFile;
	bool m_bHadNormalsInFile;
	int m_tex0u_propertyIndex;		// "u"
	int m_tex0v_propertyIndex;		// "v"
	int m_tex1u_propertyIndex;		// "tex1u"
	int m_tex1v_propertyIndex;		// "tex1v"
	int m_UNKNOWN_IGNORE_propertyIndex;		// This is used when we don't know what they heck this index is.
	// End of Added

	// 
	void m_setIndexBasedOnPropertyName(int curIndex, std::wstring propName);
	bool m_placeItemInAppropriateVertexLocation( std::wstring tempString, int propertyIndex, PLYVERTEX &tempVertex );

	unsigned int m_ID;
	static unsigned int statNextID;

	float scale;
	std::wstring fileName;

	GLuint vertexBufferID;
	GLuint vertexAtrribID;
	GLuint indexID;
	Vector3D color;
	


};



#endif