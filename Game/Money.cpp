#include "Money.h"
#include "Brick.h"
Money::Money(float posX, float posY)
{
	x = posX;
	y = posY;
	oldY = y;
	tag = EntityType::MONEY;
	SetState(0);
	//SetState(MUSHROOM_STATE_WALKING);
	timeDelay = 0;
	isDone = false;
	isOnTop = false;
}

void Money::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = x + MONEY_BBOX_WIDTH;
		bottom = y + MONEY_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = x;
		bottom = y;
	}
}

void Money::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	if (isDone)
		return;
	Entity::Update(dt, coObjects);
	/*if (isOnTop)
	{
		vy += 0.002 * dt;
		if (vx == 0)
			vx = -MONEY_WALKING_SPEED;
	}*/
	if (isCollis == true && isStart == false)
	{
		timeDelay += dt;
		if (timeDelay >= 150)
		{
			alpha = 255;
			vy = -0.19;
			if (oldY - 50 >= y)
			{
				//isOnTop = true;
				isCollis = false;
				isStart = true;
			}
		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetType() == EntityType::CBRICK || e->obj->GetType() == EntityType::BRICK)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				//if (nx != 0) vx = 0;
				if (e->ny != 0) vy = 0;

				if (e->nx != 0)
					vx = -1 * vx;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Money::Render()
{
	if (isDone)
		return;
	int ani = MONEY_ANI_WALKING;

	animationSet->at(ani)->Render(nx, x, y, alpha);

	RenderBoundingBox();
}

void Money::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case MONEY_STATE_WALKING:
		//y -= 2;
		isCollis = true;
		break;
	case 0:
		alpha = 0;
		vx = 0;
		vy = 0;
		isCollis = false;
		break;
	}
}


