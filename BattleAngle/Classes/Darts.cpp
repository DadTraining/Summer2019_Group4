#include "Darts.h"

Darts::Darts(cocos2d::Scene * scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create Sprite darts
	this->Init();
	this->m_sprite->removeFromParent();
	//PhysicBody
	mPhysicBody = PhysicsBody::createBox(Size(50, 50), PhysicsMaterial(1.0, 0.0, 1.0));
	mPhysicBody->setGravityEnable(false);
	mPhysicBody->setCollisionBitmask(1);
	mPhysicBody->setRotationEnable(false);
	mPhysicBody->setCollisionBitmask(Objects::BITMASK_DART);
	mPhysicBody->setContactTestBitmask(true);
	m_sprite->setPhysicsBody(mPhysicBody);
	m_sprite->setScale(0.5);
	//add bullet in scene
	scene->addChild(this->m_sprite, 0);
	m_LefttoRight = true;
}

Darts::~Darts()
{
}

void Darts::Init()
{
	Sprite* sprite = Sprite::create("Kunai.png");
	this->m_sprite = DuplicateSprite(sprite);
}


void Darts::Update(float deltaTime)
{
}

void Darts::MoveBullet(bool isRight)
{
}

bool Darts::Throw(Vec2 PosAlita, bool AlitaTurnRight)
{
	if (!m_sprite->isVisible()) {

		m_LefttoRight = AlitaTurnRight;
		if (!m_LefttoRight) {
			m_sprite->setPosition(Vec2(PosAlita.x - 20, PosAlita.y + 50));
			m_sprite->setFlipX(true);
		}
		else {
			m_sprite->setPosition(Vec2(PosAlita.x + 20, PosAlita.y + 50));
			m_sprite->setFlipX(false);
		}

		m_sprite->setVisible(true);

		//Throw
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto outHeight = visibleSize.height / 1.3;
		mPhysicBody->setEnabled(true);
		if (m_LefttoRight)
		{
			//turn Right
			auto moveBy = MoveBy::create(1, Vec2(outHeight, 0));
			auto setVisibleSprite = CallFunc::create([&]() {
				this->m_sprite->setVisible(false);
			});
			auto disablePhysic = CallFunc::create([&]() {
				mPhysicBody->setEnabled(false);
			});
			auto sequence = Sequence::create(moveBy, setVisibleSprite, disablePhysic, nullptr);
			this->m_sprite->runAction(sequence);
		}
		else
		{
			//turn Left
			auto moveBy = MoveBy::create(1, Vec2(-outHeight, 0));
			auto setVisibleSprite = CallFunc::create([&]() {
				this->m_sprite->setVisible(false);
			});
			auto disablePhysic = CallFunc::create([&]() {
				mPhysicBody->setEnabled(false);
			});
			auto sequence = Sequence::create(moveBy, setVisibleSprite, disablePhysic, nullptr);
			this->m_sprite->runAction(sequence);
		}
		return true;
	}
	return false;
}