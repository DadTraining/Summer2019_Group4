
#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include "Kaisa_Monster.h"
#include<iostream>


class Bullet :public Objects 
{
public:
	
	Bullet(cocos2d::Scene* scene);
	Bullet();
	~Bullet();
	void Init() override;
	void Update(float deltaTime) override;


};