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

	createMapPhysics();
	addListener();
	createController();
	m_Alita = new Alita(this);
	//nho = new Kaisa_Monster(this);
	STATIC_Position_Alita = m_Alita->getSprite()->getPosition().x;
	x_positon_Alita = m_Alita->getSprite()->getPosition().x;
	

	camera = this->getDefaultCamera();
	camera->setAnchorPoint(Vec2(1, 1));
	camera->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	createMonster();
	this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::Update_Monster), 1);
	scheduleUpdate();
	
	
	return true;
}

void PlayGameScene::update(float deltaTime) {
	m_Alita->Update(deltaTime);
	auto x_alita = m_Alita->getSprite()->getPosition().x;
	if (x_alita>STATIC_Position_Alita && x_alita<(map->getContentSize().width-visibleSize.width/2)) {
		camera->setPosition(camera->getPosition().x + (x_alita - x_positon_Alita), visibleSize.height / 2);
		mMoveLeftController->setPosition(Vec2(mMoveLeftController->getPosition().x + (x_alita - x_positon_Alita), mMoveLeftController->getPosition().y));
		mMoveRightController->setPosition(Vec2(mMoveRightController->getPosition().x + (x_alita - x_positon_Alita), mMoveRightController->getPosition().y));
		mJumpController->setPosition(Vec2(mJumpController->getPosition().x + (x_alita - x_positon_Alita), mJumpController->getPosition().y));
		x_positon_Alita = x_alita;
	}
	
	//nho->setTurnKaisa(x_alita);
	for (auto i : mMurad) {
		i->setTurn_Murad(x_alita);
	}
	/*for (auto i : mKaisa) {
		i->setTurnKaisa(x_alita);
	}*/

}
void PlayGameScene::Update_Monster(float deltaTime)
{
	auto positionAlita = m_Alita->getSprite()->getPosition().x;
	for (auto i : mMurad) {
		i->setState_Murad(positionAlita);
	}
	/*for (auto i : mKaisa) {
		i->setStateKaiSa(positionAlita);
	}*/
	//nho->setStateKaiSa(positionAlita);
	
}


void PlayGameScene::createMapPhysics() {
	

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map = TMXTiledMap::create("res/map/alita.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);
	mObjectGroup = map->getObjectGroup("Murad");
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
	auto egdeBody = PhysicsBody::createEdgeBox(map->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	egdeBody->setDynamic(false);
	egdeNode = Node::create();
	egdeNode->setPosition(map->getContentSize().width / 2, map->getContentSize().height / 2);
	egdeNode->setPhysicsBody(egdeBody);
	addChild(egdeNode);
}
void PlayGameScene::createMonster() {

	//add effect
	auto paricleEffect = ParticleSnow::create();
	paricleEffect->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	addChild(paricleEffect);


	auto objects = mObjectGroup->getObjects();

	int monster_count = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asInt();
		int posY = properties.at("y").asInt();
		int type = object.asValueMap().at("type").asInt();
		/*if (type == 1)
		{
			Kaisa_Monster *kaisa = new Kaisa_Monster(this);
			kaisa->getSprite()->setPosition(Vec2(posX, posY));
			mKaisa.push_back(kaisa);

		}*/
		 if (type ==2)
		{
			Murad_Monster *murad = new Murad_Monster(this);
			murad->getSprite()->setPosition(Vec2(posX, posY));
			//murad->setIndex(monster_count++);
			mMurad.push_back(murad);
		}
	}
}
void PlayGameScene::addListener()
{
	//touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayGameScene::onTouchBegan, this);
	//touchListener->onTouchMoved = CC_CALLBACK_2(PlayGameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PlayGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
bool PlayGameScene::onTouchBegan(Touch* touch, Event  *event)
{
	//mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	//mCurrentTouchPoint = touch->getLocation();
	return true;
}


bool PlayGameScene::onTouchEnded(Touch* touch, Event  *event)
{
	//mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	//mCurrentTouchPoint = Point(-1, -1);
	return true;
}

void PlayGameScene::createController()
{
	auto ScreenSize = Director::getInstance()->getVisibleSize();
	//MoveLeft
	
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
