#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
#include "Alita.h"

class PlayGameScene : public cocos2d::Scene
{
private:
	Alita* m_Alita;
	TMXLayer* Lane;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void createController();
	void createMap();
	void createPhysic();

	void update(float detaTime);
	CREATE_FUNC(PlayGameScene);
};

#endif // __PLAYGAME_SCENE_H__