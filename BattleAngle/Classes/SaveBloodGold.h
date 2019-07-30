#pragma once
#include"cocos2d.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

class SaveBloodGold
{
private:
	static SaveBloodGold *s_instance;
	int blood, gold;

public:
	SaveBloodGold();
	~SaveBloodGold();
	static SaveBloodGold* GetInstance();
	void setBlood(int blood);
	int getBloood();
	void setGold(int gold);
	int getGold();
};