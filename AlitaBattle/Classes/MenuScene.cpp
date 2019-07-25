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
	auto background = Sprite::create("res/Menu_UI/bg1.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	addChild(background);

	//Music for Menu
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Music/soundMenu.mp3", true);
	//Play button
	auto btnPlay = ui::Button::create("res/Menu_UI/btn.png");
	btnPlay->setScale(0.5);
	btnPlay->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace PlayScene
			Director::getInstance()->replaceScene(PlayGameScene::createScene());
	});
	btnPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
	auto title = Label::createWithTTF("PLAY", "fonts/Marker Felt.ttf", 30);
	title->setPosition(btnPlay->getPosition());
	title->setColor(Color3B::WHITE);
	addChild(title, 7);
	addChild(btnPlay);
	//Logo
	auto logo = Sprite::create("res/Menu_UI/logo2.png");
	logo->setScale(0.25);
	logo->setPosition(btnPlay->getPosition() + Vec2(0, 120));
	addChild(logo, 2);

   

	auto btnSetting = ui::Button::create("res/Menu_UI/setting.png");
	btnSetting->setScale(0.2);
	btnSetting->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace SettingScene
		Director::getInstance()->replaceScene(SettingScene::createScene());
	});
	btnSetting->setPosition(Vec2(visibleSize.width / 1.1, visibleSize.height / 8));
	addChild(btnSetting);

	//Shop button
	auto btnShop = ui::Button::create("res/Menu_UI/shop.png");
	btnShop->setScale(0.2);

	btnShop->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace ShopScene
	});
	btnShop->setPosition(btnSetting->getPosition()+Vec2(0,60));
	addChild(btnShop);

	////Exit button
	//auto btnExit = ui::Button::create("res/Menu_UI/btn.png");
	//btnExit->setScale(0.3);
	//btnExit->setScaleX(0.4);
	//btnExit->addClickEventListener([&](Ref* event) {
	//	//sound click
	//	auto audio = SimpleAudioEngine::getInstance();
	//	audio->playEffect("res/Music/buttonclick.mp3", false);
	//	//outGame
	//	exit(1);

	//});
	//btnExit->setPosition(btnShop->getPosition()-Vec2(0,40));
	//addChild(btnExit);

	//Setting button
	

	return true;
}

void MenuScene::update(float deltaTime)
{
}
