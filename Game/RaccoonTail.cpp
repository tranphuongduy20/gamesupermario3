#include "RaccoonTail.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Define.h"
#include "Brick.h"
#include "Game.h"
#include "Player.h"


RaccoonTail::RaccoonTail()
{
	/*x = position.x;
	y = position.y;
	this->nx = nx;*/
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(1));
	timeDelay = 0;
	timeDelayMax = TIME_DELAY_MAX;
}

void RaccoonTail::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects, float posX, float posY)
{
	if (!isAttack)
		return;
	timeDelay += dt;
	if (timeDelay >= timeDelayMax)
	{
		isAttack = false;
		timeDelay = 0;
		return;
	}
	Entity::Update(dt);
	this->x = posX - 8;
	this->y = posY + 19;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			//LPCOLLISIONEVENT e = coEventsResult[i];
			//if (e->obj->GetType() == EntityType::GOOMBA)
			//{
			//	Goomba* goomba = dynamic_cast<Goomba*>(e->obj);
			//	goomba->SetState(GOOMBA_STATE_DIE);
			//	//200 la state die
			//}
			//if (e->obj->GetType() == EntityType::KOOPA)
			//{
			//	Goomba* koopa = dynamic_cast<Goomba*>(e->obj);
			//	koopa->SetState(KOOPA_STATE_DIE);
			//	//200 la state die
			//}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

RaccoonTail::~RaccoonTail()
{
}

void RaccoonTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isAttack)
	{
		left = x;
		top = y;
		right = left + TAIL_BB_WIDTH;
		bottom = top + TAIL_BB_HEIGHT;
	}
}

void RaccoonTail::Render()
{
	RenderBoundingBox();
}

void RaccoonTail::Attack()
{
	isAttack = true;
}
