#include "SimpleAudioEngine.h"

#include "PlayGameScene.h"
#include "ui\UIButton.h"

USING_NS_CC;

Scene* PlayGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = PlayGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool PlayGameScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	auto ScreenSize = Director::getInstance()->getVisibleSize();
	

	createController();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto egdeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	egdeBody->setDynamic(false);
	auto egdeNode = Node::create();
	egdeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	egdeNode->setPhysicsBody(egdeBody);
	addChild(egdeNode);
	m_Alita = new Alita(this);
	createPhysic();
	scheduleUpdate();
	return true;
}

void PlayGameScene::createController()
{
	auto ScreenSize =	Director::getInstance()->getVisibleSize();
	//Move right button
	auto MoveRightButton = ui::Button::create("res/Main_UI/right.png",
		"res/Main_UI/right.png");
	MoveRightButton->addClickEventListener([&](Ref* event) {
		m_Alita->MoveRight();
	});
	MoveRightButton->setAnchorPoint(Vec2(1, 0));
	MoveRightButton->setPosition(Vec2(ScreenSize.width / 3, ScreenSize.height / 5));
	addChild(MoveRightButton);

	//Move left button
	auto MoveLeftButton = ui::Button::create("res/Main_UI/left.png",
		"res/Main_UI/left.png");
	MoveLeftButton->addClickEventListener([&](Ref* event) {
		m_Alita->MoveLeft();
	});

	MoveLeftButton->setAnchorPoint(Vec2(1, 0));
	MoveLeftButton->setPosition(Vec2(ScreenSize.width / 3 - 70, ScreenSize.height / 5));
	addChild(MoveLeftButton);

	//Jump button
	auto JumpButton = ui::Button::create("res/Main_UI/jump.png",
		"res/Main_UI/jump.png");
	JumpButton->addClickEventListener([&](Ref* event) {
		m_Alita->Attack();
	});
	JumpButton->setAnchorPoint(Vec2(1, 0));
	JumpButton->setPosition(Vec2(ScreenSize.width / 5 * 4, ScreenSize.height / 5));
	addChild(JumpButton);
}

void PlayGameScene::createMap()
{
}

void PlayGameScene::createPhysic(){
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto egdeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		egdeBody->setDynamic(false);
		auto egdeNode = Node::create();
		egdeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		egdeNode->setPhysicsBody(egdeBody);
		addChild(egdeNode);

		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto map = TMXTiledMap::create("TileMap/TileMap.tmx");
		map->setAnchorPoint(Vec2(0, 0));
		map->setPosition(0, 0);

		Lane = map->getLayer("lane");
		Size layerSize = Lane->getLayerSize();
		for (int i = 0; i < layerSize.width; i++)
		{
			for (int j = 0; j < layerSize.height; j++)
			{
				auto tileSet = Lane->getTileAt(Vec2(i, j));
				if (tileSet != NULL)
				{
					auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
					/*physics->setCollisionBitmask(Model::BITMASK_GROUND);
					physics->setContactTestBitmask(true);*/
					physics->setDynamic(false);
					tileSet->setPhysicsBody(physics);
				}
			}
		}
		addChild(map, -1);
}

//void PlayGameScene::createMap()
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto tileMap = TMXTiledMap::create("TileMap/TileMap.tmx");
//	addChild(tileMap,-10);
//	Lane = tileMap->getLayer("lane");
//	
//	//World
//	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
//	edgeBody->setCollisionBitmask(0);
//	edgeBody->setContactTestBitmask(true);
//
//
//	auto edgeNode = Node::create();
//	edgeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//	edgeNode->setPhysicsBody(edgeBody);
//	addChild(edgeNode);
//
//	//Lane
//}



void PlayGameScene::update(float detaTime)
{
	m_Alita->Update(detaTime);
}
