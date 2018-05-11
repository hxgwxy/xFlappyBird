#ifndef ___BIRD___H___
#define ___BIRD___H___

#include "cocos2d.h"


using namespace cocos2d;

class Bird : public Sprite
{
public:
	Bird();
	~Bird();
	CREATE_FUNC(Bird);
	virtual bool init();
	void stop();
	static Bird* getInstance();
private:
	static Bird *shareBird;
};

#endif