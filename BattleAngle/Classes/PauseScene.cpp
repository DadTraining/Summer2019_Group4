#include "PauseScene.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"

USING_NS_CC;

cocos2d::Scene * PauseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = PauseScene::create();

	scene->addChild(layer);

	return scene;
}

bool PauseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// set background
	auto bg = Sprite::create("res/Setting_UI/bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setScale(0.2);
	bg->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 12 + origin.y));
	addChild(bg, 0);
	auto bg1 = Sprite::create("res/Setting_UI/table.png");
	bg1->setAnchorPoint(Vec2(0, 0));
	bg1->setScale(0.2);
	bg1->setPosition(bg->getPosition() + Vec2(10, 15));
	addChild(bg1, 2);
	auto bg2 = Sprite::create("res/Pause_UI/header.png");
	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setScale(0.15);
	bg2->setPosition(bg1->getPosition() + Vec2(50, 120));
	addChild(bg2, 3);

}


void PauseScene::update(float deltaTime)
{
}