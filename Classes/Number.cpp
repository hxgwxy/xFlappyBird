#include "Number.h"
#include "GameScene.h"

USING_NS_CC;

Number *Number ::instance = nullptr;


Number::Number()
{
}


Number::~Number()
{
}

Number* Number::getInstance()
{
	if (instance == nullptr)
	{
		instance = new (std::nothrow) Number;
		CCASSERT(instance, "FATAL: Not enough memory");
	}
	return instance;
}


Sprite *Number::getSprite(const int type, const int n)
{
	auto sprite = Sprite::create();
	int i = 0, j = 0;
	int num = n;
	std::vector<Sprite *> numbers;
	do{
		j = num % 10;
		num = num / 10;
		switch (type)
		{
		case 1:
			i = 48 + j;
			numbers.push_back(Sprite::createWithSpriteFrameName("font_0" + StringUtils::format("%d", i) + ".png"));
			break;
		case 2:
			i = j;
			numbers.push_back(Sprite::createWithSpriteFrameName("number_context_0" + StringUtils::format("%d", i) + ".png"));
			break;
		case 3:
			i = j;
			numbers.push_back(Sprite::createWithSpriteFrameName("number_score_0" + StringUtils::format("%d", i) + ".png"));
			break;
		}
	} while (num > 0);

	int pos = 0, total_width = 0;
	for (int i = numbers.size() - 1; i >= 0; i--)
	{
		auto curr = numbers.at(i);
		if (i == numbers.size() - 1)
		{
			pos = curr->getContentSize().width / 2;
		}
		else
		{
			auto next = numbers.at(i + 1);
			pos = next->getPositionX() + next->getContentSize().width / 2 + curr->getContentSize().width / 2;
		}
		total_width += curr->getContentSize().width;
		curr->setPosition(pos, 0);
		sprite->addChild(curr);
	}
	sprite->setContentSize(Size(total_width, numbers.at(0)->getContentSize().height));
	return sprite;
}
