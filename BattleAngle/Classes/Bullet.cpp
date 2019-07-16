#include"Bullet.h"
Bullet::Bullet(cocos2d::Scene* scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//create Sprite bullet
	this->Init();
	this->m_sprite->removeFromParent();
	//PhysicBody
	auto mPhysicBody = PhysicsBody::createBox(Size(50,50), PhysicsMaterial(1.0, 0.0, 1.0));
	mPhysicBody->setGravityEnable(false);
	mPhysicBody->setCollisionBitmask(false);
	m_sprite->setPhysicsBody(mPhysicBody);
	m_sprite->setScale(0.5);
	//add bullet in scene
	scene->addChild(this->m_sprite,0);
	m_LefttoRight = false;
}

Bullet::~Bullet()
{

}


void Bullet::Init()
{
	Sprite* sprite = Sprite::create("bullet.png");
	this->m_sprite = DuplicateSprite(sprite);
}

void Bullet::Update(float deltaTime)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto outHeight = visibleSize.height / 1.3;
	this->m_sprite->setVisible(true);
	//Check turn Kaisa Monster
	if (!m_LefttoRight)
	{
		//turn Right
		auto moveBy = MoveBy::create(1, Vec2(outHeight, 0));
		auto setVisibleSprite = CallFunc::create([&]() {
			this->m_sprite->setVisible(false);
		});
		auto sequence = Sequence::create(moveBy, setVisibleSprite, nullptr);
		this->m_sprite->runAction(sequence);
	}
	else
	{
		//turn Left
		auto moveBy = MoveBy::create(1, Vec2(-outHeight, 0));
		auto setVisibleSprite = CallFunc::create([&]() {
			this->m_sprite->setVisible(false);
		});
		auto sequence = Sequence::create(moveBy, setVisibleSprite, nullptr);
		this->m_sprite->runAction(sequence);
	}

}

void Bullet::MoveBullet(bool isRight)
{
	
}


