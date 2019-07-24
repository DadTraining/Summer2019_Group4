#include "PlayGameScene.h"
#include "ui\UIButton.h"

USING_NS_CC;

Size visibleSize;

Scene* PlayGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -500));
	//scene->getPhysicsWorld()->setSpeed(3);
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
	createMC();
	createHub();
	createMapPhysics();
	addListener();
	createController();
	createCamera();

	//Kaisa_Monster *kaisa = new Kaisa_Monster(this);
	//Murad_Monster *murad = new Murad_Monster(this);


	createMonsters();
	//this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::UpdateMonster, 3));
	scheduleUpdate();
	return true;
}

void PlayGameScene::update(float deltaTime) {
	auto x_alita = m_Alita->getSprite()->getPosition().x;
	m_Alita->Update(deltaTime);
	updateCenterView();
	mMcHudBlood->setPercent((m_Alita->getHP() * 100) / mHP);
	setTurn_Monster(x_alita);
	UpdateMonster(x_alita);
}



void PlayGameScene::createMapPhysics() {
	
	createMap();
	createPhysics();
}
void PlayGameScene::createMap()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map = TMXTiledMap::create("res/map2/alita.tmx");
	map->setAnchorPoint(Vec2(0, 0));
	map->setPosition(0, 0);

}
void PlayGameScene::createPhysics()
{
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
				physics->setCategoryBitmask(3);
				physics->setCollisionBitmask(Objects::BITMASK_GROUND);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				//physics->setMass(100);
				tileSet->setPhysicsBody(physics);
			}
		}
	}
	addChild(map, -1);
	auto egdeBody = PhysicsBody::createEdgeBox(map->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	egdeBody->setDynamic(false);
	//egdeBody->;
	egdeNode = Node::create();
	egdeNode->setPosition(map->getContentSize().width / 2, map->getContentSize().height / 2);
	egdeNode->setPhysicsBody(egdeBody);
	addChild(egdeNode);
}
void PlayGameScene::createCamera()
{
	camera = this->getDefaultCamera();
	camera->setAnchorPoint(Vec2(1, 1));
	camera->setPosition(visibleSize.width / 2, visibleSize.height / 2);
}
void PlayGameScene::createMonsters() {

	//add effect
	auto paricleEffect = ParticleSnow::create();
	paricleEffect->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	addChild(paricleEffect);
	auto objects = mObjectGroup->getObjects();
	int kaisa_count = 0;
	int murad_count = 0;
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
		else if (type == 1)
		{
			kaisa = new Kaisa_Monster(this);
			kaisa->getSprite()->setPosition(Vec2(posX, posY));
			kaisa->setIndex(kaisa_count++);
			//kaisa->getBullet()->setIndex(kaisa_count);
			mKaisa.push_back(kaisa);
		}
		else if (type == 2)
		{
			murad = new Murad_Monster(this);
			murad->getSprite()->setPosition(Vec2(posX, posY));
			murad->setIndex(murad_count++);
			mMurad.push_back(murad);
		}
	}
}
void PlayGameScene::createHub()
{
	hud_bg = Sprite::create("res/BloodMc/hud_bg.png");
	hud_bg->setAnchorPoint(Vec2(0, 0.5));
	hud_bg->setScale(0.5);
	hud_bg->setPosition(Vec2(50, visibleSize.height - 30));
	addChild(hud_bg);

	mMcHudBlood = ui::LoadingBar::create("res/BloodMc/hud_blood.png");
	mMcHudBlood->setAnchorPoint(Vec2(0, 0.5));
	mMcHudBlood->setScale(0.5);
	mMcHudBlood->setPosition(hud_bg->getPosition());
	mMcHudBlood->setDirection(ui::LoadingBar::Direction::LEFT);
	mMcHudBlood->setPercent(m_Alita->getHP());
	addChild(mMcHudBlood);

	hud = Sprite::create("res/BloodMc/hud.png");
	hud->setAnchorPoint(Vec2(0, 0.5));
	hud->setScale(0.5);
	hud->setPosition(hud_bg->getPosition() - Vec2(12, 0));
	addChild(hud);
}
void PlayGameScene::UpdateMonster(float x_alita)
{
//	auto PositionAlita = m_Alita->getSprite()->getPositionX();
	for (auto i : mMurad) {
		i->UpdateAttack(x_alita, m_Alita);
	}
	for (auto i : mKaisa) {
		i->Update(x_alita);
	}
}
bool PlayGameScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	//dark vs mKaisa
	if ((a->getCollisionBitmask() == Objects::BITMASK_DART && b->getCollisionBitmask() == Objects::BITMASK_KAISA)
		|| (a->getCollisionBitmask() == Objects::BITMASK_KAISA && b->getCollisionBitmask() == Objects::BITMASK_DART))
	{
		if (a->getCollisionBitmask() == Objects::BITMASK_DART)
		{
			mKaisa.at(b->getGroup())->DarkCollision();
			m_Alita->getDarts()->setAlive(false);
		}
		else if (b->getCollisionBitmask() == Objects::BITMASK_DART)
		{
			mKaisa.at(a->getGroup())->DarkCollision();
			m_Alita->getDarts()->setAlive(false);
		}
	}

	//dark vs mMurad
	if ((a->getCollisionBitmask() == Objects::BITMASK_DART && b->getCollisionBitmask() == Objects::BITMASK_MURAD)
		|| (a->getCollisionBitmask() == Objects::BITMASK_MURAD && b->getCollisionBitmask() == Objects::BITMASK_DART))
	{
		if (a->getCollisionBitmask() == Objects::BITMASK_DART&& b->getContactTestBitmask()==3)
		{
			mMurad.at(b->getGroup())->DarkCollision();
			m_Alita->getDarts()->setAlive(false);
		}
		else if (b->getCollisionBitmask() == Objects::BITMASK_DART &&a->getContactTestBitmask()==3)
		{
			mMurad.at(a->getGroup())->DarkCollision();
			m_Alita->getDarts()->setAlive(false);
		}
	}

	//dark vs ground
	if ((a->getCollisionBitmask() == Objects::BITMASK_DART && b->getCollisionBitmask() == Objects::BITMASK_GROUND)
		|| (a->getCollisionBitmask() == Objects::BITMASK_GROUND && b->getCollisionBitmask() == Objects::BITMASK_DART))
	{
			m_Alita->getDarts()->setAlive(false);
	}

	//bullet vs Alita 
	if ((a->getCollisionBitmask() == Objects::BITMASK_BULLET && b->getCollisionBitmask() == Objects::BITMASK_ALITA)
		|| (a->getCollisionBitmask() == Objects::BITMASK_ALITA && b->getCollisionBitmask() == Objects::BITMASK_BULLET))
	{
		if (a->getCollisionBitmask() == Objects::BITMASK_BULLET)
		{
			m_Alita->BulletCollision();
			//mKaisa.at(a->getGroup())->getBullet()->getSprite()->setVisible(false);
		}
		else if(b->getCollisionBitmask() == Objects::BITMASK_BULLET)
		{
			m_Alita->BulletCollision();
			//mKaisa.at(a->getGroup())->getBullet()->getSprite()->setVisible(false);
		}
	}
	//Attack Murad vs Alita
	if ((a->getCollisionBitmask() == Objects::BITMASK_MURAD && b->getCollisionBitmask() == Objects::BITMASK_ALITA)
		|| (a->getCollisionBitmask() == Objects::BITMASK_ALITA && b->getCollisionBitmask() == Objects::BITMASK_MURAD))
	{
		if (a->getCollisionBitmask() == Objects::BITMASK_MURAD)
		{
			if (mMurad.at(a->getGroup())->attacked) {
				m_Alita->BulletCollision();
				mMurad.at(a->getGroup())->attacked = false;
			}
		}
		else if (b->getCollisionBitmask() == Objects::BITMASK_MURAD)
		{
			if (mMurad.at(b->getGroup())->attacked) {
				m_Alita->BulletCollision();
				mMurad.at(b->getGroup())->attacked = false;
			}
		}
	}

	//Alita vs Round
	if ((a->getCollisionBitmask() == Objects::BITMASK_GROUND && b->getCollisionBitmask() == Objects::BITMASK_ALITA)
		|| (a->getCollisionBitmask() == Objects::BITMASK_ALITA && b->getCollisionBitmask() == Objects::BITMASK_GROUND))
	{
		m_Alita->setJumping(false);
	}
	return true;
}
void PlayGameScene::setTurn_Monster(float xAlita)
{
	for (auto i : mMurad) {
		i->setTurn_Murad(xAlita);
	}
	for (auto i : mKaisa) {
		i->setTurnKaisa(xAlita);
	}
}
void PlayGameScene::updateCenterView()
{
	auto x_alita = m_Alita->getSprite()->getPosition().x;
	if (x_alita>STATIC_Position_Alita && x_alita<(map->getContentSize().width - visibleSize.width / 2)) {
		camera->setPosition(camera->getPosition().x + (x_alita - x_positon_Alita), visibleSize.height / 2);
		//egdeNode->setPosition(egdeNode->getPosition().x + (x_alita - x_positon_Alita), visibleSize.height / 2);
		mMoveLeftController->setPosition(Vec2(mMoveLeftController->getPosition().x + (x_alita - x_positon_Alita), mMoveLeftController->getPosition().y));
		mMoveRightController->setPosition(Vec2(mMoveRightController->getPosition().x + (x_alita - x_positon_Alita), mMoveRightController->getPosition().y));
		mJumpController->setPosition(Vec2(mJumpController->getPosition().x + (x_alita - x_positon_Alita), mJumpController->getPosition().y));
		mAttackController->setPosition(Vec2(mAttackController->getPosition().x + (x_alita - x_positon_Alita), mAttackController->getPosition().y));
		mThrowController->setPosition(Vec2(mThrowController->getPosition().x + (x_alita - x_positon_Alita), mThrowController->getPosition().y));
		
		hud_bg->setPosition(Vec2(hud_bg->getPosition().x + (x_alita - x_positon_Alita), hud_bg->getPosition().y));
		hud->setPosition(hud_bg->getPosition() - Vec2(15, 0));
		mMcHudBlood->setPosition(hud_bg->getPosition());
		//btnPause->setPosition(Vec2(btnPause->getPosition().x + (x_alita - x_positon_Alita), btnPause->getPosition().y));
		//mPauseLayer->setPosition(Vec2(mPauseLayer->getPosition().x + (x_alita - x_positon_Alita), mPauseLayer->getPosition().y));
		x_positon_Alita = x_alita;
	}
}
void PlayGameScene::addListener()
{
	//touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayGameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PlayGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//add contact event listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayGameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
bool PlayGameScene::onTouchBegan(Touch* touch, Event  *event)
{
	//mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	return true;
}


bool PlayGameScene::onTouchEnded(Touch* touch, Event  *event)
{
	//mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
	return true;
}

void PlayGameScene::createController()
{
	auto ScreenSize = Director::getInstance()->getVisibleSize();
	//MoveLeft

	mMoveLeftController = ui::Button::create("res/Main_UI/left.png", "res/Main_UI/left.png");
	mMoveLeftController->setPosition(Vec2(80, 80));
	mMoveLeftController->setScale(0.7);
	mMoveLeftController->setOpacity(160);
	mMoveLeftController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::moveLeft, this));
	addChild(mMoveLeftController, 10);
	//MoveRight
	mMoveRightController = ui::Button::create("res/Main_UI/left.png", "res/Main_UI/left.png");
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width, 0));
	mMoveRightController->setScale(0.7);
	mMoveRightController->setOpacity(160);
	mMoveRightController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::moveRight, this));
	addChild(mMoveRightController,10);
	//Jump
	mJumpController = ui::Button::create("res/Main_UI/jump.png", "res/Main_UI/jump.png");
	mJumpController->setScale(0.7);
	mJumpController->setOpacity(160);
	mJumpController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width -10, mJumpController->getContentSize().height + 70));
	mJumpController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::jump, this));
	addChild(mJumpController, 10);
	//Attack
	mAttackController = ui::Button::create("res/Main_UI/attack.png", "res/Main_UI/attack.png");
	mAttackController->setScale(0.7);
	mAttackController->setOpacity(160);
	mAttackController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width +10, mJumpController->getContentSize().height-10));
	mAttackController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::attack, this));
	addChild(mAttackController, 10);
	//Throw
	mThrowController = ui::Button::create("res/Main_UI/skill.png", "res/Main_UI/skill.png");
	mThrowController->setScale(0.7);
	mThrowController->setOpacity(160);
	mThrowController->setPosition(Vec2(visibleSize.width - mJumpController->getContentSize().width -60, mJumpController->getContentSize().height));
	mThrowController->addTouchEventListener(CC_CALLBACK_2(PlayGameScene::throws, this));
	addChild(mThrowController, 10);
}

void PlayGameScene::createMC()
{
	m_Alita = new Alita(this);
	STATIC_Position_Alita = m_Alita->getSprite()->getPosition().x;
	x_positon_Alita = m_Alita->getSprite()->getPosition().x;
}

void PlayGameScene::moveRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		m_Alita->MoveRight();
		break;
	case ui::Widget::TouchEventType::MOVED:
		/*if (!Rect(mMoveRightController->getPositionX(), mMoveRightController->getPositionY(), mMoveRightController->getContentSize().width*3, mMoveRightController->getContentSize().height*3).containsPoint(mCurrentTouchPoint)) {
			m_Alita->getSprite()->stopAllActions();
			m_Alita->setRunning(false);
		}*/
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
	case ui::Widget::TouchEventType::MOVED:
		/*if (!Rect(mMoveRightController->getPositionX(), mMoveRightController->getPositionY(), mMoveRightController->getContentSize().width*3, mMoveRightController->getContentSize().height*3).containsPoint(mCurrentTouchPoint)) {
			m_Alita->getSprite()->stopAllActions();
			m_Alita->setRunning(false);
		}*/
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
	case ui::Widget::TouchEventType::ENDED:
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
	case ui::Widget::TouchEventType::ENDED:
		// Collision Alita vs Monster
		rectAlita = m_Alita->getSprite()->getBoundingBox();
		for (auto i : mMurad) {
			rectMonster = i->getSprite()->getBoundingBox();
			if (rectAlita.intersectsRect(rectMonster)) {
				i->DarkCollision();
			}
		}
		for (auto i : mKaisa) {
			rectMonster = i->getSprite()->getBoundingBox();
			if (rectAlita.intersectsRect(rectMonster)) {
				i->DarkCollision();
			}
		}
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
	case ui::Widget::TouchEventType::ENDED:
		break;
	}
}
