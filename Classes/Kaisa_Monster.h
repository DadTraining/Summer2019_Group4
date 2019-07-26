#ifndef __KAISA_MONSTER__
#define __KAISA_MONSTER__

#include "cocos2d.h"
#include "Objects.h"
#include "Alita.h"
#include "Bullet.h"

USING_NS_CC;

class Kaisa_Monster : public Objects
{

public:
	static const int ANIM_IDLE = 0;
	static const int ANIM_RUN = ANIM_IDLE + 1;
	static const int ANIM_ATTACK = ANIM_RUN + 1;
	static const int ANIM_DIE = ANIM_ATTACK + 1;
	static const int ANIM_TOTAl = ANIM_DIE + 1;
private:
	int FPSKaisa = 0;
	Bullet* bullet;
	cocos2d::Action* mAnimation[ANIM_TOTAl];
public:
	Kaisa_Monster(Scene* scene);
	~Kaisa_Monster();
	void Init() override;
	void Update(float deltaTime) override;
	void Run();
	void Attack();
	void Shoot();
	void Idle();
	void Die();
	void setTurnRight();
	void setTurnLeft();
	bool getm_LetftoRight();
	void DarkCollision();
	void AlitaCollision();
	void setStateKaiSa(float position);
	void setTurnKaisa(float position);
	Bullet * getBullet();

};


#endif 