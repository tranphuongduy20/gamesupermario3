#include "Brick.h"

void Brick::Render()
{
	//animationSet->at(0)->Render(nx, x, y);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

Brick::Brick(float frameW, float frameH)
{
	tag = EntityType::BRICK;
	this->frameH = frameH;
	this->frameW = frameW;
}
