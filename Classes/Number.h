#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Number
{
public:
	Number();
	~Number();
	Sprite *getSprite(int type, int n);
	static Number *getInstance();
private:
	static Number *instance;
};

