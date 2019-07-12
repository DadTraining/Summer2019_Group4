#ifndef __ALITA__
#define __ALITA__

#include "cocos2d.h"
#include "Objects.h"

USING_NS_CC;

class Alita : public Objects
{

public:
	//Attribute

	static const int RUN_STEP = 10;
	static const int ANIM_IDLE = 0;
	static const int ANIM_RUN = 1;
	static const int ANIM_JUMP = 2;
	static const int ANIM_IDLE_FIRE = 3;
	static const int ANIM_RUN_FIRE = 4;
	static const int ANIM_JUMP_FIRE = 5;
	static const int ANIM_DAMAGE = 6;
	static const int ANIM_TOTAl = 7;
	static const int BLOOD_MAX = 100;

	static const int STATE_START = 0;
	static const int STATE_RUN = 1;
	static const int STATE_JUMP = 2;
	static const int STATE_FIRE = 3;
	static const int STATE_DAMAGE = 4;

	Alita(Scene* scene);
	~Alita();

	void Init();
	void createAnimate();
	void Update(float deltaTime);
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Attack();
	void Throw();
	void Collision();
	bool isRunning();
	bool setRunning(bool run);
private:
	bool isRun= false;
	Action * mAnimation[ANIM_TOTAl];
	Action *di;
	bool isMoveRight = true;
};



#endif 