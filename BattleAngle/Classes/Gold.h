#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include<iostream>

using namespace std;
class Gold :public Objects
{
public:
	Gold(cocos2d::Scene* scene);
	~Gold();
	void Init() override;
	void Update(float deltaTime) override;
	Action* mAnimationGold;
	void GoldCollision();
};