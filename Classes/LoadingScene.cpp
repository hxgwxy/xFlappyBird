#include "LoadingScene.h"
#include "ReadyScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
 	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	std::vector<std::string> paths;
	paths.push_back("fonts");
	paths.push_back("images");
	paths.push_back("sounds");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);
	auto title = Sprite::create("splash.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(title);


	Director::getInstance()->getTextureCache()->addImageAsync("images.png", [=](Texture2D *texture){
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images.plist", texture);
		scheduleOnce(schedule_selector(LoadingScene::delayTime), 1);

		SimpleAudioEngine::getInstance()->preloadEffect("Wing.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("Die.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("Hit.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("Point.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("Swooshing.wav");
		}
	);
	return true;
}


void LoadingScene::delayTime(float dt)
{
	auto scene = MenuScene::create();
	auto transitionScene = TransitionFade::create(1.5f, scene);
	Director::getInstance()->replaceScene(transitionScene);
}
