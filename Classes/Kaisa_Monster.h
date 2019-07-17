#ifndef __KAISA_MONSTER__
#define __KAISA_MONSTER__

#include "cocos2d.h"
#include "Objects.h"
#include "Alita.h"

USING_NS_CC;

class Kaisa_Monster : public Objects
{
public:
	static const int ANIM_IDLE = 0;
	static const int ANIM_RUN = ANIM_IDLE + 1;
	static const int ANIM_ATTACK = ANIM_RUN + 1;
	static const int ANIM_DIE = ANIM_ATTACK + 1;
	static const int ANIM_TOTAl = ANIM_DIE + 1;

	static const int HP_KAISAMONSTER = 100;
	static const int DAME_KAISAMONSTER = 10;

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
	void BulletCollision();
	void AlitaCollision();
	void setStateKaiSa(float position);
	void setTurnKaisa(float position);

private:
	std::list<Objects*> m_bullet;
	cocos2d::Action* mAnimation[ANIM_TOTAl];
};


#endif 