#include "VenusBullet.h"

VenusBullet::VenusBullet(D3DXVECTOR2 piranhaPos, Area playerArea, Player* player)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(50));
	// đọc player area và set vị trí, hướng bay
	this->x = piranhaPos.x + 4;
	this->y = piranhaPos.y + 4;
	this->player = player;

	SetRoute(playerArea);
	SetNx(playerArea);
	alpha = 255;
	isCollision = 0;
	isDone = false;
	damage = 1;
	timeDelayed = 0;
	timeDelayMax = BULLET_DELAY;
}

void VenusBullet::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects, Player* player)
{
	//Entity::Update(dt);

	//if (y > Game::GetInstance()->GetCamPosY() + SCREEN_HEIGHT / 2 || y < Game::GetInstance()->GetCamPosY())
		//isDone = true;

	if (isDone)
	{
		alpha = 0;
		DebugOut(L"isDone");
	}
	else
	{
		Bullet::Update(dt, coObjects);
		x += dx;
		y += dy;
#pragma region Xử lý va chạm

		if (this->IsCollidingObject(player))
		{
			isCollision = 1;
			vx = 0;
			vy = 0;
			if (player->level > MARIO_LEVEL_BIG)
			{
				player->level = MARIO_LEVEL_BIG;
				player->StartUntouchable();
			}
			else if (player->level == MARIO_LEVEL_BIG)
			{
				player->level = MARIO_LEVEL_SMALL;
				player->StartUntouchable();
			}
			else
			{
				player->SetState(MARIO_STATE_DIE);
				return;
			}
		}
		
	}
}

void VenusBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_BBOX_WIDTH;
	b = y + FIREBALL_BBOX_HEIGHT;
}

void VenusBullet::Render()
{

	//RenderBoundingBox();
	int ani;
	if (timeDelayed >= timeDelayMax)
	{
		isDone = true;
		timeDelayed = 0;
	}
	else
	{
		if (!isCollision)
		{
			ani = BULLET_ANI_FIRE;
			animationSet->at(0)->Render(nx, x, y, alpha);
			//DebugOut(L"Render bullet");
		}
		else
		{
			ani = BULLET_ANI_BANG;
			animationSet->at(ani)->Render(nx, x, y - DISTANCE_TO_BANG, alpha);
			if (animationSet->at(ani)->GetCurrentFrame() == 4)
			{
				isDone = true;
				timeDelayed = 0;
				Player::GetInstance()->isBullet = false;
			}
		}
	}
}


void VenusBullet::SetRoute(Area playerArea)
{
	switch (playerArea)
	{
	case TOP_LEFT_FAR:
		vx = -PIRANHA_FIREBALL_SPEED_X;
		vy = vx / 2.8;
		break;
	case TOP_LEFT_NEAR:
		vx = -PIRANHA_FIREBALL_SPEED_X;
		vy = vx;
		break;
	case TOP_RIGHT_FAR:
		vx = PIRANHA_FIREBALL_SPEED_X;
		vy = -vx / 2.8;
		break;
	case TOP_RIGHT_NEAR:
		vx = PIRANHA_FIREBALL_SPEED_X;
		vy = -vx;
		break;
	case BOTTOM_LEFT_FAR:
		vx = -PIRANHA_FIREBALL_SPEED_X;
		vy = -vx / 2.8;
		break;
	case BOTTOM_LEFT_NEAR:
		vx = -PIRANHA_FIREBALL_SPEED_X;
		vy = -vx;
		break;
	case BOTTOM_RIGHT_FAR:
		vx = PIRANHA_FIREBALL_SPEED_X;
		vy = vx / 2.8;
		break;
	case BOTTOM_RIGHT_NEAR:
		vx = PIRANHA_FIREBALL_SPEED_X;
		vy = vx;
		break;
	}
}

void VenusBullet::SetNx(Area playerArea)
{
	switch (playerArea)
	{
	case TOP_LEFT_FAR:
	case TOP_LEFT_NEAR:
	case BOTTOM_LEFT_FAR:
	case BOTTOM_LEFT_NEAR:
		nx = -1;
		break;
	case TOP_RIGHT_FAR:
	case TOP_RIGHT_NEAR:
	case BOTTOM_RIGHT_FAR:
	case BOTTOM_RIGHT_NEAR:
		nx = 1;
		break;
	}
}

