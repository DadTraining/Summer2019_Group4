#pragma once
#include"cocos2d.h"

class AnimationHelper
{
private:
	static AnimationHelper *s_instance;
public:
	AnimationHelper();
	~AnimationHelper();
	cocos2d::Animation *animation;
	cocos2d::Animation* createAnimation(std::string prerfixName, int pFrameOrder, float delay);
	static AnimationHelper* GetInstance();
};