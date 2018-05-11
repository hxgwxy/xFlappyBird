#pragma once
#include "cocos2d.h"


class LoadingScene : public cocos2d::Scene
{
public:
	LoadingScene();
	~LoadingScene();
	//static cocos2d::Scene* createScene();
	
	virtual bool init();
	void delayTime(float dt);
	CREATE_FUNC(LoadingScene);
};

