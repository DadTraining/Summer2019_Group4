
#include "SaveBloodGold.h"
using namespace CocosDenshion;

USING_NS_CC;
SaveBloodGold* SaveBloodGold::s_instance = NULL;
SaveBloodGold::SaveBloodGold()
{
	this->gold = 2000;
}

SaveBloodGold::~SaveBloodGold()
{
}

SaveBloodGold * SaveBloodGold::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new SaveBloodGold();
	}
	return s_instance;
}



void SaveBloodGold::setBlood(int blood)
{
	this->blood = blood;
}

int SaveBloodGold::getBloood()
{
	return blood;
}

void SaveBloodGold::setGold(int gold)
{
	this->gold = gold;
}

int SaveBloodGold::getGold()
{
	return gold;
}
