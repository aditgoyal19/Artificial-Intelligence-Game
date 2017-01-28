#include "fileDataLoader.h"

FileDataLoader::FileDataLoader()
{

}

FileDataLoader::~FileDataLoader()
{

}

GLuint FileDataLoader::LoadShader(const char* filename, GLenum shader_type)
{
  GLuint shader_id = 0;
  FILE* file;
  long file_size = -1;
  char* glsl_source;		// std::string shaderSourceText;

  if (NULL != (file = fopen(filename, "rb")) &&
    0 == fseek(file, 0, SEEK_END) &&
    -1 != (file_size = ftell(file)))
  {
    rewind(file);
    
    if (NULL != (glsl_source = (char*)malloc(file_size + 1)))
    {
      if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file))
      {
        glsl_source[file_size] = '\0';

        if (0 != (shader_id = glCreateShader(shader_type)))
        {
          glShaderSource(shader_id, 1, &glsl_source, NULL);
          glCompileShader(shader_id);
          ExitOnGLError("Could not compile a shader");
        }
        else
          fprintf(stderr, "ERROR: Could not create a shader.\n");
      }
      else
        fprintf(stderr, "ERROR: Could not read file %s\n", filename);

      free(glsl_source);
    }
    else
      fprintf(stderr, "ERROR: Could not allocate %i bytes.\n", file_size);

    fclose(file);
  }
  else
  {
    if (NULL != file)
      fclose(file);
    fprintf(stderr, "ERROR: Could not open file %s\n", filename);
  }

  return shader_id;
}

void FileDataLoader::loadSceneFromFileWithSinglePlayer(GameMediator* mediator  ,std::vector <GameObjectBase*> &list, unsigned  int &playerID,unsigned  int &bossID)
{
	std::ifstream daFile("external_file/scene.txt");
	// Did it open?
	if (!daFile.is_open())
	{
		//std::cout << "Can't open the file. Sorry it didn't work out.";
	}
	std::string temptext;
	
	while (daFile >> temptext)
	{
		if (temptext == "start")
			break;

	}
		int count = 0;
		while (!daFile.eof())
		{
			
			daFile >> modelname;
			

			if(modelname == "end")
				break;
		
			daFile >> plypath;
			daFile >> rotx >> roty >> rotz;
			daFile >> posx >> posy >> posz;
			daFile >> colr >> colg >> colb ;
			daFile >> scale ;
			daFile >> player;
		
			Vector3D color(colr,colg,colb);
			unsigned int ID = mediator->createObject(modelname,ASCII_to_Unicode(plypath),list, color);// ->CreateObjectByType(modelname,plypath);

			GameObjectBase* obj ;
		bool IdFound = false;
		for(int i = 0 ; i < list.size(); i ++)
		{
		if(list[i]->getID() == ID){
			obj = list[i];
			IdFound = true;
		}
		}

		mediator->UpdateObjectPositionByID(Vector3D(posx,posy,posz),obj);
		mediator->UpdateObjectRotationByID(Vector3D(rotx,roty,rotz),obj);
		//mediator->UpdateObjectColourByID(Vector3D(colr,roty,rotz),obj);
		mediator->UpdateObjectScaleByID(scale,obj);
		if(modelname == "Sphere"){
		mediator->UpdateObjectRadiusByID(scale/2,obj);
		}

		if(player == 1)
		{
		playerID = ID;
		}
		if(player == 2)
		{
		bossID = ID;
		}
		count++;	
		//std::cout <<"Game Object "<< modelname <<" "<<count<<" created"<< std::endl;
	   }
		


}


void FileDataLoader::loadSceneFromFileWithMultiPlayer(GameMediator* mediator  ,std::vector <GameObjectBase*> &list,std::vector <unsigned int> &playerList)
{
	std::ifstream daFile("external_file/scene.txt");
	// Did it open?
	if (!daFile.is_open())
	{
		//std::cout << "Can't open the file. Sorry it didn't work out.";
	}
	std::string temptext;
	
	while (daFile >> temptext)
	{
		if (temptext == "start")
			break;

	}
		int count = 0;
		while (!daFile.eof())
		{
			
			daFile >> modelname;
			

			if(modelname == "end")
				break;
		
			daFile >> plypath;
			daFile >> rotx >> roty >> rotz;
			daFile >> posx >> posy >> posz;
			daFile >> colr >> colg >> colb ;
			daFile >> scale ;
			daFile >> player;
		
			Vector3D color(colr,colg,colb);
			unsigned int ID = mediator->createObject(modelname,ASCII_to_Unicode(plypath),list, color);// ->CreateObjectByType(modelname,plypath);

			GameObjectBase* obj ;
		bool IdFound = false;
		for(int i = 0 ; i < list.size(); i ++)
		{
		if(list[i]->getID() == ID){
			obj = list[i];
			IdFound = true;
		}
		}

		mediator->UpdateObjectPositionByID(Vector3D(posx,posy,posz),obj);
		mediator->UpdateObjectRotationByID(Vector3D(rotx,roty,rotz),obj);
		mediator->UpdateModelColourByID(Vector3D(colr,roty,rotz),obj);
		mediator->UpdateObjectScaleByID(scale,obj);
		if(modelname == "Sphere"){
		mediator->UpdateObjectRadiusByID(scale/2,obj);
		}

		if(player == 1)
		{
			playerList.push_back(ID);
		}
		count++;	
		//std::cout <<"Game Object "<< modelname <<" "<<count<<" created"<< std::endl;
	   }
		


}


// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
// But this is "good enough" for now
std::wstring FileDataLoader::ASCII_to_Unicode( std::string ASCIIstring )
{
	std::wstringstream ssReturnUNICODE;
	for ( std::string::iterator itChar = ASCIIstring.begin(); itChar != ASCIIstring.end(); itChar++ )
	{
		wchar_t theChar = static_cast<wchar_t>( *itChar );
		ssReturnUNICODE << theChar;
	}
	return ssReturnUNICODE.str();
}



//For loading sounds 
void FileDataLoader::loadSoundsForFMOD(Audio* fmod)
{
	std::wifstream myFile("external_file/mysoundfile.txt");

	if (!myFile.is_open())
		return;
	
	std::wstring temptext;

	//Reads till start is found ....

	while (temptext != L"start")
	{
		std::getline(myFile, temptext);

	}

	std::wstring filename;
	bool bKeepReading = true;

	// read the stream sounds
	while (bKeepReading)
	{
		std::getline(myFile, filename);

		if (filename == L"sample")
		{
			bKeepReading = false;
			break;
		}
		//fmod->stream.push_back(filename);
		fmod->loadSound("STREAM",filename);
	
	};

	// Next value is sample sounds so store in variables

	bKeepReading = true;
	while (bKeepReading)
	{

		std::getline(myFile, filename);

		if (filename == L"end")
		{
			bKeepReading = false;
			break;
		}
		//sample[i] = filename;
		fmod->loadSound("SAMPLE",filename);
	};
	
	myFile.close();
	return;






}
