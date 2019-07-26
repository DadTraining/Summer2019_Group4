#ifndef __KAISA_MONSTER__
#define __KAISA_MONSTER__

#include "cocos2d.h"
#include "Objects.h"
#include "Alita.h"
#include "Bullet.h"

USING_NS_CC;

class Kaisa_Monster : public Objects
{
private:
	int FPSKaisa = 0;
	Bullet* bullet;
	cocos2d::Action* mAnimation[4];
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