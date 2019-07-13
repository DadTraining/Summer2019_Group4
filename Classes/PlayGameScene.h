#ifndef __PLAY_GAME_SCENE_H__
#define __PLAY_GAME_SCENE_H__

#include "cocos2d.h"
#include "Murad_Monster.h"
#include "Alita.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class PlayGameScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float deltaTime);
	//bool onTouchBegan(Touch *touch, Event *unused_event);
	//void onTouchMoved(Touch * touch, Event* event);
	
	bool onTouchBegan(Touch* touch, Event  *event);
	void onTouchMoved(Touch* touch, Event  *event);
	void onTouchEnded(Touch* touch, Event  *event);
	
	CREATE_FUNC(PlayGameScene);

private:
	Alita* m_Alita;
	float x_positon_Alita;
	cocos2d::ui::Button* mMoveLeftController;
	cocos2d::ui::Button* mMoveRightController;
	cocos2d::ui::Button* mJumpController;
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	cocos2d::Point mCurrentTouchPoint;
	cocos2d::TMXLayer * mPhysicsLayer;
	cocos2d::TMXTiledMap*  map;
	cocos2d::PhysicsWorld *world;
	void createMapPhysics();
	void createController();
	void addListener();
	void moveLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void moveRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void jump(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void setPhysicsWorld(PhysicsWorld *m_world) {
		world = m_world;
	}
};

#endif // __PLAY_GAME_SCENE_H__
