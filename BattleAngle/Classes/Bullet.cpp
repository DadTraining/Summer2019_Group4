#include"Bullet.h"

Bullet::Bullet(cocos2d::Scene* scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->Init();
	this->m_sprite->removeFromParent();
	auto mPhysicBody = PhysicsBody::createBox(Size(50,50), PhysicsMaterial(1.0, 0.0, 1.0));
	mPhysicBody->setGravityEnable(false);
	mPhysicBody->setCollisionBitmask(false);
	m_sprite->setPhysicsBody(mPhysicBody);
	m_sprite->setScale(0.5);
	scene->addChild(this->m_sprite,0);
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
	auto outHeight = visibleSize.height/1.3;
	this->m_sprite->setVisible(true);	
	//Check turn Kaisa Monster
	if(m_LefttoRight == true)
	{
		auto moveBy = MoveBy::create(deltaTime, Vec2(outHeight, 0));
		auto setVisibleSprite = CallFunc::create([&]() {
			this->m_sprite->setVisible(false);
		});
		auto sequence = Sequence::create(moveBy, setVisibleSprite, nullptr);
		this->m_sprite->runAction(sequence);
	}
	else
	{
		auto moveBy = MoveBy::create(deltaTime, Vec2(-outHeight, 0));
		auto setVisibleSprite = CallFunc::create([&]() {
			this->m_sprite->setVisible(false);
		});
		auto sequence = Sequence::create(moveBy, setVisibleSprite, nullptr);
		this->m_sprite->runAction(sequence);
	}
	
	
}


