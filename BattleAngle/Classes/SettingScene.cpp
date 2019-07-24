#include "SettingScene.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

ui::Slider* volumeSlider;
ui::CheckBox* checkboxSound;
ui::CheckBox* checkboxMusic;

cocos2d::Scene * SettingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingScene::create();

	scene->addChild(layer);

	return scene;
}

bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	} 
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//set background
	auto visibleSize1 = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("res/Menu_UI/bg1.png");
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setScale(0.37);
	background->setPosition(visibleSize1 / 2);
	addChild(background, -2);
	auto bg = Sprite::create("res/Setting_UI/bg.png");
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setScale(0.2);
	bg->setPosition(visibleSize1 / 2);
	addChild(bg, 0);
	auto bg1 = Sprite::create("res/Setting_UI/table.png");
	bg1->setAnchorPoint(Vec2(0.5, 0.5));
	bg1->setScale(0.2);
	bg1->setPosition(bg->getPosition());
	addChild(bg1, 2);
	auto bg2 = Sprite::create("res/Setting_UI/head.png");
	bg2->setAnchorPoint(Vec2(0.5, 0.5));
	bg2->setScale(0.2);
	bg2->setPosition(bg1->getPosition() + Vec2(0, 70));
	addChild(bg2, 3);
	//BackButton
	auto btnBack = ui::Button::create("res/Setting_UI/close.png");
	btnBack->setPosition(Vec2(visibleSize.width-btnBack->getContentSize().width -24,visibleSize.height-btnBack->getContentSize().height+70));
	btnBack->setScale(0.23);
	addChild(btnBack, 7);
	btnBack->addClickEventListener([&](Ref* event) {
		//sound click
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		//replace PlayScene
		auto gotoNext = CallFunc::create([]() {

			Director::getInstance()->replaceScene(MenuScene::createScene());

		});

		auto sequence = Sequence::create(DelayTime::create(0.00001f), gotoNext,nullptr);

		runAction(sequence);

	});

	//Sound Checkbox
	auto title = Label::createWithTTF("SOUND", "fonts/Marker Felt.ttf", 20);
	title->setPosition(visibleSize.width / 2.7, visibleSize.height - 150);
	title->setColor(Color3B::BLACK);
	addChild(title, 7);

	checkboxSound = ui::CheckBox::create("res/Setting_UI/on.png","res/Setting_UI/off.png");
	checkboxSound->retain();
	checkboxSound->setScale(0.3);
	checkboxSound->setSelected(true);
	checkboxSound->addClickEventListener([&](Ref* event)
	{
		checkboxSound->isSelected();
		if (!checkboxSound->isSelected() && !checkboxMusic->isSelected())
		{
			volumeSlider->setEnabled(false);
		}
		else
		{
			volumeSlider->setEnabled(true);
		}

	});
	checkboxSound->setPosition(Vec2(title->getPosition().x + 120, title->getPosition().y));
	checkboxSound->setEnabled(true);
	addChild(checkboxSound, 10);

	//Music checkbox
	auto title1 = Label::createWithTTF("MUSIC", "fonts/Marker Felt.ttf", 20);
	title1->setPosition(Vec2(title->getPosition()-Vec2(0,30)));
	title1->setColor(Color3B::BLACK);
	addChild(title1, 7);

	checkboxMusic = ui::CheckBox::create("res/Setting_UI/on.png", "res/Setting_UI/off.png");
	checkboxMusic->retain();
	checkboxMusic->setScale(0.3);
	checkboxMusic->setSelected(true);
	checkboxMusic->addClickEventListener([&](Ref* event)
	{
		checkboxMusic->isSelected();
		checkboxSound->isSelected();
		if (!checkboxSound->isSelected() && !checkboxMusic->isSelected())
		{
			volumeSlider->setEnabled(false);
		}
		else
		{
			volumeSlider->setEnabled(true);
		}

	});
	checkboxMusic->setPosition(Vec2(title1->getPosition().x + 120, title1->getPosition().y));
	checkboxMusic->setEnabled(true);
	addChild(checkboxMusic, 10);

	//Volume Slider
	auto title2 = Label::createWithTTF("VOLUME", "fonts/Marker Felt.ttf", 20);
	title2->setPosition(Vec2(title1->getPosition() - Vec2(0,30)));
	title2->setColor(Color3B::BLACK);
	addChild(title2, 7);

	volumeSlider = ui::Slider::create();
	volumeSlider->setScale(0.13);
	volumeSlider->loadBarTexture("res/Setting_UI/volume1.png");
	volumeSlider->loadSlidBallTextures("res/Setting_UI/rate.png", "res/Setting_UI/rate.png", "res/Setting_UI/less.png");
	volumeSlider->loadProgressBarTexture("res/Setting_UI/volume2.png");
	volumeSlider->setPosition(Vec2(title2->getPosition().x + 115, title2->getPosition().y));
	//volumeSlider->setPercent();
	volumeSlider->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	this->addChild(volumeSlider,10);


	

	return true;
}

void SettingScene::update(float deltaTime)
{
}
