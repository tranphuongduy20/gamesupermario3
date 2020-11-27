#include "Koopa.h"
#include "Brick.h"

Koopa::Koopa()
{
	tag = EntityType::KOOPA;
	SetState(KOOPA_STATE_WALKING);
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isDeath)
	{
		left = x;

		right = x + KOOPA_BBOX_WIDTH;
		bottom = y + KOOPA_BBOX_HEIGHT + 1;
		/*if (state == KOOPA_STATE_DIE)
			bottom = y + KOOPA_BBOX_HEIGHT_DIE;
		else
			bottom = y + KOOPA_BBOX_HEIGHT;*/
		//if (state == KOOPA_STATE_DIE || state == KOOPA_STATE_TROOPA_SPIN)
		//	top = y + 10;
		//else
			top = y + 10;
		//else
		//	bottom = y + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y;
		right = left;
		bottom = top;
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);


	/// Simple fall down
	//DebugOut(L"SOPT:%d \n", state);
	if (state != KOOPA_STATE_DIE) vy += 0.002 * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (/*state != KOOPA_STATE_DIE &&*/ state != KOOPA_STATE_DIE_FLY)
	{
		//Disable Collider
		CalcPotentialCollisions(coObjects, coEvents);
	}


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

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		//DebugOut(L"SOPT:%d \n", coEvents.size());
		/*if (coEvents.size() >= 3 )
			vx *= -1;*/
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj))
				if (e->nx != 0)vx = -1 * vx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Koopa::Render()
{
	int ani = KOOPA_ANI_RED_WALKING;
	if (state == KOOPA_STATE_DIE) {
		ani = KOOPA_ANI_RED_DIE;
	}
	else if (state == KOOPA_STATE_TROOPA_SPIN) {
		ani = KOOPA_ANI_RED_TROOPA_SPIN;
	}
	else if (state == KOOPA_STATE_DIE_FLY)
		ani = KOOPA_ANI_RED_DIE_FLY;




	if (state == KOOPA_STATE_WALKING)
		animationSet->at(ani)->Render(nx, x, y);
	else if (state == KOOPA_STATE_DIE)
	{
		/*if (timerenderanidie == 0)
			timerenderanidie = GetTickCount64();
		if (GetTickCount64() - timerenderanidie < 200)*/
			animationSet->at(ani)->Render(nx, x, y);
	}
	else if (state == KOOPA_STATE_DIE_FLY)
	{
		animationSet->at(ani)->Render(nx, x, y);
	}
	if (vx > 0)
		nx = 1;
	else nx = -1;

	animationSet->at(ani)->Render(nx, x, y);

	RenderBoundingBox();
}

void Koopa::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE)/2 -5;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_TROOPA_SPIN:
		vx = -nx * 0.1;
		break;
	case KOOPA_STATE_DIE_FLY:
		vx = KOOPA_WALKING_SPEED - 0.04f;
		vy = -0.35;
		isDeath = true;
		break;
	}
}
