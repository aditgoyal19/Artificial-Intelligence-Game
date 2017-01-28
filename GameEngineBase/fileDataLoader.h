#ifndef _FILEDATA_LOADER_H
#define _FILEDATA_LOADER_H

//#include "global.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <glew.h>
#include <vector>
#include "mediator.h"
#include "audioManager.h"

void ExitOnGLError(const char* error_message);

class FileDataLoader
{
public:
	FileDataLoader();
	~FileDataLoader();
	void loadSceneFromFileWithSinglePlayer(GameMediator* mediator ,std::vector <GameObjectBase*> &list, unsigned int &playerID, unsigned  int &bossID);
	void loadSceneFromFileWithMultiPlayer(GameMediator* mediator ,std::vector <GameObjectBase*> &list,std::vector <unsigned int> &playerList);
	void loadSoundsForFMOD(Audio* fmod);
	static GLuint LoadShader(const char* filename, GLenum shader_type);

	std::wstring ASCII_to_Unicode( std::string ASCIIstring );

private:
	//std::vector< std::string > vecModelsToLoad;
	std::string modelname;
	std::string plypath;
	float rotx, roty, rotz;
	float posx, posy, posz;
	float scale,player;
	float colr, colg, colb;


};


#endif