#pragma once
#include "cocos2d.h"
#include "Objects.h"
#include<iostream>
#include <MyItems.h>
using namespace std;

class Darts :public Objects
{
private:

public:
	bool hadDart = false;
	bool Throwing = false;
	Darts(cocos2d::Scene* scene);
	~Darts();
	PhysicsBody * mPhysicBody;
	void Init() override;
	void Update(float deltaTime) override;
	void MoveBullet(bool isRight);
	bool Throw(Vec2 PosAlita, bool AlitaTurnRight);
};