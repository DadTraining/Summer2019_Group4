#include "Objects.h"

Objects::Objects()
{
	this->m_dame;
	this->m_hp;
	this->m_dame;
	this->m_isAlive = true;
}

Objects::~Objects()
{
}

void Objects::Init()
{

}

void Objects::Update(float deltaTime)
{
}
void Objects::setSprite(Sprite* m_sprite)
{
	this->m_sprite = m_sprite;
}

Sprite * Objects::getSprite()
{
	return this->m_sprite;
}

void Objects::setHP(int m_hp)
{
	this->m_hp = m_hp;
}

int  Objects::getHP()
{
	return this->m_hp;
}

void Objects::setDame(int m_dame)
{
	this->m_dame = m_dame;
}

int  Objects::getDame()
{
	return this->m_dame;
}

Animation* Objects::createAnimation(std::string prerfixName, int pFrameOrder, float delay)
{
	Vector<SpriteFrame*> animFrame;
	for (int i = 0; i <= pFrameOrder; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		std::string str = prerfixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrame.pushBack(frame);


	}
	animation = Animation::createWithSpriteFrames(animFrame, delay);
	return animation;
}

Sprite* Objects::DuplicateSprite(Sprite * sprite)
{
	Sprite* pRet = Sprite::createWithTexture(sprite->getTexture());
	pRet->setVisible(false);
	if (sprite->getChildrenCount() > 0)
	{
		for (int child = 0; child < sprite->getChildrenCount(); child++)
		{
			Sprite* spriteChild = (Sprite*)sprite->getChildren().at(child);
			Sprite* clone = DuplicateSprite((Sprite*)spriteChild);
			clone->boundingBox() = spriteChild->boundingBox();
			clone->setContentSize(spriteChild->getContentSize());
			clone->setPosition(spriteChild->getPosition());
			clone->setAnchorPoint(spriteChild->getAnchorPoint());
			pRet->addChild(clone, spriteChild->getZOrder(), spriteChild->getTag());
		}
	}
	return pRet;
}
