#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include<iostream>


class Bullet :public Objects
{
public:

	Bullet(cocos2d::Scene* scene);
	~Bullet();
	void Init() override;
	void Update(float deltaTime) override;
	void MoveBullet(bool isRight);
};