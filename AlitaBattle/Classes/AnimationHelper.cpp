#include "AnimationHelper.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
AnimationHelper* AnimationHelper::s_instance = NULL;

AnimationHelper::AnimationHelper()
{
	Init();
}



void AnimationHelper::Init()
{
	//Create Animation Alita
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/runAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/runAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Run__000.png");
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Run__00", 9, 0.05));
	mAnimationAlita[ANIM_RUN] = RepeatForever::create(animate);
	CC_SAFE_RETAIN(mAnimationAlita[ANIM_RUN]);

	/*Alita IDLE */
	spriteNode = SpriteBatchNode::create("plist/Alita/IdleAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/IdleAlita.plist");
	model = Sprite::createWithSpriteFrameName("Idle__000.png");
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Idle__00", 9, 0.05));
	mAnimationAlita[ANIM_IDLE] = RepeatForever::create(animate);
	CC_SAFE_RETAIN(mAnimationAlita[ANIM_IDLE]);

	/*Alita JUMP */
	spriteNode = SpriteBatchNode::create("plist/Alita/jumpAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/jumpAlita.plist");
	model = Sprite::createWithSpriteFrameName("Jump__000.png");
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Jump__00", 9, 0.05));
	mAnimationAlita[ANIM_JUMP] = Repeat::create(animate, 1);
	CC_SAFE_RETAIN(mAnimationAlita[ANIM_JUMP]);

	/*Alita THROW*/
	spriteNode = SpriteBatchNode::create("plist/Alita/throwAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/throwAlita.plist");
	model = Sprite::createWithSpriteFrameName("Throw__000.png");
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Throw__00", 9, 0.05));
	mAnimationAlita[ANIM_THROW] = Repeat::create(animate, 1);
	CC_SAFE_RETAIN(mAnimationAlita[ANIM_THROW]);

	/*Alita ATTACK*/
	spriteNode = SpriteBatchNode::create("plist/Alita/attackAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/attackAlita.plist");
	model = Sprite::createWithSpriteFrameName("Attack__000.png");
	spriteNode->addChild(model);
	animate = Animate::create(createAnimation("Attack__00", 9, 0.05));
	mAnimationAlita[ANIM_ATTACK] = Repeat::create(animate, 1);
	CC_SAFE_RETAIN(mAnimationAlita[ANIM_ATTACK]);
}

cocos2d::Animation * AnimationHelper::createAnimation(std::string prerfixName, int pFrameOrder, float delay)
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

AnimationHelper * AnimationHelper::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new AnimationHelper();
	}
	return s_instance;
}

AnimationHelper::~AnimationHelper()
{
}