#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "PlayGameScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"

using namespace CocosDenshion;

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
	background->setScale(0.37);
	addChild(background);

	//Music for Menu

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Music/soundMenu.mp3", true);
	//Play button
	auto btnPlay = ui::Button::create("res/Menu_UI/btn.png");
	btnPlay->setScale(0.3);
	btnPlay->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace PlayScene
			Director::getInstance()->replaceScene(PlayGameScene::createScene());
	});
	btnPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.5));
	auto title = Label::createWithTTF("PLAY", "fonts/Marker Felt.ttf", 20);
	title->setPosition(btnPlay->getPosition());
	title->setColor(Color3B::WHITE);
	addChild(title, 7);
	addChild(btnPlay);

	//Shop button
	auto btnShop = ui::Button::create("res/Menu_UI/btn.png");
	btnShop->setScale(0.3);
	btnShop->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace ShopScene
	});
	btnShop->setPosition(btnPlay->getPosition()-Vec2(0,40));
	auto title1 = Label::createWithTTF("SHOP", "fonts/Marker Felt.ttf", 20);
	title1->setPosition(btnShop->getPosition());
	title1->setColor(Color3B::WHITE);
	addChild(title1, 7);
	addChild(btnShop);

	//Exit button
	auto btnExit = ui::Button::create("res/Menu_UI/btn.png");
	btnExit->setScale(0.3);
	btnExit->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//outGame
		exit(1);

	});
	btnExit->setPosition(btnShop->getPosition()-Vec2(0,40));
	auto title2 = Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 20);
	title2->setPosition(btnExit->getPosition());
	title2->setColor(Color3B::WHITE);
	addChild(title2, 7);
	addChild(btnExit);

	//Setting button
	auto btnSetting = ui::Button::create("res/Menu_UI/setting.png");
	btnSetting->setScale(0.2);
	btnSetting->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace SettingScene
		Director::getInstance()->replaceScene(SettingScene::createScene());
	});
	btnSetting->setPosition(Vec2(visibleSize.width / 1.2, visibleSize.height / 6));
	addChild(btnSetting);

	return true;
}

void MenuScene::update(float deltaTime)
{
}
