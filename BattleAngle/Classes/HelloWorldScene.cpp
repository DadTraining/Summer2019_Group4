

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Bullet.h"

USING_NS_CC;
Size visibleSize;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	createMapPhysics();
	createHubAlita();
	kaisa = new Kaisa_Monster(this);
	alita = new Alita(this);
	this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::UpdateKaisa), 1);
	this->scheduleUpdate();

	return true;
   

}

void HelloWorld::update(float deltaTime)
{
	auto positionAlita = alita->getSprite()->getPosition().x;
	kaisa->setTurnKaisa(positionAlita);
	
}

void HelloWorld::UpdateKaisa(float deltaTime)
{
	auto positionAlita = alita->getSprite()->getPosition().x;
	kaisa->setStateKaiSa(positionAlita);
	
}




void HelloWorld::createMapPhysics() {
	auto egdeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	egdeBody->setDynamic(false);
	auto egdeNode = Node::create();
	egdeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	egdeNode->setPhysicsBody(egdeBody);
	addChild(egdeNode);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map = TMXTiledMap::create("map/alita.tmx");
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

void HelloWorld::createHubAlita()
{
	auto hud = Sprite::create("res/BloodMc/hud.png");
	hud->setPosition(Vec2(50,visibleSize.height-40));
	hud->setScale(0.5);
	hud->setAnchorPoint(Vec2(0,0));
	addChild(hud,10);

	auto bloodMC = ui::LoadingBar::create("res/BloodMc/hud_blood.png");
	bloodMC->setPosition(Vec2(50, visibleSize.height - 40));
	bloodMC->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodMC->setScale(0.5);
	bloodMC->setPercent(20);
	bloodMC->setAnchorPoint(Vec2(0, 0));
	addChild(bloodMC, 11);


}


