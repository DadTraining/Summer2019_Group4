#ifndef __PLAY_GAME_SCENE_H__
#define __PLAY_GAME_SCENE_H__

#include "cocos2d.h"
#include "Murad_Monster.h"
#include "Kaisa_Monster.h"
#include "Alita.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class PlayGameScene : public cocos2d::Scene
{
private:
	/*Attriibute Mainly*/
	Alita* m_Alita;
	Node *egdeNode;
	Point mCurrentTouchPoint;
	TMXLayer * mPhysicsLayer;
	TMXTiledMap*  map;
	TMXObjectGroup* mObjectGroup;
	PhysicsWorld *world;
	Camera *camera;
	Kaisa_Monster *kaisa;
	Murad_Monster *murad;
	std::vector<Murad_Monster*> mMurad;
	std::vector<Kaisa_Monster*> mKaisa;

	/*Another Attribute */
	float STATIC_Position_Alita;
	float x_positon_Alita;
	int mHP;

public:
	/*Methods in cocos2dx default*/
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float deltaTime);

	/* Methods using for Init*/
	void createMapPhysics();
	void createMap();
	void createPhysics();
	void createCamera();
	void createController();
	void createMC();
	void addListener();
	void createMonsters();
	void createHub();
	void createPause();

	/* Methods using for controller game*/
	cocos2d::ui::Button* mMoveLeftController;
	cocos2d::ui::Button* mMoveRightController;
	cocos2d::ui::Button* mJumpController;
	cocos2d::ui::Button* mAttackController;
	cocos2d::ui::Button* mThrowController;
	cocos2d::ui::Button* btnPause;
	cocos2d::ui::LoadingBar *mMcHudBlood;
	Sprite * hud;
	Sprite * hud_bg;
	bool onTouchBegan(Touch* touch, Event  *event);
	bool onTouchEnded(Touch* touch, Event  *event);
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	void moveLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void moveRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void jump(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void attack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void throws(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void pause(Ref* sender, ui::Widget::TouchEventType type);

	/*Methods using logic game*/
	void setPhysicsWorld(PhysicsWorld *m_world) {
		world = m_world;
	}
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	/* Methods using for update*/
	void setTurn_Monster(float xAlita);
	void updateCenterView();
	void UpdateMonster(float x_alita);

	CREATE_FUNC(PlayGameScene);
};

#endif // __PLAY_GAME_SCENE_H__