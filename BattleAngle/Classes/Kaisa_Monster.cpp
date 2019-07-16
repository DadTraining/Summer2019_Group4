
#include "Objects.h"
#include "Kaisa_Monster.h"
#include "Bullet.h"

USING_NS_CC;



Kaisa_Monster::Kaisa_Monster(Scene * scene)
{
	//set Blood for KaisaMonster
	this->setHP(HP_KAISAMONSTER);

	//Set Dame for KaisaMonster
	this->setDame(DAME_KAISAMONSTER);

	//KaisaMonster is live
	this->m_isAlive = true;

	Init();
	scene->addChild(m_sprite);
	
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


void Kaisa_Monster::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_sprite = Sprite::create("Plist/Kaisa/Die_000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	m_sprite->setPosition(Vec2(visibleSize.width / 3, 60));
	m_sprite->setScale(0.1);	
	//PhysicBody
	auto mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize());
	mPhysicBody->setDynamic(true);
	mPhysicBody->setRotationEnable(false);
	mPhysicBody->setCollisionBitmask(1);
	m_sprite->setPhysicsBody(mPhysicBody);
}

void Kaisa_Monster::Update(float deltaTime)
{
	for (auto i : m_bullet)
	{
		if (i->getSprite()->isVisible() == false) 
		{
			i->m_LefttoRight = (!m_LefttoRight);
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
	if (getm_LetftoRight() == true) 
	{
		m_sprite->setPosition(m_sprite->getPosition().x +5, m_sprite->getPosition().y);
	}
	else
	{
		m_sprite->setPosition(m_sprite->getPosition().x -5, m_sprite->getPosition().y);
	}

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
	//Kaisa shoot bullet
	Shoot();
	
	
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
	Update(3);
	m_LefttoRight = false;
}

bool Kaisa_Monster::getm_LetftoRight()
{
	Update(3);
	if (m_LefttoRight == true)
		return true;
	else
		return false;
}

