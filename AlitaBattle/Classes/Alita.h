#ifndef __ALITA__
#define __ALITA__

#include "cocos2d.h"
#include "Objects.h"

USING_NS_CC;

class Alita : public Objects
{
protected:
	Action* m_Animation;
	bool isMoveRight = true;
public:
	Alita(Scene* scene);
	~Alita();
	void Init();
	void Update(float deltaTime);
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Attack();
	void Throw();
	void Collision();
};



#endif 