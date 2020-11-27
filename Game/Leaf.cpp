#include "Leaf.h"
#include "Brick.h"
#include "CBrick.h"
Leaf::Leaf(float posX, float posY)
{
	//alpha = 0;
	x = posX;
	y = posY;
	oldY = y+1;
	oldX = x;
	tag = EntityType::LEAF;
	SetState(0);
	//SetState(MUSHROOM_STATE_WALKING);
	timeDelay = 0;
}

void Leaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (!isDeath)
	{
		right = x + LEAF_BBOX_WIDTH;
		bottom = y + LEAF_BBOX_HEIGHT;
	}
}

void Leaf::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	if (isDeath)
		return;
	Entity::Update(dt, coObjects);
	if (isOnTop)
	{
		if (vy < 0)
			vy = 0;
		if (vx == 0)
		{
			vy = 0.026;
			vx = LEAF_WALKING_SPEED;
		}
		else
		{
			if (abs(x - oldX) > 40)
			{
				vy = 0.026;
				vx = -vx;
				oldX = x;
			}
			else
				vy -= 0.0002;
		}
	}
	if (isCollis == true && isStart == false)
	{
		timeDelay += dt;
		if (timeDelay >= 200)
		{
			vy = -0.04;
			alpha = 255;
			if (oldY - 30 >= y)
			{
				isOnTop = true;
				isCollis = false;
				isStart = true;
			}
		}
	}

	x += dx;
	y += dy;
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();


	//CalcPotentialCollisions(coObjects, coEvents);

	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	//x += dx;
	//	//y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	//	//if (rdx != 0 && rdx!=dx)
	//	//	x += nx*abs(rdx); 

	//	// block every object first!
	//	x += min_tx * dx + nx * 0.4f;
	//	y += min_ty * dy + ny * 0.4f;

	//	//if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;


	//	//
	//	// Collision logic with other objects
	//	//
	//	//DebugOut(L"SOPT:%d \n", coEvents.size());
	//	/*if (coEvents.size() >= 3 )
	//		vx *= -1;*/
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		/*if (dynamic_cast<Brick*>(e->obj))
	//			if (e->nx != 0)vx = -1 * vx;*/
	//		//if (e->obj->GetType() == EntityType::BRICK) // if e->obj is CBrick 
	//		//{
	//		//	Brick* brick = dynamic_cast<Brick*>(e->obj);
	//		//	/*x += min_tx * dx + nx * 0.4f;
	//		//	y += min_ty * dy + ny * 0.001f;*/
	//		//	if (nx != 0) vx = 0;
	//		//	if (ny != 0) vy = 0;
	//		//	if (e->ny != 0)
	//		//	{
	//		//		if (e->ny == -1)
	//		//		{
	//		//			isDeath = true;
	//		//			//isFly = false;
	//		//			//vy = 0;
	//		//		}
	//		//	}
	//		//}
	//	
	//	}
	//}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Leaf::Render()
{
	if (isDeath)
		return;
	int ani = LEAF_ANI_WALKING;
	if (vx > 0)
		nx = -1;
	else
		nx = 1;
	animationSet->at(ani)->Render(nx, x, y, alpha);
	RenderBoundingBox();
}

void Leaf::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case LEAF_STATE_WALKING:
		y -= 2;
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

