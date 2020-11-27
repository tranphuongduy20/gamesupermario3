#include "Coin.h"

void Coin::Render()
{
	animationSet->at(0)->Render(nx, x, y);
	RenderBoundingBox();
}

void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

Coin::Coin(float frameW, float frameH)
{
	tag = EntityType::COIN;
	this->frameH = frameH;
	this->frameW = frameW;
}
