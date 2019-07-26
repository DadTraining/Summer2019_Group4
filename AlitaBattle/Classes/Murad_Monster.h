#pragma once
#include "Objects.h"
#include "Alita.h"
class Murad_Monster : public Objects
{
public:
	Murad_Monster(Scene * scene);
	~Murad_Monster();
	bool attacked = false;
	void Init() override;
	void UpdateAttack(float xAlita, Alita * alita);
	void Update(float deltaTime) override;
	void Idle();
	void Run();
	void Attack();
	void Die();
	void setTurnRight();
	void setTurnLeft();
	bool getm_LetftoRight();
	void DarkCollision();
	void setState_Murad(float position);
	void setTurn_Murad(float position);
	void Collision();

private:
	cocos2d::Action* mAnimation[4];
	int FPS = 0;
};

#pragma once