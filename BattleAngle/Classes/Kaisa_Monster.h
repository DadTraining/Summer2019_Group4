

#ifndef __KAISA_MONSTER__
#define __KAISA_MONSTER__

#include "cocos2d.h"
#include "Objects.h"
#include "Alita.h"

USING_NS_CC;

class Kaisa_Monster : public Objects
{
public:
	Kaisa_Monster(Scene* scene);
	~Kaisa_Monster();
	void Shoot();
	void Init() override;
	void Update(float deltaTime) override;
	void Run();
	void Attack();
	void Idle();
	void Die();
	void setTurnRight();
	void setTurnLeft();
private:
	std::list<Objects*> m_bullet;
	cocos2d::Action* m_Animation[3];

public:
	static const int HP_KAISAMONSTER = 100;
	static const int DAME_KAISAMONSTER = 10;
	
};


#endif 
