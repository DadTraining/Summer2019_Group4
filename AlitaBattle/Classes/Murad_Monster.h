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

	Murad_Monster(Scene * scene);
	~Murad_Monster();
	void Init() override;
	void Update(float xAlita) override;
	void Idle();
	void Run();
	void Attack();
	void Die();
	void setTurnRight();
	void setTurnLeft();
	bool getm_LetftoRight();
	void setState_Murad(float position);
	void setTurn_Murad(float position);
	void Collision();

private:
	cocos2d::Action* mAnimation[ANIM_TOTAl];
	int FPS = 0;
};

#pragma once