#pragma once
#ifndef __OBJECTS__
#define __OBJECTS__

#include "cocos2d.h"

USING_NS_CC;

class Objects
{
public:
	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_PLAYER_BULLET = BITMASK_PLAYER + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER_BULLET + 1;
	static const int BITMASK_MONSTER = BITMASK_GROUND + 1;
	static const int BITMASK_MONSTER_BULLET = BITMASK_MONSTER + 1;
protected:
	Sprite* m_sprite;
	int m_hp;
	int m_dame;
	bool m_isAlive;
	cocos2d::Animation *animation;
	cocos2d::PhysicsBody* m_PhysicsBody;

public:
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
	cocos2d::Animation* createAnimation(std::string prerfixName, int pFrameOrder, float delay);

};



#endif 