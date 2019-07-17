#include "LoadingScene.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"

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
	auto bgloading = Sprite::create("res/Loading_Bar/text.png");
	bgloading->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.5 + origin.y));
	addChild(bgloading, -2);
	//Loading Bar
	auto loadingBarGB = Sprite::create("res/Loading_Bar/2.png");
	loadingBarGB->setScale(0.4);
	//loadingBarGB->setScaleX(0.9);

	loadingBarGB->setPosition(Vec2(visibleSize.width / 2, 100));

	addChild(loadingBarGB);

	static auto loadingbar = ui::LoadingBar::create("res/Loading_Bar/1.png");
	loadingbar->setPercent(0);
	loadingbar->setScale(0.4);
	loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);

	loadingbar->setPosition(loadingBarGB->getPosition());

	addChild(loadingbar);

	//update Loading Bar

	auto updateLoadingBar = CallFunc::create([]() {

		if (loadingbar->getPercent() < 100)

		{

			loadingbar->setPercent(loadingbar->getPercent() + 1);

		}

	});

	auto sequenceRunUpdateLoadingBar =
		Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.02f));

	auto repeat = Repeat::create(sequenceRunUpdateLoadingBar, 100);

	loadingbar->runAction(repeat);

	auto gotoNext = CallFunc::create([]() {

		Director::getInstance()->replaceScene(MenuScene::createScene());

	});

	auto sequence = Sequence::create(DelayTime::create(2), gotoNext,
		nullptr);

	runAction(sequence);

	return true;
}

void LoadingScene::update(float deltaTime)
{
}