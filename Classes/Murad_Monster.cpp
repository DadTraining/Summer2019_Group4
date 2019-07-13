#include "Murad_Monster.h"

USING_NS_CC;

Murad_Monster::Murad_Monster(Scene * scene)
{
	auto visiblesize = Director::getInstance()->getVisibleSize();

	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Murad/attack_Murad.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Murad/attack_Murad.plist");
	m_sprite = Sprite::createWithSpriteFrameName("Attack_000.png");
	m_sprite->setPosition(Vec2(visiblesize.width *0.8, visiblesize.height*0.8));
	m_sprite->setFlippedX(false);
	m_sprite->setScale(0.05);
	auto mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize());
	mPhysicBody->setDynamic(true);
	m_sprite->setPhysicsBody(mPhysicBody);
	scene->addChild(m_sprite, 10);
	auto animateIdle = Animate::create(Murad_Monster::createAnimation("Attack_00", 4, 0.15));
	animateIdle->retain();
	m_sprite->runAction(RepeatForever::create(animateIdle));
}

Murad_Monster::~Murad_Monster()
{

}

void Murad_Monster::Init() {

}
void Murad_Monster::Update(float deltaTime) {

}
void Murad_Monster::Attack() {

}
