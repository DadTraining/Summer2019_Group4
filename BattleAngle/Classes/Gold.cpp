#include "Gold.h"

USING_NS_CC;
Gold::Gold(cocos2d::Scene * scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Init();
	scene->addChild(m_sprite);
	SpriteBatchNode *spriteNode;
	Sprite* sprite1;
	SpriteFrame* spriteFrame;

	spriteNode = SpriteBatchNode::create("plist/Gold/gold.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Gold/gold.plist");
	sprite1 = Sprite::createWithSpriteFrameName("gold_00.png");
	sprite1->setPosition(m_sprite->getPosition());
	spriteNode->addChild(sprite1);
	auto animate = Animate::create(Gold::createAnimation("gold_0", 3, 0.15));
	//animateIdle->retain();
	mAnimationGold = m_sprite->runAction(RepeatForever::create(animate));
	CC_SAFE_RETAIN(mAnimationGold);
}

Gold::~Gold()
{
}

void Gold::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_sprite = Sprite::create("plist/Gold/gold_00.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	m_sprite->setPosition(Vec2(visibleSize.width / 2, 0));
	m_sprite->setScale(0.5);
	mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize());
	mPhysicBody->setCollisionBitmask(Objects::BITMASK_GOLD);
	mPhysicBody->setContactTestBitmask(3);
	mPhysicBody->setCategoryBitmask(1);
	mPhysicBody->setDynamic(true);
	mPhysicBody->setRotationEnable(false);
	m_sprite->setPhysicsBody(mPhysicBody);
}

void Gold::Update(float deltaTime)
{
}

void Gold::GoldCollision()
{
	m_sprite->setVisible(false);
	mPhysicBody->setEnabled(false);
}
