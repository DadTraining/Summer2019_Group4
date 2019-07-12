

#ifndef __OBJECTS__
#define __OBJECTS__

#include "cocos2d.h"

USING_NS_CC;

class Objects
{
protected:
	Sprite* m_sprite;
	int m_hp;
	int m_dame;
	bool m_isAlive;


public:
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
	cocos2d::Animation* createAnimation(std::string prerfixName, int pFrameOrder, float delay);
	cocos2d::Animation *animation;
	Sprite* DuplicateSprite(Sprite * sprite);

};



#endif 