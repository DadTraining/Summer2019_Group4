#include "Objects.h"
#include "Alita.h"

USING_NS_CC;
Alita::Alita(Scene * scene)
{
	m_sprite = Sprite::create("plist/Alita/Throw__000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	auto ScreenSize = Director::getInstance()->getVisibleSize();
	m_sprite->setPosition(ScreenSize / 2);
	m_sprite->setScale(0.2);

	bodySprite1 = PhysicsBody::createBox(m_sprite->getContentSize());
	bodySprite1->setGravityEnable(true);	//Gravity
	bodySprite1->setMass(200);
	bodySprite1->setRotationEnable(false);
	//bodySprite1->setDynamic(true);		//setDynamic
	m_sprite->setPhysicsBody(bodySprite1);
	scene->addChild(m_sprite,10);
	this->darts = new Darts(scene);
	Init();
}

Alita::~Alita()
{

}

void Alita::Init()
{
	createAnimate();
	Idle();
}

void Alita::createAnimate()
{
	/*Alita RUN */
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/runAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/runAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Run__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Run__00", 9, 0.05));
	mAnimation[ANIM_RUN] = RepeatForever::create(animate);
	CC_SAFE_RETAIN(mAnimation[ANIM_RUN]);

	/*Alita IDLE */
	spriteNode = SpriteBatchNode::create("plist/Alita/IdleAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/IdleAlita.plist");
	model = Sprite::createWithSpriteFrameName("Idle__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Idle__00", 9, 0.05));
	mAnimation[ANIM_IDLE] = RepeatForever::create(animate);
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);

	/*Alita JUMP */
	spriteNode = SpriteBatchNode::create("plist/Alita/jumpAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/jumpAlita.plist");
	model = Sprite::createWithSpriteFrameName("Jump__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Jump__00", 9, 0.05));
	mAnimation[ANIM_JUMP] = Repeat::create(animate,1);
	CC_SAFE_RETAIN(mAnimation[ANIM_JUMP]);

	/*Alita THROW*/
	spriteNode = SpriteBatchNode::create("plist/Alita/throwAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/throwAlita.plist");
	model = Sprite::createWithSpriteFrameName("Throw__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Throw__00", 9, 0.05));
	mAnimation[ANIM_THROW] = Repeat::create(animate,1);
	CC_SAFE_RETAIN(mAnimation[ANIM_THROW]);

	/*Alita ATTACK*/
	spriteNode = SpriteBatchNode::create("plist/Alita/attackAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/attackAlita.plist");
	model = Sprite::createWithSpriteFrameName("Attack__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Attack__00", 9, 0.05));
	mAnimation[ANIM_ATTACK] = Repeat::create(animate,1);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);
}

void Alita::MoveLeft()
{
	if (isMoveRight) {
		m_sprite->setFlippedX(true);
		isMoveRight = false;
	}
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
	isRun = true;
	//m_sprite->setPosition(Vec2(m_sprite->getPosition().x - 10, m_sprite->getPosition().y));
}

void Alita::MoveRight()
{
	//m_sprite->runAction(Repeat::create(animate, 1));
	if (!isMoveRight) {
		m_sprite->setFlippedX(false);
		isMoveRight = true;
	}
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
	isRun = true;
}

void Alita::Jump()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_JUMP]);
	bodySprite1->applyImpulse(Vec2(0, 25000));
}

void Alita::Attack()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_ATTACK]);
}

void Alita::Throw()
{
	if (darts->Throw(m_sprite->getPosition(), this->isMoveRight)) {
		m_sprite->stopAllActions();
		m_sprite->runAction(mAnimation[ANIM_THROW]);
	}
}

void Alita::Update(float deltaTime)
{
	if (isRun) {
		if (!isMoveRight) {
			m_sprite->setPosition(m_sprite->getPosition() + Vec2(-2, 0));
		}
		else {
			m_sprite->setPosition(m_sprite->getPosition() + Vec2(+2, 0));
		}
	}
	else {
		//m_sprite->stopAllActions();
		//m_sprite->runAction(mAnimation[ANIM_IDLE]);
	}
}

void Alita::Idle()
{
	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_IDLE]);
}

void Alita::Collision()
{

}

bool Alita::isRunning()
{
	return isRun;
}

void Alita::setRunning(bool run)
{
	if (run == false) {
		isRun = run;
		Idle();
	}
}
