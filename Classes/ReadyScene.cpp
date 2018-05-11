#include "ReadyScene.h"
#include "MenuLayer.h"
#include "BGLayer.h"
#include "LandLayer.h"
#include "Bird.h"


USING_NS_CC;

MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();
	auto bg = BGLayer::create();
	addChild(bg);
	auto menu = MenuLayer::create();
	addChild(menu);
	auto land = LandLayer::create();
	addChild(land);
	auto bird = Bird::getInstance();
	bird->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bird);
	return true;
}
