#pragma once
#include "Objects.h"
class Murad_Monster : public Objects
{
public:

	static const int ANIM_IDLE = 0;
	static const int ANIM_RUN = ANIM_IDLE + 1;
	static const int ANIM_ATTACK = ANIM_RUN + 1;
	static const int ANIM_DIE = ANIM_ATTACK + 1;
	static const int ANIM_TOTAl = ANIM_DIE + 1;
	
	static const int HP_MURADMONSTER = 100;
	static const int DAME_MURADMONSTER = 10;

	Murad_Monster(Scene * scene);
	~Murad_Monster();
	void Init() override;
	void Update(float deltaTime) override;
	void Idle();
	void Run();
	void Attack();
	void Die();
	void setTurnRight();
	void setTurnLeft();
	void Collision();

private:
	cocos2d::Action* mAnimation[ANIM_TOTAl];
	bool isRun = false;
};

#pragma once
