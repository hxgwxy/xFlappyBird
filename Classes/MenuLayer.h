#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public cocos2d::Layer
{
public:
	MenuLayer();
	~MenuLayer();
	virtual bool init();
	CREATE_FUNC(MenuLayer);

public:
	void showTitle(bool b);
	void showPlay(bool b);
	void showOver(bool b);
	void showRate(bool b);
	void showScore(bool b);
	void showPanel(bool b, int score, int best_score);
private:
	Sprite *m_title;
	Sprite *m_play;
	Sprite *m_over;
	Sprite *m_rate;
	Sprite *m_score;
	Sprite *m_panel;
};

