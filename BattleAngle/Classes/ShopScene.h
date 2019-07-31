#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "MyItems.h"
#include "Item.h"

USING_NS_CC;

class ShopScene :public cocos2d::Scene {
	ui::PageView * pageView;
	ui::Layout* page;
	Sprite* Darts, *mySprite;
	Size visibleSize;
	Item * item;
	ui::Button * button_Buy, *button_Use;
	Label * title;
	int index = 0;
	Sprite* goldFrame;
	CCString* tempCount1;
	Label* labelGold;

public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	virtual void update(float deltaTime) override;
	void createBackground();
	void createPageView();
	void createLayout(ui::PageView* pageView, Sprite * sprite);
	void buy(Ref* sender, ui::Widget::TouchEventType type);
	void use(Ref* sender, ui::Widget::TouchEventType type);
	CREATE_FUNC(ShopScene);
};



#endif // __SHOP_SCENE_H__