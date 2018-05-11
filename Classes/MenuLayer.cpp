#include "MenuLayer.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "Number.h"

USING_NS_CC;

MenuLayer::MenuLayer()
{
}


MenuLayer::~MenuLayer()
{
}

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
 	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	//add title
	m_title = Sprite::createWithSpriteFrameName("title.png");
	m_title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 5));
	this->addChild(m_title);
	m_over = Sprite::createWithSpriteFrameName("text_game_over.png");
	m_over->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - visibleSize.height / 5));
	this->addChild(m_over);
	m_panel = Sprite::createWithSpriteFrameName("score_panel.png");
	m_panel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_panel);


	m_rate = Sprite::createWithSpriteFrameName("button_rate.png");
	m_score = Sprite::createWithSpriteFrameName("button_score.png");
	m_play = Sprite::createWithSpriteFrameName("button_play.png");
	m_rate->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	m_score->setPosition(Vec2(visibleSize.width - visibleSize.width / 4, visibleSize.height / 5));
	m_play->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 5));
	m_rate->setTag(0);
	m_play->setTag(1);
	this->addChild(m_rate);
	this->addChild(m_score);
	this->addChild(m_play);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			e->getCurrentTarget()->runAction(ScaleTo::create(0.1f, 0.8f));
			return true;
		}
		return false;
	};
	
	listener->onTouchEnded = [=](Touch *t, Event *e)
	{
		e->getCurrentTarget()->runAction(Sequence::create(ScaleTo::create(0.1f, 1.2f), ScaleTo::create(0.1f, 1.0f), NULL));
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			switch (e->getCurrentTarget()->getTag())
			{
			case 0:
				break;
			case 1:
				auto scene = GameScene::create();
				auto transitionScene = TransitionFade::create(1.0f, scene);
				Director::getInstance()->replaceScene(transitionScene);
				break;
			}
		}
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_rate);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), m_score);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), m_play);

	showOver(false);
	showPanel(false, 0, 0);
	return true;
}

void MenuLayer::showTitle(bool b)
{
	m_title->setVisible(b);
}

void MenuLayer::showPlay(bool b)
{
	m_play->setVisible(b);
}

void MenuLayer::showOver(bool b)
{
	m_over->setVisible(b);
}

void MenuLayer::showRate(bool b)
{
	m_rate->setVisible(b);
}

void MenuLayer::showScore(bool b)
{
	m_score->setVisible(b);
}
void MenuLayer::showPanel(bool b, int score, int best_score)
{
	m_panel->removeChildByName("score");
	m_panel->removeChildByName("best_score");

	auto s = Number::getInstance()->getSprite(3, score);
	auto best = Number::getInstance()->getSprite(3, best_score);
	s->setPositionX(m_panel->getContentSize().width - 45);
	s->setPositionY(m_panel->getContentSize().height - 35);
	
	best->setPositionX(m_panel->getContentSize().width - 45);
	best->setPositionY(m_panel->getContentSize().height - 80);

	s->setName("score");
	best->setName("best_score");

	m_panel->addChild(s);
	m_panel->addChild(best);
	m_panel->setVisible(b);
}