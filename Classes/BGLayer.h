#pragma once
#include "cocos2d.h"

USING_NS_CC;

class BGLayer : public cocos2d::Layer
{
public:
	BGLayer();
	~BGLayer();
	virtual bool init();
	CREATE_FUNC(BGLayer);
};

