#include "LandLayer.h"
#include "GameScene.h"

USING_NS_CC;

LandLayer::LandLayer() :m_speed(2)
{
}


LandLayer::~LandLayer()
{
}

bool LandLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
 	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	m_land1 = Sprite::createWithSpriteFrameName("land.png");
	m_land2 = Sprite::createWithSpriteFrameName("land.png");
	m_land1->setPosition(Vec2(0, 0));
	m_land2->setPosition(Vec2(m_land1->getContentSize().width, 0));
	m_land2->setAnchorPoint(Vec2(0, 0));
	m_land1->setAnchorPoint(Vec2(0, 0));

	this->addChild(m_land1);
	this->addChild(m_land2);

	this->schedule(schedule_selector(LandLayer::landStartRoll), 1.0f / 60.0f);
	return true;
}

void LandLayer::setLandPhysics(bool b)
{
	if (b)
	{
		auto body_land1 = PhysicsBody::createBox(m_land1->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
		auto body_land2 = PhysicsBody::createBox(m_land2->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
		body_land1->setDynamic(false);
		body_land2->setDynamic(false);
		body_land1->setGravityEnable(false);
		body_land2->setGravityEnable(false);
		body_land1->setName("land1");
		body_land2->setName("land2");
		m_land1->addComponent(body_land1);
		m_land2->addComponent(body_land2);
	}
	else
	{
		m_land1->removeComponent("land1");
		m_land2->removeComponent("land2");
	}
}

void LandLayer::landStartRoll(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto posX1 = m_land1->getPositionX() - m_speed;
	auto posX2 = m_land2->getPositionX() - m_speed;

	if (posX2 + m_land2->getContentSize().width <= visibleSize.width)
	{
		posX1 = 0;
		posX2 = m_land1->getContentSize().width;
	}
	m_land1->setPositionX(posX1);
	m_land2->setPositionX(posX2);
}
void LandLayer::landStopRoll()
{
	this->unschedule(schedule_selector(LandLayer::landStartRoll));
}