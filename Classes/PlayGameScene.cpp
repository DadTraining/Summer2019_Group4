#include "PlayGameScene.h"

#include "ui\UIButton.h"

USING_NS_CC;

Size visibleSize;
Camera *camera;

Scene* PlayGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = PlayGameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer, 0);
	return scene;
}
bool PlayGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
	createMapPhysics();
	addListener();
	createController();
	m_Alita = new Alita(this);
	x_positon_Alita = m_Alita->getSprite()->getPosition().x;
	Murad_Monster* murad = new Murad_Monster(this);

	camera = Camera::create();
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	camera->setAnchorPoint(Vec2(1, 1));
	camera->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	camera->setCameraFlag(CameraFlag::USER1);
	addChild(camera);
	scheduleUpdate();
	/*auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayGameScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this)*/;
	return true;
}

void PlayGameScene::update(float deltaTime) {
	m_Alita->Update(deltaTime);
	auto x_alita = m_Alita->getSprite()->getPosition().x;
	camera->setPosition(camera->getPosition().x + (x_alita-x_positon_Alita), visibleSize.height / 2);
	mMoveLeftController->setPosition(Vec2(mMoveLeftController->getPosition().x+ (x_alita - x_positon_Alita),mMoveLeftController->getPosition().y));
	mMoveRightController->setPosition(Vec2(mMoveRightController->getPosition().x + (x_alita - x_positon_Alita), mMoveRightController->getPosition().y));
	mJumpController->setPosition(Vec2(mJumpController->getPosition().x + (x_alita - x_positon_Alita), mJumpController->getPosition().y));
	x_positon_Alita = x_alita;

}



void PlayGameScene::createMapPhysics() {
	auto egdeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	egdeBody->setDynamic(false);
	auto egdeNode = Node::create();
	egdeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	egdeNode->setPhysicsBody(egdeBody);
	addChild(egdeNode);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map = TMXTiledMap::create("res/map/alita.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);

	auto mPhysicsLayer = map->getLayer("Layer 1");
	Size layerSize = mPhysicsLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = mPhysicsLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				/*physics->setCollisionBitmask(Model::BITMASK_GROUND);
				physics->setContactTestBitmask(true);*/
				physics->setDynamic(false);
				//physics->setMass(100);
				tileSet->setPhysicsBody(physics);
			}
		}
	}
	addChild(map, -1);
}
void PlayGameScene::addListener()
{
	//touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayGameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PlayGameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PlayGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//key
	/*auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayGameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayGameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

	//add contact event listener
	/*auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(InGameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);*/
}
bool PlayGameScene::onTouchBegan(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	return true;
}

void PlayGameScene::onTouchMoved(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
	mCurrentTouchPoint = touch->getLocation();
	log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
}

void PlayGameScene::onTouchEnded(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
}

void PlayGameScene::createController()
{
	auto ScreenSize = Director::getInstance()->getVisibleSize();
	//MoveLeft
	/*mMoveLeftController = Sprite::create("res/Main_UI/left.png");
	mMoveLeftController->setAnchorPoint(Vec2(0, 0));
	mMoveLeftController->setPosition(Vec2(50, 50));
	addChild(mMoveLeftController);
	mMoveLeftControllerPressed = Sprite::create("res/Main_UI/left.png");
	mMoveLeftControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveLeftControllerPressed->setPosition(mMoveLeftController->getPosition());
	mMoveLeftControllerPressed->setVisible(false);
	addChild(mMoveLeftControllerPressed);*/
	mMoveLeftController = ui::Button::create("res/Main_UI/left.png", "res/Main_UI/left.png");
	mMoveLeftController->setPosition(Vec2(80, 80));
	mMoveLeftController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::moveLeft, this));
	addChild(mMoveLeftController);
	//MoveRight
	mMoveRightController = ui::Button::create("res/Main_UI/left.png", "res/Main_UI/left.png");
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width, 0));
	mMoveRightController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::moveRight, this));
	addChild(mMoveRightController);
	/*mMoveRightController = Sprite::create("res/Main_UI/left.png");
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setAnchorPoint(Vec2(0, 0));
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width, 0));
	addChild(mMoveRightController);
	mMoveRightControllerPressed = Sprite::create("res/Main_UI/left.png");
	mMoveRightControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveRightControllerPressed->setFlippedX(true);
	mMoveRightControllerPressed->setPosition(mMoveRightController->getPosition());
	mMoveRightControllerPressed->setVisible(false);
	addChild(mMoveRightControllerPressed);*/
	//Jump
	mJumpController = ui::Button::create("res/Main_UI/jump.png", "res/Main_UI/jump.png");
	mJumpController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width + 10, mJumpController->getContentSize().height + 50));
	mJumpController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::jump, this));
	addChild(mJumpController);
}

void PlayGameScene::moveRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->MoveRight();
		
		break;
	case ui::Widget::TouchEventType::ENDED:
		m_Alita->setRunning(false);
		m_Alita->getSprite()->stopAllActions();
		break;
	}

	
}

void PlayGameScene::moveLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->MoveLeft();

		//camera->setPosition(camera->getPosition().x - 1, visibleSize.height / 2);
		break;
	case ui::Widget::TouchEventType::ENDED:
		m_Alita->setRunning(false);
		m_Alita->getSprite()->stopAllActions();
		break;
	}
}
void PlayGameScene :: jump(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->Jump();
		break;
	}
}

//bool PlayGameScene::onTouchBegan(Touch *touch, Event *unused_event) {
//	auto Alita_Position = m_Alita->getSprite()->getPosition().x;
//	if (Alita_Position > visibleSize.width/2) {
//		camera->setPosition(camera->getPosition().x+(Alita_Position-visibleSize.width/2), visibleSize.height/2);
//	}
//	else {
//
//	}
//	
//	return true;
//}