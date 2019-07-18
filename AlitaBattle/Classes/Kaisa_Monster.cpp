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

	//Create Animation
	SpriteBatchNode *spriteNode1;
	Sprite* sprite;

	spriteNode1 = SpriteBatchNode::create("plist/Kaisa/run.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Kaisa/run.plist");
	sprite = Sprite::createWithSpriteFrameName("Run_0000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode1->addChild(sprite);
	auto animateRun = Animate::create(Kaisa_Monster::createAnimation("Run_000", 4, 0.15));
	mAnimation[ANIM_RUN] = m_sprite->runAction(Repeat::create(animateRun, 1));
	CC_SAFE_RETAIN(mAnimation[ANIM_RUN]);

	spriteNode1 = SpriteBatchNode::create("plist/Kaisa/attacknobullet.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Kaisa/attacknobullet.plist");
	sprite = Sprite::createWithSpriteFrameName("Attack_0000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode1->addChild(sprite);
	auto animateAttack = Animate::create(Kaisa_Monster::createAnimation("Attack_000", 2, 0.5));
	mAnimation[ANIM_ATTACK] = m_sprite->runAction(Repeat::create(animateAttack, 1));
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);

	spriteNode1 = SpriteBatchNode::create("plist/Kaisa/idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Kaisa/idle.plist");
	sprite = Sprite::createWithSpriteFrameName("Idle_0000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode1->addChild(sprite);
	auto animateIdle = Animate::create(Kaisa_Monster::createAnimation("Idle_000", 4, 0.15));
	mAnimation[ANIM_IDLE] = m_sprite->runAction(Repeat::create(animateIdle, 1));
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);

	spriteNode1 = SpriteBatchNode::create("plist/Kaisa/die.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Kaisa/die.plist");
	sprite = Sprite::createWithSpriteFrameName("Die_0000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode1->addChild(sprite);
	auto animateDie = Animate::create(Kaisa_Monster::createAnimation("Die_000", 4, 0.15));
	mAnimation[ANIM_DIE] = m_sprite->runAction(Repeat::create(animateDie, 1));
	CC_SAFE_RETAIN(mAnimation[ANIM_DIE]);

}

Kaisa_Monster::~Kaisa_Monster()
{
}


void Kaisa_Monster::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_sprite = Sprite::create("plist/Kaisa/Die_000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	m_sprite->setPosition(Vec2(visibleSize.width / 1.1, visibleSize.height / 2));
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
	FPSKaisa++;
	if (FPSKaisa == 150) {
		setStateKaiSa(deltaTime);
		FPSKaisa = 0;
	}
}



void Kaisa_Monster::Run()
{

	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
	if (getm_LetftoRight() == true)
	{
		m_sprite->setPosition(m_sprite->getPosition().x + 5, m_sprite->getPosition().y);
	}
	else
	{
		m_sprite->setPosition(m_sprite->getPosition().x - 5, m_sprite->getPosition().y);
	}

}

void Kaisa_Monster::Attack()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_ATTACK]);
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
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_IDLE]);
}

void Kaisa_Monster::Die()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_DIE]);
}

void Kaisa_Monster::setTurnRight()
{
	this->m_sprite->setFlippedX(false);
	Update(3);
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

void Kaisa_Monster::BulletCollision()
{
}

void Kaisa_Monster::AlitaCollision()
{
}

void Kaisa_Monster::setStateKaiSa(float position)
{
	auto X_kaisa = m_sprite->getPosition().x;
	auto X_ailta = position;
	auto X_shoot = abs(X_kaisa - X_ailta);
	if (X_shoot <= 250)
	{
		Attack();
	}
	else if (X_shoot > 250 && X_shoot < 350)
	{
		Run();
	}
	else {
		Idle();
	}
	//Setturn


}

void Kaisa_Monster::setTurnKaisa(float position)
{
	if (position > m_sprite->getPosition().x)
	{
		setTurnRight();

	}
	else
	{
		setTurnLeft();
	}
}
