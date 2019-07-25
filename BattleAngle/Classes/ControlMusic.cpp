#include "ControlMusic.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
ControlMusic* ControlMusic::s_instance = NULL;
ControlMusic::ControlMusic()
{
	volume = 100;
	music = true;
	sound = true;
}

ControlMusic::~ControlMusic()
{
}

ControlMusic * ControlMusic::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new ControlMusic();
	}
	return s_instance;
}

bool ControlMusic::isMusic()
{
	return music;
}

void ControlMusic::setMusic(bool music)
{
	this->music = music;
}

bool ControlMusic::isSound()
{
	return sound;
}

void ControlMusic::setSound(bool sound)
{
	this->sound = sound;
}

int ControlMusic::getVolume()
{
	return volume;
}

void ControlMusic::setVolume(int volume)
{
	this->volume = volume;
}




