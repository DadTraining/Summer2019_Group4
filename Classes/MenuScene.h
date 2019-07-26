
#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene :public cocos2d::Scene {

public:
	static cocos2d::Scene* createScene();
	bool init();
	void update(float deltaTime);
	CREATE_FUNC(MenuScene);
};



#endif // __MENU_SCENE_H__