
#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

class SettingScene :public cocos2d:: Scene {

public:
	static cocos2d::Scene* createScene();
	bool init();
	void update(float deltaTime);
	CREATE_FUNC(SettingScene);
};



#endif //  __SETTING_SCENE_H__
