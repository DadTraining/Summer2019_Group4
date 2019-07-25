
#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"

class OverScene :public cocos2d::Scene {

public:
	static cocos2d::Scene* createScene();
	bool init();
	void update(float deltaTime);
	CREATE_FUNC(OverScene);
};



#endif // __OVER_SCENE_H__