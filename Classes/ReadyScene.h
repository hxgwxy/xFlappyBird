#pragma once
#include "cocos2d.h"


class MenuScene : public cocos2d::Scene
{
public:
	MenuScene();
	~MenuScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);
};

