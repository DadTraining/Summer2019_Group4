#include "AnimationHelper.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
AnimationHelper* AnimationHelper::s_instance = NULL;

AnimationHelper::AnimationHelper()
{
	/*SpriteBatchNode *spriteNode = SpriteBatchNode::create("plist/Alita/runAlita.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Alita/runAlita.plist");
	auto model = Sprite::createWithSpriteFrameName("Run__000.png");
	spriteNode->addChild(model);
	auto animate = Animate::create(createAnimation("Run__00", 9, 0.05));
	mAnimation[ANIM_RUN] = RepeatForever::create(animate);
	CC_SAFE_RETAIN(mAnimation[ANIM_RUN]);*/
}

AnimationHelper::~AnimationHelper()
{
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
