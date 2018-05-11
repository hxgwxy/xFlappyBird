#pragma once

#include "cocos2d.h"
#include "Bird.h"
#include "BGLayer.h"
#include "LandLayer.h"
#include <vector>


using namespace cocos2d;


typedef enum Z_ORDER{
	Z_ORDER_BG,
	Z_ORDER_PIPE,
	Z_ORDER_LAND,
	Z_ORDER_BIRD,
	Z_ORDER_MENU
};

const int PIPE_PASS = 1001;
const int PIPE_NOT_PASS = 1002;

typedef enum GAME_STATUS{
	GAME_STATUS_READY,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} ;



class GameScene : public cocos2d::Scene
{
public:
	GameScene();
	~GameScene();
    static cocos2d::Scene* createScene();
	
    virtual bool init();
    
	CREATE_FUNC(GameScene);

	virtual void update(float dt);
	int getGameStatus();
	void pipeRoll();
	void createPipe(float dt);
	void computeScore();
	bool onContactBegin(const PhysicsContact &contact);
	void gameOver();
	void setScoreSprite();
private:
	BGLayer *m_bg;
	LandLayer *m_land;
	Bird *m_bird;
	Sprite *m_sprite_score;
	int m_speed;
	int m_score;
	Vector<Node*> m_pipes;
	GAME_STATUS _gameStatus;
};


