#pragma once
#include "Entity.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

class Coin : public Entity
{
	float frameW, frameH;

public:

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	Coin(float frameW, float frameH);
	~Coin();
};

