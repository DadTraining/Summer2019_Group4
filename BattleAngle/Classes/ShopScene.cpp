#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "PlayGameScene.h"
#include "SimpleAudioEngine.h"
#include "ShopScene.h"
#include "sstream"
#include "SaveBloodGold.h"

using namespace CocosDenshion;
using namespace std;


USING_NS_CC;



Sprite* spriteNew;
cocos2d::Scene * ShopScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ShopScene::create();

	scene->addChild(layer);

	return scene;
}

bool ShopScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	createBackground();
	createPageView();
	//Gold
	goldFrame = Sprite::create("goldFrame.png");
	goldFrame->setPosition(Vec2(visibleSize.width / 1.3, visibleSize.height / 1.1));
	goldFrame->setScale(0.7);
	tempCount1 = CCString::createWithFormat("%i", SaveBloodGold::GetInstance()->getGold());
	labelGold = Label::createWithTTF(tempCount1->getCString(), "fonts/Marker Felt.ttf", 20);
	labelGold->setColor(Color3B::YELLOW);
	labelGold->setPosition(goldFrame->getPosition() + Vec2(10, 0));
	addChild(labelGold, 21);
	addChild(goldFrame, 20);

	return true;
}

void ShopScene::update(float deltaTime)
{

}

void ShopScene::createBackground()
{
	//background
	auto background = Sprite::create("res/Menu_UI/bg1.png");
	background->setAnchorPoint(Vec2(0.5, 0.5));
	background->setPosition(visibleSize / 2);
	addChild(background);

	//label shop
	auto label = cocos2d::Sprite::create("res/shop/shop.png");
	label->setAnchorPoint(Vec2(0.5, 1));
	label->setScale(0.2);
	label->setPosition(visibleSize.width / 2, visibleSize.height);
	addChild(label, 20);
}

void ShopScene::createPageView()
{
	pageView = ui::PageView::create();
	pageView->setAnchorPoint(Vec2(0.5, 0.5));
	pageView->setPosition(visibleSize / 2);
	pageView->setContentSize(visibleSize);
	pageView->setDirection(ui::PageView::Direction::HORIZONTAL);
	pageView->setMagneticType(ui::ListView::MagneticType::CENTER);
	pageView->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
	pageView->setBounceEnabled(true);
	pageView->setGlobalZOrder(200);

	addChild(pageView);

	for (std::list<Item*>::iterator it = MyItems::GetInstance()->ListItems.begin(); it != MyItems::GetInstance()->ListItems.end(); it++) {
		(*it)->getSprite()->retain();
		createLayout(pageView, (*it)->getSprite());
	}
}

void ShopScene::createLayout(ui::PageView * pageView, Sprite * sprite)
{
	page = ui::Layout::create();
	page->setContentSize(pageView->getContentSize());
	page->setPosition(visibleSize / 2);

	mySprite = cocos2d::Sprite::create("res/shop/4.png");
	mySprite->setScale(0.5);
	mySprite->setPosition(visibleSize / 2);
	page->addChild(mySprite);

	sprite->setScale(0.35);
	sprite->setPosition(visibleSize / 2);
	page->addChild(sprite, 10);
	sprite->retain();
	//Button buy
	button_Buy = cocos2d::ui::Button::create("res/shop/btn.png", "res/shop/btn.png");
	button_Buy->setScale(0.3);
	button_Buy->setAnchorPoint(Vec2(0, 0.5));
	button_Buy->setPosition(Vec2(visibleSize.width / 2, 20));
	button_Buy->addTouchEventListener(CC_CALLBACK_2(ShopScene::buy, this));
	page->addChild(button_Buy, 10);

	goldFrame = Sprite::create("buygold.png");
	goldFrame->setPosition(Vec2(button_Buy->getPosition().x - 30 + button_Buy->getContentSize().width*0.3 / 2, 2 + button_Buy->getPosition().y));
	goldFrame->setScale(0.1);

	int goldCur = 0;
	for (std::list<Item*>::iterator it = MyItems::GetInstance()->ListItems.begin(); it != MyItems::GetInstance()->ListItems.end(); it++) {
		if ((*it)->getId() == index + 1) {
			goldCur = (*it)->getGold();
		}
	}
	tempCount1 = CCString::createWithFormat("%i", goldCur);
	labelGold = Label::createWithTTF(tempCount1->getCString(), "fonts/Marker Felt.ttf", 20);
	labelGold->setColor(Color3B::YELLOW);
	labelGold->setPosition(goldFrame->getPosition() + Vec2(30, 0));
	page->addChild(labelGold, 21);
	page->addChild(goldFrame, 20);
	//button use
	button_Use = cocos2d::ui::Button::create("res/shop/btn.png", "res/shop/btn.png");
	button_Use->setScale(0.3);
	button_Use->setAnchorPoint(Vec2(1, 0.5));
	button_Use->setPosition(Vec2(visibleSize.width / 2, 20));
	button_Use->addTouchEventListener(CC_CALLBACK_2(ShopScene::use, this));
	page->addChild(button_Use, 10);

	title = Label::createWithTTF("USE", "fonts/Marker Felt.ttf", 15);
	title->setPosition(Vec2(button_Use->getPosition().x - button_Use->getContentSize().width*0.3 / 2, button_Use->getPosition().y));
	page->addChild(title, 10);
	//button back
	auto btnBack = ui::Button::create("res/Lose_UI/restart.png");
	btnBack->setPosition(Vec2(visibleSize.width*0.9, 20));
	btnBack->setScale(0.15);
	btnBack->addClickEventListener([&](Ref* event) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/buttonclick.mp3", false);
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	page->addChild(btnBack, 30);

	pageView->insertPage(page, index);
	index++;
}
void ShopScene::updateLabel()
{
	tempCount1 = CCString::createWithFormat("%i", SaveBloodGold::GetInstance()->getGold());
	labelGold->setString(tempCount1->getCString());

}

void ShopScene::buy(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;
	case ui::Widget::TouchEventType::ENDED:

		int goldCur = 0;
		for (std::list<Item*>::iterator it = MyItems::GetInstance()->ListItems.begin(); it != MyItems::GetInstance()->ListItems.end(); it++) {
			if ((*it)->getId() == pageView->getCurPageIndex() + 1) {
				goldCur = (*it)->getGold();
			}
		}
		if (SaveBloodGold::GetInstance()->getGold() >= goldCur) {
			//
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("res/Music/itempickup.mp3", false);
			for (std::list<Item*>::iterator it = MyItems::GetInstance()->ListItems.begin(); it != MyItems::GetInstance()->ListItems.end(); it++) {
				if ((*it)->getId() == pageView->getCurPageIndex() + 1) {
					if ((*it)->getBuy() == false) {
						(*it)->setBuy(true);
						if ((*it)->getId() == Objects::ID_BottleBlood) {
							(*it)->setBuy(false);
							(*it)->setSum((*it)->getSum() + 1);
							log("%d", (*it)->getSum());
						}
						SaveBloodGold::GetInstance()->setGold(SaveBloodGold::GetInstance()->getGold() - (*it)->getGold());
						// Update Gold label
						updateLabel();
					}

				}
			}
		}

		break;
	}
}
void ShopScene::use(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		for (std::list<Item*>::iterator it = MyItems::GetInstance()->ListItems.begin(); it != MyItems::GetInstance()->ListItems.end(); it++) {
			(*it)->setUse(false);
			if ((*it)->getId() == pageView->getCurPageIndex() + 1) {
				if ((*it)->getBuy() == true) {
					(*it)->setUse(true);
					log("ok");
					auto audio = SimpleAudioEngine::getInstance();
					audio->playEffect("res/Music/use.wav", false);
				}
			}
		}
		break;
	case ui::Widget::TouchEventType::ENDED:
		break;
	}
}
