#include "Objects.h"
#include "Alita.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;
Alita::Alita(Scene * scene)
{
	m_sprite = Sprite::create("plist/Alita/Throw__000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	auto ScreenSize = Director::getInstance()->getVisibleSize();
	m_sprite->setPosition(ScreenSize / 2);
	m_sprite->setScale(0.2);
	mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize());
	mPhysicBody->setGravityEnable(true);	//Gravity
	mPhysicBody->setMass(200);
	mPhysicBody->setRotationEnable(false);
	mPhysicBody->setCollisionBitmask(Objects::BITMASK_ALITA);
	mPhysicBody->setContactTestBitmask(true);
	mPhysicBody->setDynamic(true);	//setDynamic
	mPhysicBody->setCategoryBitmask(1);
	m_sprite->setPhysicsBody(mPhysicBody);
	scene->addChild(m_sprite, 10);
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
	setHP(Objects::ALITA_HP);
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
	mAnimation[ANIM_JUMP] = Repeat::create(animate, 1);
	CC_SAFE_RETAIN(mAnimation[ANIM_JUMP]);

	/*Alita THROW*/
	spriteNode = SpriteBatchNode::create("plist/Alita/throwAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/throwAlita.plist");
	model = Sprite::createWithSpriteFrameName("Throw__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Throw__00", 9, 0.05));
	mAnimation[ANIM_THROW] = Repeat::create(animate, 1);
	CC_SAFE_RETAIN(mAnimation[ANIM_THROW]);

	/*Alita ATTACK*/
	spriteNode = SpriteBatchNode::create("plist/Alita/attackAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/attackAlita.plist");
	model = Sprite::createWithSpriteFrameName("Attack__000.png");
	model->setPosition(m_sprite->getPosition());
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Attack__00", 9, 0.05));
	mAnimation[ANIM_ATTACK] = Repeat::create(animate, 1);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);
}

void Alita::MoveLeft()
{
	if (isMoveRight) {
		m_sprite->setFlippedX(true);
		isMoveRight = false;
	}
	m_sprite->stopAllActions();
	attacking = false;
	if (!isJump) {
		m_sprite->runAction(mAnimation[ANIM_RUN]);
	}
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
	attacking = false;
	if (!isJump) {
		m_sprite->runAction(mAnimation[ANIM_RUN]);
	}
	isRun = true;
}

void Alita::Jump()
{
	if (!isJump) {
		attacking = false;
		m_sprite->stopAllActions();
		m_sprite->runAction(mAnimation[ANIM_JUMP]);
		mPhysicBody->applyImpulse(Vec2(0, 60000));
		isJump = true;
	}
}

bool Alita::Attack()
{
	//m_sprite->stopAllActions();
	if (!attacking && !isJump) {
		if (!isRun) {
			m_sprite->stopAllActions();
		}
		m_sprite->runAction(mAnimation[ANIM_ATTACK]);
		auto setAttackingTrue = CallFunc::create([&]() {
			this->attacking = true;
		});
		auto setAttackingFalse = CallFunc::create([&]() {
			this->attacking = false;
		});
		// Set Already for next Attack
		auto sequence = Sequence::create(setAttackingTrue, DelayTime::create(1), setAttackingFalse, nullptr);
		this->m_sprite->runAction(sequence);
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/knife.wav", false);
		return true;
	}
	return false;
}

void Alita::Throw()
{
	if (darts->Throw(m_sprite->getPosition(), this->isMoveRight)) {	// already throw
		if (!isRun) {
			m_sprite->stopAllActions();
		}
		attacking = false;
		m_sprite->runAction(mAnimation[ANIM_THROW]);
		/*if (isRunning()) {
			auto sequence = Sequence::create(DelayTime::create(1.2), this->mAnimation[ANIM_RUN], nullptr);
			this->m_sprite->runAction(sequence);
		}*/
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Music/attackAlita.wav", false);
		}
}

void Alita::Update(float deltaTime)
{
	if (isRun) {
		if (!isMoveRight) {
			m_sprite->setPosition(m_sprite->getPosition() + Vec2(-4, 0));
		}
		else {
			m_sprite->setPosition(m_sprite->getPosition() + Vec2(+4, 0));
		}
	}
	else {
		//m_sprite->stopAllActions();
		//m_sprite->runAction(mAnimation[ANIM_IDLE]);
	}
	this->darts->Update(deltaTime);
}

void Alita::Idle()
{
	m_sprite->stopAllActions();
	attacking = false;
	m_sprite->runAction(mAnimation[ANIM_IDLE]);
}

void Alita::Collision()
{

}

void Alita::BulletCollision()
{
	this->setHP(this->getHP() - Objects::KAISA_DAME);
	if (this->getHP() <= 0) {
		this->m_sprite->setVisible(false);
		mPhysicBody->setEnabled(false);
	}
}

bool Alita::isRunning()
{
	return isRun;
}

void Alita::setRunning(bool run)
{
	if (run == false) {
		Idle();
	}
	isRun = run;
}

bool Alita::isJumping()
{
	return isJump;
}


void Alita::setJumping(bool jump)
{
	if (jump == false) {
		if (isJump != jump) {
			isJump = jump;
			if (isRun) {
				m_sprite->stopAllActions();
				m_sprite->runAction(mAnimation[ANIM_RUN]);
			}
			else if (!attacking) {
				Idle();
			}
		}
	}
	isJump = jump;
}

Darts * Alita::getDarts()
{
	return darts;
}