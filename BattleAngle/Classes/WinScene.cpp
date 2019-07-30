#include "WinScene.h"
#include "PlayGameScene.h"
#include "ui\UIButton.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "PlayGameScene2.h"


using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * WinScene::createScene(int percentBlood)
{
	auto scene = Scene::create();
	auto layer = WinScene::create();

	scene->addChild(layer);
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("res/Menu_UI/bg1.png");
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(visibleSize / 2);
	layer ->addChild(background, -2);
	auto bg = Sprite::create("res/Win_UI/bg.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setScale(0.2);
	bg->setPosition(visibleSize / 2);
	layer->addChild(bg, 0);
	auto bg1 = Sprite::create("res/Win_UI/table.png");
	bg1->setAnchorPoint(Vec2(0.5, 0.5));
	bg1->setScale(0.2);
	bg1->setPosition(bg->getPosition()+Vec2(0,30));
	layer->addChild(bg1, 2);
	auto bg2 = Sprite::create("res/Win_UI/header.png");
	bg2->setAnchorPoint(Vec2(0.5, 0.5));
	bg2->setScale(0.2);
	bg2->setPosition(bg1->getPosition() + Vec2(0, 75));
	layer->addChild(bg2, 3);
	Sprite* text;
	//createStar
	if (percentBlood <= 50)
	{
		 text = Sprite::create("res/Win_UI/star_3.png");

	}
	else if (percentBlood >= 50 && percentBlood <= 70)
	{
		 text = Sprite::create("res/Win_UI/star_2.png");

	}
	else
	{
		 text = Sprite::create("res/Win_UI/star_1.png");
	}
	
	text->setAnchorPoint(Vec2(0.5, 0.5));
	text->setScale(0.2);
	text->setPosition(bg2->getPosition() - Vec2(0, 70));
	layer->addChild(text, 3);
	
	//Button Reset

	auto btnOk = ui::Button::create("res/Lose_UI/restart.png");
	btnOk->setAnchorPoint(Vec2(0.5, 0.5));
	btnOk->setPosition(text->getPosition() - Vec2(60, 120));
	btnOk->setScale(0.2);
	layer->addChild(btnOk, 7);
	btnOk->addClickEventListener([&](Ref* event) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(PlayGameScene::createScene());
	});
	//Button Menu

	auto btnMenu = ui::Button::create("res/Lose_UI/menu.png");
	btnMenu->setAnchorPoint(Vec2(0.5, 0.5));
	btnMenu->setPosition(btnOk->getPosition() + Vec2(116 / 2, 0));
	btnMenu->setScale(0.2);
	layer->addChild(btnMenu, 7);
	btnMenu->addClickEventListener([&](Ref* event) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	// Button Next
	auto btnNext = ui::Button::create("res/Win_UI/next.png");
	btnNext->setAnchorPoint(Vec2(0.5, 0.5));
	btnNext->setPosition(btnOk->getPosition() + Vec2(116, 0));
	btnNext->setScale(0.2);
	layer->addChild(btnNext, 7);
	btnNext->addClickEventListener([&](Ref* event) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		Director::getInstance()->replaceScene(PlayGameScene2::createScene());
	});

	return scene;
}

bool WinScene::init()
{
	if(!Scene::init())
	{ 
		return false;
	}
	
	return true;
}

void WinScene::update(float deltaTime)
{
}

