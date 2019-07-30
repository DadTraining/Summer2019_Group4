#ifndef __PLAY_GAME_SCENE2_H__
#define __PLAY_GAME_SCENE2_H__

#include "cocos2d.h"
#include "Murad_Monster.h"
#include "Kaisa_Monster.h"
#include "Alita.h"
#include "Gold.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class PlayGameScene2 : public cocos2d::Scene
{
private:
	/*Attriibute Mainly*/
	Rect rectFlag;
	Sprite * flag;
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
	Gold *gold;
	std::vector<Murad_Monster*> mMurad;
	std::vector<Kaisa_Monster*> mKaisa;
	std::vector<Gold*> mGold;
	Sprite * hud;
	Sprite * hud_bg;
	cocos2d::ui::LoadingBar *mMcHudBlood;
	int mHP = Objects::ALITA_HP;
	Rect rectMonster;
	Rect rectAlita;
	CCString *tempCount;
	CCString *tempCount1;
	int countMonster = 0;
	Label* labelMonster;
	Label* labelGold;
	Sprite* goldFrame;
	Sprite* monsterFrame;
	int sizeMonster = 0;
	int countGold;

	Size visibleSize;
	cocos2d::Sprite* mPauseLayer;


	/*Another Attribute */
	float STATIC_Position_Alita;
	float x_positon_Alita;

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
	void createLose();
	void createWin();
	void createLabel();
	void updateKillLabel();
	void createGoldLabel();
	void updateGoldLabel();

	/* Methods using for controller game*/
	cocos2d::ui::Button* mMoveLeftController;
	cocos2d::ui::Button* mMoveRightController;
	cocos2d::ui::Button* mJumpController;
	cocos2d::ui::Button* mAttackController;
	cocos2d::ui::Button* mThrowController;
	cocos2d::ui::Button* btnPause;
	bool onTouchBegan(Touch* touch, Event  *event);
	bool onTouchEnded(Touch* touch, Event  *event);
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	void moveLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void moveRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void jump(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void attack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void throws(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/*Methods using logic game*/
	void setPhysicsWorld(PhysicsWorld *m_world) {
		world = m_world;
	}
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	/* Methods using for update*/
	void setTurn_Monster(float xAlita);
	void updateCenterView();
	void UpdateMonster(float x_alita);
	void UpdateGotoFlag();

	CREATE_FUNC(PlayGameScene2);
};

#endif // __PLAY_GAME_SCENE2_H__