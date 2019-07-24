#include "Murad_Monster.h"
#include "Alita.h"

USING_NS_CC;
Murad_Monster::Murad_Monster(Scene * scene)
{
	this->setHP(Objects::MURAD_HP);
	this->setDame(Objects::MURAD_DAME);
	this->m_isAlive = true;
	Init();
	scene->addChild(m_sprite);

	SpriteBatchNode *spriteNode;
	Sprite* sprite;
	SpriteFrame* spriteFrame;

	spriteNode = SpriteBatchNode::create("plist/Murad/Idle_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/Idle_Murad.plist");
	//sprite = Sprite::createWithSpriteFrameName("Idle_000.png");
	spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Idle_000.png");
	sprite = Sprite::createWithSpriteFrame(spriteFrame);

	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateIdle = Animate::create(Murad_Monster::createAnimation("Idle_00", 9, 0.15));
	//animateIdle->retain();
	mAnimation[ANIM_IDLE] = m_sprite->runAction(Repeat::create(animateIdle, 1));
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);

	spriteNode = SpriteBatchNode::create("plist/Murad/Run_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/Run_Murad.plist");
	//sprite = Sprite::createWithSpriteFrameName("Run_000.png");
	spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Run_000.png");
	sprite = Sprite::createWithSpriteFrame(spriteFrame);

	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateRun = Animate::create(Murad_Monster::createAnimation("Run_00", 9, 0.15));
	//animateRun->retain();
	mAnimation[ANIM_RUN] = m_sprite->runAction(RepeatForever::create(animateRun));
	CC_SAFE_RETAIN(mAnimation[ANIM_RUN]);

	spriteNode = SpriteBatchNode::create("plist/Murad/attack_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/attack_Murad.plist");
	//sprite = Sprite::createWithSpriteFrameName("Attack_000.png");
	spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Attack_000.png");
	sprite = Sprite::createWithSpriteFrame(spriteFrame);

	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateAttack = Animate::create(Murad_Monster::createAnimation("Attack_00", 9, 0.5));
	//animateAttack->retain();

	mAnimation[ANIM_ATTACK] = m_sprite->runAction(Repeat::create(animateAttack, 1.2));
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);

	spriteNode = SpriteBatchNode::create("plist/Murad/Dead_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/Dead_Murad.plist");
	spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Dead_000.png");
	sprite = Sprite::createWithSpriteFrame(spriteFrame);
	//sprite = Sprite::createWithSpriteFrameName("Dead_000.png");


	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateDie = Animate::create(Murad_Monster::createAnimation("Dead_00", 9, 0.15));
	//animateDie->retain();
	mAnimation[ANIM_DIE] = m_sprite->runAction(Repeat::create(animateDie, 1));
	CC_SAFE_RETAIN(mAnimation[ANIM_DIE]);

}

Murad_Monster::~Murad_Monster()
{

}

void Murad_Monster::Init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_sprite = Sprite::create("plist/Murad/Idle_000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	m_sprite->setPosition(Vec2(visibleSize.width / 2, 0));
	m_sprite->setScale(0.12);
	mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize());
	mPhysicBody->setCollisionBitmask(Objects::BITMASK_MURAD);
	mPhysicBody->setContactTestBitmask(3);
	mPhysicBody->setCategoryBitmask(1);
	mPhysicBody->setDynamic(true);
	mPhysicBody->setRotationEnable(false);
	m_sprite->setPhysicsBody(mPhysicBody);
}
void Murad_Monster::UpdateAttack(float xAlita, Alita * alita) {
	FPS++;
	if (FPS == 120) {
		setState_Murad(xAlita);
		FPS = 0;
	}
	if (attacked == true) {
		alita->BulletCollision();
		attacked = false;
	}

}
void Murad_Monster::Update(float deltaTime)
{
}
void Murad_Monster::Idle()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_IDLE]);
}
void Murad_Monster::Run() {
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
	if (getm_LetftoRight() == true)
	{
		auto moveby = MoveBy::create(1.35, Vec2(50, 0));
		m_sprite->runAction(moveby);
	}
	else
	{
		auto moveby = MoveBy::create(1.35, Vec2(-50, 0));
		m_sprite->runAction(moveby);
	}
}

void Murad_Monster::Attack() {
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_ATTACK]);
}
void Murad_Monster::Die()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_DIE]);
	mPhysicBody->setEnabled(false);
	m_sprite->setVisible(false);
}


void Murad_Monster::setTurnRight()
{
	this->m_sprite->setFlippedX(false);
	Update(3);
	m_LefttoRight = true;
}

void Murad_Monster::setTurnLeft()
{
	this->m_sprite->setFlippedX(true);
	Update(3);
	m_LefttoRight = false;

}

bool Murad_Monster::getm_LetftoRight()
{
	Update(3);
	if (m_LefttoRight == true)
		return true;
	else
		return false;
}

void Murad_Monster::DarkCollision()
{
	this->setHP(this->getHP() - Objects::ALITA_DAME);
	if (this->getHP() <= 0) {
		this->Die();
	}
}

void Murad_Monster::setState_Murad(float position)
{
	auto X_murad = m_sprite->getPosition().x;
	auto X_distance = abs(X_murad - position);
	if (X_distance <= 70)
	{
		Attack();
		attacked = true;
	}
	else if (X_distance > 70 && X_distance < 250)
	{
		Run();
	}
	else {
		Idle();
	}
}

void Murad_Monster::setTurn_Murad(float position)
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

void Murad_Monster::Collision() {

}