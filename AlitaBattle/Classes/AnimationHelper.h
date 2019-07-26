#pragma once
#include"cocos2d.h"
USING_NS_CC;
class AnimationHelper
{
private:
	static AnimationHelper *s_instance;
public:
	static const int RUN_STEP = 10;
	static const int ANIM_IDLE = 0;
	static const int ANIM_RUN = 1;
	static const int ANIM_DIE = 2;
	static const int ANIM_ATTACK = 3;
	static const int ANIM_JUMP = 4;
	static const int ANIM_THROW = 5;


	Action * mAnimationAlita[5];
	Action * mAnimationKaisa[4];
	Action * mAnimationMurad[4];
	AnimationHelper();
	~AnimationHelper();
	void Init();
	cocos2d::Animation *animation;
	cocos2d::Animation* createAnimation(std::string prerfixName, int pFrameOrder, float delay);
	static AnimationHelper* GetInstance();
};