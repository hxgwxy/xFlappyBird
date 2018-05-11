#include "Bird.h"


typedef enum {
	BIRD_STATUS_FLYING,
	BIRD_STATUS_DIE
}BIRD_STATUS;


Bird *Bird::shareBird = nullptr;

Bird::Bird()
{
	
}

Bird::~Bird()
{

}

bool Bird::init()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto r = random() % 3;
	Vector<SpriteFrame*> birdFrame;
	if (Sprite::initWithSpriteFrameName(StringUtils::format("bird%d_1.png", r)))
	{
		for (auto i = 0; i <= 2; i++)
		{
			auto f = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bird%d_%d.png", r, i));
			birdFrame.pushBack(f);
		}
		auto animation = Animation::createWithSpriteFrames(birdFrame);
		animation->setLoops(-1);
		animation->setRestoreOriginalFrame(true);
		animation->setDelayPerUnit(0.1f);

		auto flyAction = Animate::create(animation);
		flyAction->setTag(0);
		runAction(flyAction);
	}
	return true;
}

void Bird::stop()
{
	stopActionByTag(0);
}

Bird* Bird::getInstance()
{
	if (shareBird == nullptr)
	{
		shareBird = new (std::nothrow) Bird;
		CCASSERT(shareBird, "FATAL: Not enough memory");
		shareBird->init();
	}
	return shareBird;
}

