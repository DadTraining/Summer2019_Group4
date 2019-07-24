#ifndef __OBJECTS__
#define __OBJECTS__

#include "cocos2d.h"

USING_NS_CC;


class Objects
{
public:
	static const int BITMASK_WOLRD = 0;
	static const int BITMASK_ALITA = BITMASK_WOLRD + 1;
	static const int BITMASK_KAISA = BITMASK_ALITA + 1;
	static const int BITMASK_GROUND = BITMASK_KAISA + 1;
	static const int BITMASK_BULLET = BITMASK_GROUND + 1;
	static const int BITMASK_DART = BITMASK_BULLET + 1;
	static const int BITMASK_MURAD = BITMASK_DART + 1;


	static const int ALITA_DAME = 10;
	static const int ALITA_HP = 400;
	static const int KAISA_DAME = 10;
	static const int KAISA_HP = 30;
	static const int MURAD_DAME = 10;
	static const int MURAD_HP = 40;
protected:
	Sprite* m_sprite;

	int m_hp;
	int m_dame;
	bool m_isAlive;


public:
	cocos2d::PhysicsBody* mPhysicBody;
	void setEnablePhySicBody(bool temp) {
		mPhysicBody->setEnabled(temp);
	}
	bool m_LefttoRight;
	Objects();
	~Objects();
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	void setSprite(Sprite* m_sprite);
	Sprite* getSprite();
	void setHP(int m_hp);
	int getHP();
	void setDame(int m_dame);
	int getDame();
	void setIndex(int index);
	int getIndex();
	bool isAlive();
	void setAlive(bool alive);
	cocos2d::Animation* createAnimation(std::string prerfixName, int pFrameOrder, float delay);
	cocos2d::Animation *animation;
	Sprite* DuplicateSprite(Sprite * sprite);

};
#endif 