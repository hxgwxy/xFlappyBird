#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LandLayer : public cocos2d::Layer
{
public:
	LandLayer();
	~LandLayer();
	virtual bool init();
	void landStartRoll(float dt);
	void landStopRoll();
	void setLandPhysics(bool b);
	CREATE_FUNC(LandLayer);
private:
	Sprite *m_land1;
	Sprite *m_land2;
	int m_speed;
};

