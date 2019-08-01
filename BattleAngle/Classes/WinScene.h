
#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__
#include "cocos2d.h"

class WinScene :public cocos2d::Scene {

public:
	static cocos2d::Scene* createScene(int precentBlood);
	bool init();
	void update(float deltaTime);
};



#endif // __OVER_SCENE_H__