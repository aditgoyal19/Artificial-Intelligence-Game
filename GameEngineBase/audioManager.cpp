#include "audioManager.h"


Audio::Audio()
{
   c=0;
   
}

Audio::~Audio()
{
		///////================================releasing of all the sounds and effects been loaded=============/////////////
	for (int i = 0; i < g_sounds.size(); i++)
	{

		FMODERRORCHECK(g_sounds[i]->release());
	}


	///////================================= releasing of the system ================================//////////////////
      FMODERRORCHECK(system->release());



}


bool Audio::FMODERRORCHECK(FMOD_RESULT result, std::wstring &errorDetails)
{
	if (result != FMOD_OK)
	{
		std::wstringstream ss;
		ss << FMOD_ErrorString(result);
		errorDetails = ss.str();
		return false;
	}
	return true;

}
bool Audio::FMODERRORCHECK(FMOD_RESULT result)
{
	std::wstring error;
	return FMODERRORCHECK(result, error);

}

bool Audio::initFMOD()
{
	std::wstring error;
		//FMOD::System *system;
	FMOD_RESULT result;
	//unsigned int version;
	//int numdrivers;
	//FMOD_SPEAKERMODE speakermode;
	//FMOD_CAPS caps;
	char local_name[256];
	/*
	Create a System object and initialize.
	*/
	result = FMOD::System_Create(&(system));
	if (!FMODERRORCHECK(result, error))	return false;

	result = system->getVersion(&(version));
	if (!FMODERRORCHECK(result, error))	return false;

	if (version < FMOD_VERSION)
	{
		std::wstringstream ss;
		ss << "Error! You are using an old version of FMOD " << version
			<< ". This program requires " << FMOD_VERSION;
		error = ss.str();
		return false;
	}

	result = system->getNumDrivers(&(numdrivers));
	if (!FMODERRORCHECK(result, error))	return false;

	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if (!FMODERRORCHECK(result, error))	return false;
	}
	else
	{
		// ** There's an error in the documentation for this... **
		result = system->getDriverCaps(0, &(caps), 0, &(speakermode));
		if (!FMODERRORCHECK(result, error))	return false;
		/*
		Set the user selected speaker mode.
		*/
		result = system->setSpeakerMode(speakermode);
		if (!FMODERRORCHECK(result, error))	return false;

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			/*
			The user has the 'Acceleration' slider set to off! This is really bad
			for latency! You might want to warn the user about this.
			*/
			result = system->setDSPBufferSize(1024, 10);
			if (!FMODERRORCHECK(result, error))	return false;
		}
		result = system->getDriverInfo(0,local_name, 256, 0);
		if (!FMODERRORCHECK(result, error))	return false;

		if (strstr(local_name, "SigmaTel"))
		{
			/*
			Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
			PCM floating point output seems to solve it.
			*/
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0,
				FMOD_DSP_RESAMPLER_LINEAR);
			if (!FMODERRORCHECK(result, error))	return false;
		}
	}
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		/*
		Ok, the speaker mode selected isn't supported by this soundcard. Switch it
		back to stereo...
		*/
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if (!FMODERRORCHECK(result, error))	return false;
		/*
		... and re-init.
		*/
		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}
	if (!FMODERRORCHECK(result, error))	return false;

	// Copylocal_name char array to  wstring
	std::wstringstream ss;
	ss <<local_name;
	name = ss.str();

	//creates Fmod sounds and channels
	createFMODSound(error);
	// Audio::g_channels[c]->setPaused(true);
	//g_channels[c]->setPaused(false);
	// All is well
	return true;
}

bool Audio::loadSound(std::string Type, std::wstring fileName)
{
	if(Type == "STREAM")
	{
		stream.push_back(fileName);
	}
	else if(Type == "SAMPLE")
	{
		sample.push_back(fileName);
	
	}

	return true;
}

bool Audio::switchStream(int index)
{
	if (c != -1)
	 g_channels[c]->setPaused(true);
	
	c = index;
	g_channels[c]->setPaused(false);


	return true;
}

bool Audio::pauseStream(int index)
{

	c = index;
	g_channels[c]->setPaused(true);


	return true;
}

bool Audio::playSample(int index)
{

	system->playSound(FMOD_CHANNEL_FREE, g_sounds[index + stream.size()], false, 0);
	return true;
}

bool Audio::createFMODSound(std::wstring &error)
{
	FMOD_RESULT FMODResult;
	std::wstringstream ssErrors;
	bool bAllOK = true;



	for (int i = 0; i < stream.size(); i++)
	{

		char str[100];
		std::wcstombs(str, stream[i].c_str(), 100);
		FMOD::Sound* temp;
		FMODResult = system->createStream(str, FMOD_DEFAULT, 0, &temp);
		g_sounds.push_back(temp);
		if (!FMODERRORCHECK(FMODResult, error))
		{
			ssErrors << error << std::endl;
			bAllOK = false;
		}
	}


	for (int i = 0; i < sample.size(); i++)
	{
		char sam[100];
		std::wcstombs(sam, sample[i].c_str(), 100);

		FMOD::Sound* temp;
		//FMODResult = system->createSound(sam, FMOD_DEFAULT, 0, &(g_sounds[sample.size() + i]));
		FMODResult = system->createSound(sam, FMOD_DEFAULT, 0, &temp);
		g_sounds.push_back(temp);
		if (!FMODERRORCHECK(FMODResult, error))
		{
			ssErrors << error << std::endl;
			bAllOK = false;
		}



	}


   for (int i = 0; i < stream.size(); i++)
	{
		FMOD::Channel* temp;
		//FMODResult = system->playSound(FMOD_CHANNEL_FREE, g_sounds[i], true, &(g_channels[i]));
		FMODResult = system->playSound(FMOD_CHANNEL_FREE, g_sounds[i], true, &temp);
		Audio::g_channels.push_back(temp);
		FMODERRORCHECK(FMODResult);
		Sleep(1000);  //Channel needs time to loads (Dont know why)
		Audio::g_channels[i]->setChannelGroup(channelMusic);
	}
	//std::cout<< "All sounds loaded "<<std::endl;

		error = ssErrors.str();
		return bAllOK;

}