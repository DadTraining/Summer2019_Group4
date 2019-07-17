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
	STATIC_Position_Alita = m_Alita->getSprite()->getPosition().x;
	x_positon_Alita = m_Alita->getSprite()->getPosition().x;
	//Murad_Monster* murad = new Murad_Monster(this);

	camera = this->getDefaultCamera();
	//this->setCameraMask((unsigned short)CameraFlag::USER1, false);
	camera->setAnchorPoint(Vec2(1, 1));
	camera->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//camera->setCameraFlag(CameraFlag::USER1);
	//addChild(camera);
	createMonsters();
	this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::UpdateMonster, 1));
	scheduleUpdate();
	
	//createObjects()
		/*auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(PlayGameScene::onTouchBegan, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this)*/;
	return true;
}

void PlayGameScene::update(float deltaTime) {
	m_Alita->Update(deltaTime);
	auto x_alita = m_Alita->getSprite()->getPosition().x;
	if (x_alita>STATIC_Position_Alita && x_alita<(map->getContentSize().width - visibleSize.width / 2)) {
		camera->setPosition(camera->getPosition().x + (x_alita - x_positon_Alita), visibleSize.height / 2);
		//egdeNode->setPosition(egdeNode->getPosition().x + (x_alita - x_positon_Alita), visibleSize.height / 2);
		mMoveLeftController->setPosition(Vec2(mMoveLeftController->getPosition().x + (x_alita - x_positon_Alita), mMoveLeftController->getPosition().y));
		mMoveRightController->setPosition(Vec2(mMoveRightController->getPosition().x + (x_alita - x_positon_Alita), mMoveRightController->getPosition().y));
		mJumpController->setPosition(Vec2(mJumpController->getPosition().x + (x_alita - x_positon_Alita), mJumpController->getPosition().y));
		mAttackController->setPosition(Vec2(mAttackController->getPosition().x + (x_alita - x_positon_Alita), mAttackController->getPosition().y));
		mThrowController->setPosition(Vec2(mThrowController->getPosition().x + (x_alita - x_positon_Alita), mThrowController->getPosition().y));

		x_positon_Alita = x_alita;
	}
	setTurn_Monster(x_alita);
}



void PlayGameScene::createMapPhysics() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map = TMXTiledMap::create("res/map/alita.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);
	mObjectGroup = map->getObjectGroup("Monster");
	auto mPhysicsLayer = map->getLayer("Lane");
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
void PlayGameScene::createMonsters() {

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
		if (type == 0)
		{
			m_Alita->getSprite()->setPosition(Vec2(posX, posY));
		}
		//else if (type == 1)
		//{
		//	Kaisa_Monster *kaisa = new Kaisa_Monster(this);
		//	kaisa->getSprite()->setPosition(Vec2(posX, posY));
		//	//murad->setIndex(monster_count++);
		//	mKaisa.push_back(kaisa);
		//}
		else if (type == 2)
		{
			Murad_Monster *murad = new Murad_Monster(this);
			murad->getSprite()->setPosition(Vec2(posX, posY));
			//murad->setIndex(monster_count++);
			mMurad.push_back(murad);
		}
	}
}
void PlayGameScene::UpdateMonster(float DeltaTime)
{
	auto PositionAlita = m_Alita->getSprite()->getPositionX();
	for (auto i : mMurad) {
		i->setState_Murad(PositionAlita);
	}
	/*for (auto i : mKaisa) {
		i->setStateKaiSa(PositionAlita);
	}*/
}
void PlayGameScene::setTurn_Monster(float xAlita)
{
	for (auto i : mMurad) {
		i->setTurn_Murad(xAlita);
	}
	/*for (auto i : mKaisa) {
		i->setTurnKaisa(xAlita);
	}*/
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
	//Jump
	mJumpController = ui::Button::create("res/Main_UI/jump.png", "res/Main_UI/jump.png");
	mJumpController->setScale(0.7);
	mJumpController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width -10, mJumpController->getContentSize().height + 70));
	mJumpController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::jump, this));
	addChild(mJumpController);
	//Attack
	mAttackController = ui::Button::create("res/Main_UI/attack.png", "res/Main_UI/attack.png");
	mAttackController->setScale(0.7);
	mAttackController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width +10, mJumpController->getContentSize().height-10));
	mAttackController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::attack, this));
	addChild(mAttackController);
	//Throw
	mThrowController = ui::Button::create("res/Main_UI/skill.png", "res/Main_UI/skill.png");
	mThrowController->setScale(0.7);
	mThrowController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width -60, mJumpController->getContentSize().height));
	mThrowController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::throws, this));
	addChild(mThrowController);
}

void PlayGameScene::moveRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->MoveRight();
		break;
	case ui::Widget::TouchEventType::ENDED:
		m_Alita->getSprite()->stopAllActions();
		m_Alita->setRunning(false);
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
		m_Alita->getSprite()->stopAllActions();
		m_Alita->setRunning(false);
		break;
	}
}
void PlayGameScene::jump(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->Jump();
		break;
	}
}

void PlayGameScene::attack(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->Attack();
		break;
	}
}

void PlayGameScene::throws(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->Throw();
		break;
	}
}
