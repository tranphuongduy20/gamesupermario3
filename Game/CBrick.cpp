#include "CBrick.h"

void CBrick::Render()
{
	if (isColliCbrick)
	{
		animationSet->at(1)->Render(nx, x, y);
	}
	else
		animationSet->at(0)->Render(nx, x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + frameW;
	b = y + frameH;
}

CBrick::CBrick(float posX, float posY, float frameW, float frameH)
{
	x = posX;
	y = posY;
	oldY = posY;
	isColliCbrick = false;
	tag = EntityType::CBRICK;
	this->frameH = frameH;
	this->frameW = frameW;
}

void CBrick::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case CBRICK_STATE_COLLISION:
		if (!isColliCbrick)
		{
			y -= 16;
			vy += 0.05;
			isColliCbrick = true;
		}
		break;
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (y >= oldY)
	{
		y = oldY;
		vy = 0;
	}
}

