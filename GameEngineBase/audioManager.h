#ifndef _AUDIO_H
#define _AUDIO_H
/*
For Audio this template uses FMOD 
*/
#include <windows.h>
#include <vector>
#include <fmod.hpp>		// For C++ (includes C header, too)
#include <fmod_errors.h>
#include <fmod_dsp.h>
#include <string>
#include <sstream>


class Audio
{
public:
	Audio();
	~Audio();

	bool FMODERRORCHECK(FMOD_RESULT result, std::wstring &errorDetails);
	bool FMODERRORCHECK(FMOD_RESULT result);

	bool initFMOD();
	bool loadSound(std::string Type , std::wstring fileName);
	bool createFMODSound(std::wstring &error);
	bool switchStream(int index);
	bool pauseStream(int index);
	bool playSample(int index);

private:
	FMOD::System* system;
	//FMOD_RESULT result;
	unsigned int version;
	int numdrivers;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS caps;
	std::wstring name;	//char name[256];


	std::vector<std::wstring> stream;
	std::vector<std::wstring> sample;
	FMOD::ChannelGroup *channelMusic;  //a channel group to control master volume
	std::vector<FMOD::Sound*>	g_sounds;// = { 0 };
	std::vector<FMOD::Channel*>  g_channels;// = { 0 };
	
	std::vector<FMOD::DSP*> g_DSPEffects;//={0};
	float volume;
	float pitch;
	float pan;
	int c;//=0;

};


#endif