#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include<iostream>


class Darts :public Objects
{
private:

public:
	bool Throwing = false;
	Darts(cocos2d::Scene* scene);
	~Darts();
	PhysicsBody * mPhysicBody;
	void Init() override;
	void Update(float deltaTime) override;
	void MoveBullet(bool isRight);
	bool Throw(Vec2 PosAlita, bool AlitaTurnRight);
};