#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "PlayGameScene.h"

USING_NS_CC;

cocos2d::Scene * MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("res/Menu_UI/bg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(0.32);
	addChild(background);
	//Play button
	auto btnPlay = ui::Button::create("res/Menu_UI/play.png");
	btnPlay->setScale(0.3);
	btnPlay->addClickEventListener([&](Ref* event) {
		auto gotoNext = CallFunc::create([]() {

			Director::getInstance()->replaceScene(PlayGameScene::createScene());

		});

		auto sequence = Sequence::create(DelayTime::create(0.1), gotoNext,
			nullptr);

		runAction(sequence);

	});
	btnPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
	addChild(btnPlay);
	//Shop button
	auto btnShop = ui::Button::create("res/Menu_UI/shop.png");
	btnShop->setScale(0.3);
	btnShop->addClickEventListener([&](Ref* event) {


	});
	btnShop->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.3));
	addChild(btnShop);
	//Exit button
	auto btnExit = ui::Button::create("res/Menu_UI/exit.png");
	btnExit->setScale(0.3);
	btnExit->addClickEventListener([&](Ref* event) {


	});
	btnExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5));
	addChild(btnExit);
	//Setting button
	auto btnSetting = ui::Button::create("res/Menu_UI/setting.png");
	btnSetting->setScale(0.3);
	btnSetting->addClickEventListener([&](Ref* event) {


	});
	btnSetting->setPosition(Vec2(visibleSize.width / 1.2, visibleSize.height / 5));
	addChild(btnSetting);

	return true;
}

void MenuScene::update(float deltaTime)
{
}