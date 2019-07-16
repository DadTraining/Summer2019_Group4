#include "LoadingScene.h"

USING_NS_CC;

cocos2d::Scene * LoadingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadingScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	} 
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto bgloading = Sprite::create("res/Loading_Bar/bgloading.png");
	bgloading->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(bgloading, -2);
	return true;
}

void LoadingScene::update(float deltaTime)
{
}
