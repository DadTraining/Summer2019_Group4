#include "Objects.h"
#include "Kaisa_Monster.h"
#include "Bullet.h"

USING_NS_CC;
Kaisa_Monster::Kaisa_Monster(Scene * scene)
{
	//set Blood for KaisaMonster
	this->setHP(Objects::KAISA_HP);

	//Set Dame for KaisaMonster
	this->setDame(Objects::KAISA_DAME);

	//KaisaMonster is live
	this->m_isAlive = true;
	Init();
	scene->addChild(m_sprite);
	scene->addChild(loadingBarMonsterBG, 10);
	scene->addChild(loadingMonster, 15);

	//Create Bullet
	bullet = new Bullet(scene);
	bullet->getSprite()->setVisible(false);
	//bullet->getSprite()->setPosition(Vec2(this->m_sprite->getPosition().x - 20, this->m_sprite->getPosition().y + 60));

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
	delete this;
}


void Kaisa_Monster::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_sprite = Sprite::create("plist/Kaisa/Die_000.png");
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	m_sprite->setPosition(Vec2(visibleSize.width / 1.1, visibleSize.height / 2));
	m_sprite->setScale(0.08);
	//PhysicBody
	mPhysicBody = PhysicsBody::createBox(m_sprite->getContentSize()-Size(1000,0));
	mPhysicBody->setDynamic(true);
	mPhysicBody->setRotationEnable(false);
	mPhysicBody->setCollisionBitmask(Objects::BITMASK_KAISA);
	mPhysicBody->setContactTestBitmask(true);
	mPhysicBody->setCategoryBitmask(1);
	m_sprite->setPhysicsBody(mPhysicBody);

	//LoadingBar
	loadingBarMonsterBG = Sprite::create("loading_bg.png");
	loadingBarMonsterBG->setAnchorPoint(Vec2(0.5, 0));
	loadingBarMonsterBG->setScale(0.2);
	loadingMonster = ui::LoadingBar::create("progress.png");
	loadingMonster->setAnchorPoint(Vec2(0.5, 0));
	loadingMonster->setScale(0.2);
	loadingMonster->setPercent(Objects::KAISA_HP);
	loadingMonster->setDirection(ui::LoadingBar::Direction::LEFT);
}


void Kaisa_Monster::Update(float deltaTime)
{

	if (bullet->getSprite()->isVisible() == false)
	{
		bullet->m_LefttoRight = (!m_LefttoRight);
	}
	FPSKaisa++;
	if (FPSKaisa == 120) {
		setStateKaiSa(deltaTime);
		FPSKaisa = 0;
	}
	//bullet->UpdateAlive();
	//update LoadingMonster
	loadingBarMonsterBG->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + m_sprite->getContentSize().height*0.1);
	loadingMonster->setPosition(loadingBarMonsterBG->getPosition());
	loadingMonster->setPercent(getHP() * 100 / Objects::KAISA_HP);
}

void Kaisa_Monster::Run()
{

	m_sprite->stopAllActions();
	m_sprite->runAction(mAnimation[ANIM_RUN]);
	if (getm_LetftoRight() == true)
	{
		auto moveby = MoveBy::create(0.6, Vec2(5, 0));
		m_sprite->runAction(moveby);
	}
	else
	{
		auto moveby1 = MoveBy::create(0.6, Vec2(-5, 0));
		m_sprite->runAction(moveby1);
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
	if (bullet->getSprite()->isVisible() == false)
	{
		bullet->getSprite()->setPosition(Vec2(this->m_sprite->getPosition().x - 20, this->m_sprite->getPosition().y + 60));
		/*if (bullet->isAlive()) {
		bullet->getSprite()->setVisible(true);
		}*/
		bullet->Update(3);
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
	mPhysicBody->setEnabled(false);
	m_sprite->setVisible(false);
	bullet->mPhysicBody->setEnabled(false);
	bullet->getSprite()->setVisible(false);
	bullet->setAlive(false);
	loadingBarMonsterBG->setVisible(false);
	loadingMonster->setVisible(false);
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

void Kaisa_Monster::DarkCollision(int dame)
{
	this->setHP(this->getHP() - dame);
	if (this->getHP() <= 0) {
		this->Die();
	}
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

Bullet * Kaisa_Monster::getBullet()
{
	return bullet;
}