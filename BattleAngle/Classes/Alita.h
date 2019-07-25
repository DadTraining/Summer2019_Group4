#ifndef __ALITA__
#define __ALITA__

#include "cocos2d.h"
#include "Objects.h"
#include "Darts.h"

USING_NS_CC;

class Alita : public Objects
{

public:
	//Attribute DEFAULT
	static const int RUN_STEP = 10;
	static const int ANIM_IDLE = 0;
	static const int ANIM_RUN = 1;
	static const int ANIM_JUMP = 2;
	static const int ANIM_ATTACK = 3;
	static const int ANIM_THROW = 4;
	static const int ANIM_RUN_FIRE = 5;
	static const int ANIM_JUMP_FIRE = 6;
	static const int ANIM_DAMAGE = 7;
	static const int ANIM_TOTAl = 8;
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
	void Idle();
	void MoveLeft();
	void MoveRight();
	void Jump();
	bool Attack();
	void Throw();
	void Collision();
	void BulletCollision();
	bool isRunning();
	void setRunning(bool run);
	bool isJumping();
	void setJumping(bool jump);
	Darts* getDarts();
	bool attacking = false;
private:
	bool isJump = false;
	bool isRun = false;
	Action * mAnimation[ANIM_TOTAl];
	bool isMoveRight = true;
	Darts* darts;
};



#endif 