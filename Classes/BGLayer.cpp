#include "BGLayer.h"
#include "GameScene.h"

USING_NS_CC;

BGLayer::BGLayer()
{
}


BGLayer::~BGLayer()
{
}

bool BGLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
 	
	auto size = Director::getInstance()->getVisibleSize();

	auto t = time(NULL);
	auto hour = localtime(&t)->tm_hour;
	auto bg = Sprite::create();
	if (hour >= 6 && hour <= 18){
		bg->initWithSpriteFrameName("bg_day.png");
	}
	else{
		bg->initWithSpriteFrameName("bg_night.png");
	}
	bg->setPosition(Vec2(size.width / 2, size.height));
	bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	this->addChild(bg);

	return true;
}
