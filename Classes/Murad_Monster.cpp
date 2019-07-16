#include "Murad_Monster.h"

USING_NS_CC;

Murad_Monster::Murad_Monster(Scene * scene)
{
	this->setHP(HP_MURADMONSTER);
	this->setDame(DAME_MURADMONSTER);
	this->m_isAlive = true;
	Init();
	scene->addChild(m_sprite);


	SpriteBatchNode *spriteNode;
	Sprite* sprite;

	spriteNode = SpriteBatchNode::create("plist/Murad/Idle_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/Idle_Murad.plist");
	sprite = Sprite::createWithSpriteFrameName("Idle_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateIdle = Animate::create(Murad_Monster::createAnimation("Idle_00", 9, 0.15));
	animateIdle->retain();
	mAnimation[ANIM_IDLE] = m_sprite->runAction(Repeat::create(animateIdle, 1));

	spriteNode= SpriteBatchNode::create("Plist/Murad/Run_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Murad/Run_Murad.plist");
	sprite = Sprite::createWithSpriteFrameName("Run_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateRun = Animate::create(Murad_Monster::createAnimation("Run_00", 9, 0.15));
	animateRun->retain();
	mAnimation[ANIM_RUN] = m_sprite->runAction(Repeat::create(animateRun, 1));

	spriteNode = SpriteBatchNode::create("plist/Murad/attack_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/attack_Murad.plist");
	sprite = Sprite::createWithSpriteFrameName("Attack_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateAttack = Animate::create(Murad_Monster::createAnimation("Attack_00", 9, 0.5));
	animateAttack->retain();
	mAnimation[ANIM_ATTACK] = m_sprite->runAction(Repeat::create(animateAttack, 1));

	spriteNode = SpriteBatchNode::create("plist/Murad/Dead_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/Dead_Murad.plist");
	sprite = Sprite::createWithSpriteFrameName("Dead_000.png");
	sprite->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite);
	auto animateDie = Animate::create(Murad_Monster::createAnimation("Dead_00", 9, 0.15));
	animateDie->retain();
	mAnimation[ANIM_DIE] = m_sprite->runAction(Repeat::create(animateDie, 1));
	
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
	m_sprite->setScale(0.1);
	auto mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize()*0.5);
	mPhysicBody->setDynamic(true);
	mPhysicBody->setRotationEnable(false);
	m_sprite->setPhysicsBody(mPhysicBody);
}
void Murad_Monster::Update(float deltaTime) {

}
void Murad_Monster::Idle()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_IDLE]);
}
void Murad_Monster::Run() {
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
}

void Murad_Monster::Attack() {
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
}
void Murad_Monster::Die()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_DIE]);
}


void Murad_Monster::setTurnRight()
{
	this->m_sprite->setFlippedX(false);
}

void Murad_Monster::setTurnLeft()
{
	this->m_sprite->setFlippedX(true);
	
}
void Murad_Monster::Collision() {

}
