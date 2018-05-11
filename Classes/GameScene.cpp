#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "ui\CocosGUI.h"
#include "BGLayer.h"
#include "LandLayer.h"
#include "MenuLayer.h"
#include "Number.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d::ui; 
using namespace CocosDenshion;

USING_NS_CC;


GameScene::GameScene() :m_speed(2)
{
	_gameStatus = GAME_STATUS_READY;
	m_sprite_score = nullptr;
	m_score = 0;
}

GameScene::~GameScene()
{

}

Scene* GameScene::createScene()
{
    return GameScene::create();
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	if ( !Scene::initWithPhysics() )
	{
		return false;
	}
	
	m_bg = BGLayer::create();
	addChild(m_bg, Z_ORDER_BG);
	m_land = LandLayer::create();
	m_land->setLandPhysics(true);
	addChild(m_land, Z_ORDER_LAND);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	getPhysicsWorld()->setGravity(Vec2(0, -1500.0));
	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //绘制调试遮罩
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
    
	m_bird = Bird::create();
	m_bird->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2));

	
	auto physicsBody = PhysicsBody::create();
	physicsBody->addShape(PhysicsShapeCircle::create(14));
	physicsBody->setLinearDamping(0.0f);
	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(false);
	physicsBody->setContactTestBitmask(0x01);
	physicsBody->getShape(0)->setDensity(10.0f);
	physicsBody->getShape(0)->setRestitution(0.0f);
	physicsBody->getShape(0)->setFriction(1.0f);
	m_bird->addComponent(physicsBody);
	this->addChild(m_bird, Z_ORDER_BIRD);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto ready = Sprite::createWithSpriteFrameName("text_ready.png");
	ready->setPosition(visibleSize.width / 2, visibleSize.height - visibleSize.height / 4);
	addChild(ready, Z_ORDER_PIPE);
	auto tutorial = Sprite::createWithSpriteFrameName("tutorial.png");
	tutorial->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(tutorial, Z_ORDER_PIPE);

	auto layerListener = EventListenerTouchOneByOne::create();
	layerListener->onTouchBegan = [=](Touch *t, Event *e){
		//SimpleAudioEngine::getInstance()->playEffect("Wing.wav");
		switch (_gameStatus)
		{
		case GAME_STATUS_READY:
			_gameStatus = GAME_STATUS_START;
			m_bird->getPhysicsBody()->setGravityEnable(true);
			m_bird->getPhysicsBody()->setVelocity(Vect(0, 400));
			schedule(schedule_selector(GameScene::createPipe), 1.3f);
			ready->runAction(FadeOut::create(1));
			tutorial->runAction(FadeOut::create(1));
			break;
		case GAME_STATUS_START:
			m_bird->getPhysicsBody()->setVelocity(Vect(0, 400));
			break;
		case GAME_STATUS_OVER:
			return false;
			break;
		}
		return true;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(layerListener, this);
	
	setScoreSprite();
	scheduleUpdate();
    return true;
}

void GameScene::setScoreSprite()
{
	if (m_sprite_score != nullptr)
	{
		removeChild(m_sprite_score);
	}
	auto size = Director::getInstance()->getVisibleSize();
	m_sprite_score = Number::getInstance()->getSprite(1, m_score);
	m_sprite_score->setPosition(Vec2(size.width / 2, size.height - 30));
	addChild(m_sprite_score, Z_ORDER_BIRD);
}

bool GameScene::onContactBegin(const PhysicsContact &contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	
	if (_gameStatus == GAME_STATUS_START)
	{
		gameOver();
	}
	return false;
}

void GameScene::gameOver()
{
	auto size = Director::getInstance()->getVisibleSize();
	_gameStatus = GAME_STATUS_OVER;
	unschedule(schedule_selector(GameScene::createPipe));	
	m_bird->stop();
	m_land->landStopRoll();

	auto max_scroe = UserDefault::getInstance()->getIntegerForKey("MAX_SCORE", 0);

	if (max_scroe < m_score)
	{
		UserDefault::getInstance()->setIntegerForKey("MAX_SCORE", m_score);
		max_scroe = m_score;
	}

	auto menu = MenuLayer::create();
	menu->showOver(true);
	menu->showRate(false);
	menu->showTitle(false);
	menu->showPanel(true, m_score, max_scroe);
	addChild(menu, Z_ORDER_MENU);

	
}


void GameScene::update(float dt)
{
	if (_gameStatus != GAME_STATUS_OVER)
	{
		pipeRoll();
	}
	if (_gameStatus == GAME_STATUS_START)
	{
		computeScore();
	}
}

void GameScene::computeScore()
{
	
	for (auto p : m_pipes)
	{
		if (p->getTag() == PIPE_NOT_PASS && (m_bird->getPositionX() - p->getPositionX()) >= (p->getContentSize().width / 2 + m_bird->getContentSize().width))
		{
			m_score++;
			p->setTag(PIPE_PASS);			
			setScoreSprite();
		}
		else
		{
			break;
		}
	}	
}


void GameScene::pipeRoll()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float posX = 0.0, distanceX = 0.0;
	
	for (auto i = 0; i < m_pipes.size(); i++)
	{
		auto pipes = m_pipes.at(i);
		posX = pipes->getPositionX() - m_speed;
		if (posX < -pipes->getContentSize().width)
		{
			removeChild(pipes);
			m_pipes.erase(i);
			continue;
		}		
		pipes->setPositionX(posX);
	}
}

void GameScene::createPipe(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto distanceY = 130; //上下距离	

	Sprite *pipe_up = Sprite::createWithSpriteFrameName("pipe_up.png");
	Sprite *pipe_down = Sprite::createWithSpriteFrameName("pipe_down.png");
	Node *pipes = Node::create();
	auto pipe_width = pipe_up->getContentSize().width;
	auto pipe_height = pipe_up->getContentSize().height;
	
	
	auto Body_up = PhysicsBody::createBox(pipe_up->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	auto Body_down = PhysicsBody::createBox(pipe_down->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	Body_up->setDynamic(false);
	Body_down->setDynamic(false);
	Body_up->setContactTestBitmask(true);
	Body_down->setContactTestBitmask(true);
	
	pipe_up->addComponent(Body_up);
	pipe_down->addComponent(Body_down);

	pipes->setContentSize(Size(pipe_width, pipe_height * 2 + distanceY));
	auto size = pipes->getContentSize();
	
	pipes->addChild(pipe_up, Z_ORDER_PIPE);
	pipes->addChild(pipe_down, Z_ORDER_PIPE);
		
	pipe_up->setPosition(Vec2(pipes->getContentSize().width / 2, pipes->getContentSize().height / 2));
	pipe_down->setPosition(Vec2(pipes->getContentSize().width / 2, pipes->getContentSize().height / 2 - distanceY));
	
	pipes->setPosition(Vec2(visibleSize.width, visibleSize.height / 2 + random() % 230));

	pipe_up->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	pipe_down->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	pipes->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	pipes->setTag(PIPE_NOT_PASS);
	addChild(pipes, Z_ORDER_PIPE);
	m_pipes.pushBack(pipes);
}
