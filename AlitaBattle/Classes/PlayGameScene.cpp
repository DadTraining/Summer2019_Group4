
#include "SimpleAudioEngine.h"

#include "PlayGameScene.h"
#include "ui\UIButton.h"

USING_NS_CC;

Scene* PlayGameScene::createScene()
{
    return PlayGameScene::create();
}

bool PlayGameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto ScreenSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2(0.5,0.5));
	background->setPosition(ScreenSize / 2);

	m_Alita = new Alita(this);
	//Move right button
	auto MoveRightButton = ui::Button::create("res/Main_UI/right.png",
		"res/Main_UI/right.png");
	MoveRightButton->addClickEventListener([&](Ref* event) {
		m_Alita->MoveRight();
	});
	MoveRightButton->setAnchorPoint(Vec2(1, 0));
	MoveRightButton->setPosition(Vec2(ScreenSize.width/3, ScreenSize.height/5));
	addChild(MoveRightButton);
	
	//Move left button
	auto MoveLeftButton = ui::Button::create("res/Main_UI/left.png",
		"res/Main_UI/left.png");
	MoveLeftButton->addClickEventListener([&](Ref* event) {
		m_Alita->MoveLeft();
	});
	MoveLeftButton->setAnchorPoint(Vec2(1, 0));
	MoveLeftButton->setPosition(Vec2(ScreenSize.width/3 - 70, ScreenSize.height / 5));
	addChild(MoveLeftButton);

	//Jump button
	auto JumpButton = ui::Button::create("res/Main_UI/jump.png",
		"res/Main_UI/jump.png");
	JumpButton->addClickEventListener([&](Ref* event) {
		m_Alita->Attack();
	});
	JumpButton->setAnchorPoint(Vec2(1, 0));
	JumpButton->setPosition(Vec2(ScreenSize.width / 5*4, ScreenSize.height / 5));
	addChild(JumpButton);
}

void PlayGameScene::update(float detaTime)
{
}

