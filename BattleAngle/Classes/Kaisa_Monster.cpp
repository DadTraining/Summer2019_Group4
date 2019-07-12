
#include "Objects.h"
#include "Kaisa_Monster.h"
#include "Bullet.h"

USING_NS_CC;



Kaisa_Monster::Kaisa_Monster(Scene * scene)
{
	this->setHP(HP_KAISAMONSTER);
	this->setDame(DAME_KAISAMONSTER);
	this->m_isAlive = true;
	Init();
	scene->addChild(m_sprite);
	
	
	////Attack
	//SpriteBatchNode *spriteNode = SpriteBatchNode::create("Plist/Kaisa/attacknobullet.png");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Kaisa/attacknobullet.plist");
	//m_sprite = Sprite::createWithSpriteFrameName("Attack_000.png");
	//m_sprite->setPosition(Vec2(visibleSize.width / 2, 50));
	//m_sprite->setAnchorPoint(Vec2(0.5,0.5));
	//m_sprite->setFlippedX(false);
	//m_sprite->setScale(0.1);
	//auto mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize()*0.1, PhysicsMaterial(1.0, 0.0, 1.0));
	//mPhysicBody->setPositionOffset(this->m_sprite->getPosition());
	//mPhysicBody->setDynamic(true);
	//mPhysicBody->setRotationEnable(false);
	//spriteNode->addChild(m_sprite, 2);
	//spriteNode->setPhysicsBody(mPhysicBody);
	//scene->addChild(spriteNode, 2);

	//auto animateAttack = Animate::create(Kaisa_Monster::createAnimation("Attack_00", 2, 1));
	//animateAttack->retain();
	//m_Animation[ATTACK_KAISA] = Repeat::create(animateAttack,1);
	////Idle
	//SpriteBatchNode *spriteNode1 = SpriteBatchNode::create("Plist/Kaisa/idle.png");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Kaisa/idle.plist");
	//m_sprite = Sprite::createWithSpriteFrameName("Idle_000.png");
	//m_sprite->setPosition(Vec2(visibleSize.width / 3, 50));
	//m_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	//m_sprite->setFlippedX(false);
	//m_sprite->setScale(0.1);
	//mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize()*0.1, PhysicsMaterial(1.0, 0.0, 1.0));
	//mPhysicBody->setPositionOffset(this->m_sprite->getPosition());
	//mPhysicBody->setDynamic(true);
	//mPhysicBody->setRotationEnable(false);
	//spriteNode1->addChild(m_sprite, 2);
	//spriteNode1->setPhysicsBody(mPhysicBody);
	//scene->addChild(spriteNode1, 2);

	//auto animateIdle = Animate::create(Kaisa_Monster::createAnimation("Idle_00", 2, 1));
	//animateIdle->retain();
	//m_Animation[IDLE_KAISA] = Repeat::create(animateIdle, 1);



	//Bullet
	for (int i = 0; i < 1; i++)
	{
		Bullet*  bullet = new Bullet(scene);
		bullet->getSprite()->setVisible(false);
		m_bullet.push_back(bullet);
	}

 }

Kaisa_Monster::~Kaisa_Monster()
{
}

void Kaisa_Monster::Shoot()
{
	
	for (auto i : m_bullet)
	{
		if (i->getSprite()->isVisible() == false)
		{
			i->getSprite()->setPosition(Vec2(this->m_sprite->getPosition().x - 20, this->m_sprite->getPosition().y + 60));
			i->getSprite()->setVisible(true);
			i->Update(3);
			break;
		}
	}
	
}

void Kaisa_Monster::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_sprite = Sprite::create("Plist/Kaisa/Die_000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	m_sprite->setPosition(Vec2(visibleSize.width / 2, 60));
	m_sprite->setScale(0.1);	
	auto mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize());
	mPhysicBody->setDynamic(true);
	mPhysicBody->setRotationEnable(false);
	m_sprite->setPhysicsBody(mPhysicBody);
}

void Kaisa_Monster::Update(float deltaTime)
{
	for (auto i : m_bullet) {
		if (i->getSprite()->isVisible() == false) 
		{
			if (m_LefttoRight == true)
			{
				i->m_LefttoRight = true;
			}
			else
			{
				i->m_LefttoRight = false;
			}
		}
	}
	
	 

}

void Kaisa_Monster::Run()
{
	SpriteBatchNode *spriteNode= SpriteBatchNode::create("Plist/Kaisa/run.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Kaisa/run.plist");
	auto sprite = Sprite::createWithSpriteFrameName("Run_000.png");
	
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateRun = Animate::create(Kaisa_Monster::createAnimation("Run_00", 4, 0.15));
	animateRun->retain();
	m_sprite->runAction(Repeat::create(animateRun,1));


}

void Kaisa_Monster::Attack()
{
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("Plist/Kaisa/attacknobullet.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Kaisa/attacknobullet.plist");
	auto sprite = Sprite::createWithSpriteFrameName("Attack_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateAttack = Animate::create(Kaisa_Monster::createAnimation("Attack_00", 2, 0.5));
	animateAttack->retain();
	m_sprite->runAction(Repeat::create(animateAttack, 1));
	Shoot();
	
	
}

void Kaisa_Monster::Idle()
{
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("Plist/Kaisa/idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Kaisa/idle.plist");
	auto sprite = Sprite::createWithSpriteFrameName("Idle_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateIdle = Animate::create(Kaisa_Monster::createAnimation("Idle_00", 4, 0.15));
	animateIdle->retain();

	m_sprite->runAction(Repeat::create(animateIdle, 1));
}

void Kaisa_Monster::Die()
{
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("Plist/Kaisa/die.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Kaisa/die.plist");
	auto sprite = Sprite::createWithSpriteFrameName("Die_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateDie = Animate::create(Kaisa_Monster::createAnimation("Die_00", 4, 0.15));
	animateDie->retain();

	m_sprite->runAction(Repeat::create(animateDie, 1));
}

void Kaisa_Monster::setTurnRight()
{
	this->m_sprite->setFlippedX(false);
	m_LefttoRight = true;
}

void Kaisa_Monster::setTurnLeft()
{
	this->m_sprite->setFlippedX(true);
	m_LefttoRight = false;
}

