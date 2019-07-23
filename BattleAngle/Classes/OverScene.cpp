#include "OverScene.h"
#include "PlayGameScene.h"
#include "ui\UIButton.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"


using namespace CocosDenshion;
USING_NS_CC;


cocos2d::Scene * OverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = OverScene::create();

	scene->addChild(layer);

	return scene;
}

bool OverScene::init()
{
	if(!Scene::init())
	{ 
		return false;
	}
	auto visibleSize1 = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("res/Menu_UI/bg.png");
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setScale(0.37);
	background->setPosition(visibleSize1 / 2);
	addChild(background, -2);
	auto bg = Sprite::create("res/Setting_UI/bg.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setScale(0.2);
	bg->setPosition(visibleSize1 / 2);
	addChild(bg, 0);
	auto bg1 = Sprite::create("res/Lose_UI/table.png");
	bg1->setAnchorPoint(Vec2(0.5, 0.5));
	bg1->setScale(0.3);
	bg1->setPosition(bg->getPosition());
	addChild(bg1, 2);
	auto bg2 = Sprite::create("res/Lose_UI/header.png");
	bg2->setAnchorPoint(Vec2(0.5, 0.5));
	bg2->setScale(0.2);
	bg2->setPosition(bg1->getPosition() + Vec2(0, 70));
	addChild(bg2, 3);
	auto text = Sprite::create("res/Lose_UI/star_4.png");
	text->setAnchorPoint(Vec2(0.5, 0.5));
	text->setScale(0.2);
	text->setPosition(bg2->getPosition() - Vec2(0, 50));
	addChild(text, 3);
	//Button Reset

	auto btnOk = ui::Button::create("res/Lose_UI/restart.png");
	btnOk->setAnchorPoint(Vec2(0.5, 0.5));
	btnOk->setPosition(text->getPosition() - Vec2(60, 65));
	btnOk->setScale(0.2);
	addChild(btnOk, 7);
	btnOk->addClickEventListener([&](Ref* event) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		setVisible(false);
		Director::getInstance()->replaceScene(PlayGameScene::createScene());
	});
	//Button Menu

	auto btnMenu = ui::Button::create("res/Lose_UI/menu.png");
	btnMenu->setAnchorPoint(Vec2(0.5, 0.5));
	btnMenu->setPosition(btnOk->getPosition() + Vec2(116, 0));
	btnMenu->setScale(0.2);
	addChild(btnMenu, 7);
	btnMenu->addClickEventListener([&](Ref* event) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	return true;
}

void OverScene::update(float deltaTime)
{
}
