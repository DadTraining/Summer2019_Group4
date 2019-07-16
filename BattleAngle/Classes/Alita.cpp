#include "Objects.h"
#include "Alita.h"

Alita::Alita(Scene * scene)
{
	m_sprite = Sprite::create("plist/Alita/Throw__000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_sprite->setPosition(Vec2(visibleSize.width / 3, 60));
	m_sprite->setScale(0.3);

	auto bodySprite1 = PhysicsBody::createBox(m_sprite->getContentSize());
	bodySprite1->setGravityEnable(true);	//Gravity
	bodySprite1->setMass(10);
	bodySprite1->setRotationEnable(false);
	//bodySprite1->setDynamic(true);		//setDynamic
	m_sprite->setPhysicsBody(bodySprite1);

	scene->addChild(m_sprite);
}

Alita::~Alita()
{

}

void Alita::Init()
{

}

void Alita::MoveLeft()
{

	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/runAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/runAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Run__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Run__00", 9, 0.05));
	animate->retain();

	if (isMoveRight) {
		m_sprite->setFlippedX(true);
		isMoveRight = false;
	}
	m_sprite->runAction(Repeat::create(animate, 1));
	m_sprite->setPosition(Vec2(m_sprite->getPosition().x - 10, m_sprite->getPosition().y));
}

void Alita::MoveRight()
{
	
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/runAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/runAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Run__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Run__00", 9, 0.05));
	animate->retain();

	if (!isMoveRight) {
		m_sprite->setFlippedX(false);
		isMoveRight = true;
	}
	m_sprite->runAction(Repeat::create(animate, 1));
	m_sprite->setPosition(Vec2(m_sprite->getPosition().x + 10, m_sprite->getPosition().y));
}

void Alita::Jump()
{

	if (m_sprite->getPosition().y < Director::getInstance()->getVisibleSize().height / 2) {
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/jumpAlita.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/jumpAlita.plist");
		auto model = Sprite::createWithSpriteFrameName("Jump__000.png");
		model->setPosition(m_sprite->getPosition());
		spriteNode->addChild(model);
		auto animate = Animate::create(createAnimation("Jump__00", 9, 0.05));
		animate->retain();
		m_sprite->runAction(Repeat::create(animate, 1));
		m_sprite->setPosition(Vec2(m_sprite->getPosition().x, m_sprite->getPosition().y + 50));
	}
}

void Alita::Attack()
{
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/attackAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/attackAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Attack__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Attack__00", 9, 0.05));
	animate->retain();
	m_sprite->runAction(Repeat::create(animate, 1));
}

void Alita::Throw()
{
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/throwAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/throwAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Throw__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Throw__00", 9, 0.05));
	animate->retain();
	m_sprite->runAction(Repeat::create(animate, 1));
}

void Alita::Update(float deltaTime)
{

}

void Alita::Collision()
{

}