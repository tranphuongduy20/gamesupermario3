#include "Venus.h"
#include "VenusBullet.h"

Venus::Venus(Player* mario, int piranhaType)
{
	tag = EntityType::VENUS;
	player = mario;
	this->piranhaType = piranhaType;

	SetAreaLimit();
	SetState(FIRE_PIRANHA_STATE_MOVE_UP);
}

void Venus::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);
	y += dy;
	if (vanish)
	{
		for (int i = 0; i < listFireball.size(); i++)
			listFireball.erase(listFireball.begin() + i);
		return;
	}

	for (int i = 0; i < listFireball.size(); i++)
	{
		if (listFireball[i]->isDone)
			listFireball.erase(listFireball.begin() + i);
	}

	if (delayToAttackStartTime && GetTickCount64() - delayToAttackStartTime > FIRE_PIRANHA_DELAY_TO_ATTACK_TIME)
	{
		if (playerArea != Area::OUTSIDE_AREA)
			CreateFireball();
		delayToAttackStartTime = 0;
	}

	for (LPVENUSBULLET fireball : listFireball)
		fireball->Update(dt, coObjects, player);

	if (!attackStartTime && y <= minPosY)
	{
		y = minPosY;
		vy = 0;
		attackStartTime = GetTickCount64();
		delayToAttackStartTime = GetTickCount64();
		SetState(FIRE_PIRANHA_STATE_ATTACK);
	}
	else if (!sleepStartTime && y >= FIRE_PIRANHA_MAX_Y)
	{
		y = FIRE_PIRANHA_MAX_Y;
		vy = 0;
		sleepStartTime = GetTickCount64();
	}

	if (attackStartTime && GetTickCount64() - attackStartTime > FIRE_PIRANHA_DELAY_TIME)
	{
		attackStartTime = 0;
		SetState(FIRE_PIRANHA_STATE_MOVE_DOWN);
	}

	if (sleepStartTime && GetTickCount64() - sleepStartTime > FIRE_PIRANHA_DELAY_TIME)
	{
		if (!CheckPlayerInSafeZone(playerLeft, playerTop, playerRight, playerBottom))
		{
			sleepStartTime = 0;
			SetState(FIRE_PIRANHA_STATE_MOVE_UP);
		}
	}
}

void Venus::Render()
{
	int ani;
	playerArea = GetCurrentPlayerArea();

	if (state == FIRE_PIRANHA_STATE_ATTACK)
	{
		switch (playerArea)
		{
		case TOP_LEFT_FAR:
		case TOP_LEFT_NEAR:
			ani = FIRE_PIRANHA_ANI_ATTACK_UP_LEFT;
			break;
		case TOP_RIGHT_FAR:
		case TOP_RIGHT_NEAR:
			ani = FIRE_PIRANHA_ANI_ATTACK_UP_RIGHT;
			break;
		case BOTTOM_LEFT_FAR:
		case BOTTOM_LEFT_NEAR:
			ani = FIRE_PIRANHA_ANI_ATTACK_DOWN_LEFT;
			break;
		case BOTTOM_RIGHT_FAR:
		case BOTTOM_RIGHT_NEAR:
			ani = FIRE_PIRANHA_ANI_ATTACK_DOWN_RIGHT;
			break;
		case OUTSIDE_AREA:
			ani = last_attack_ani;
			break;
		}
		last_attack_ani = ani;
	}
	else
	{
		switch (playerArea)
		{
		case TOP_LEFT_FAR:
		case TOP_LEFT_NEAR:
			ani = FIRE_PIRANHA_ANI_FACE_UP_LEFT;
			break;
		case TOP_RIGHT_FAR:
		case TOP_RIGHT_NEAR:
			ani = FIRE_PIRANHA_ANI_FACE_UP_RIGHT;
			break;
		case BOTTOM_LEFT_FAR:
		case BOTTOM_LEFT_NEAR:
			ani = FIRE_PIRANHA_ANI_FACE_DOWN_LEFT;
			break;
		case BOTTOM_RIGHT_FAR:
		case BOTTOM_RIGHT_NEAR:
			ani = FIRE_PIRANHA_ANI_FACE_DOWN_RIGHT;
			break;
		case OUTSIDE_AREA:
			ani = last_face_ani;
			break;
		}
		last_face_ani = ani;
	}

	if (!vanish)
		animationSet->at(ani)->Render(1, x, y);

	for (LPVENUSBULLET fireball : listFireball)
		fireball->Render();
	//RenderBoundingBox();
}

void Venus::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (vanish)
		return;

	if (piranhaType == TypeOfFirePiranha::RED)
	{
		l = x;
		t = y;
		r = x + RED_FIRE_PIRANHA_BBOX_WIDTH;
		b = y + RED_FIRE_PIRANHA_BBOX_HEIGHT;
	}
	else if (piranhaType == TypeOfFirePiranha::GREEN)
	{
		l = x;
		t = y;
		r = x + GREEN_FIRE_PIRANHA_BBOX_WIDTH;
		b = y + GREEN_FIRE_PIRANHA_BBOX_HEIGHT;
	}
}

void Venus::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case FIRE_PIRANHA_STATE_MOVE_UP:
		vy = -FIRE_PIRANHA_MOVE_SPEED_Y;
		break;
	case FIRE_PIRANHA_STATE_MOVE_DOWN:
		vy = FIRE_PIRANHA_MOVE_SPEED_Y;
		break;
	case FIRE_PIRANHA_STATE_ATTACK: // this line is just for drawing
		break;
	case 199:
		vanish = true;
		deadTime = GetTickCount64();
		break;
	}
}

Area Venus::GetCurrentPlayerArea()
{
	player->GetBoundingBox(playerLeft, playerTop, playerRight, playerBottom);

	float horizontalSeparationLine = y + RED_FIRE_PIRANHA_BBOX_HEIGHT - 1;

	if (playerBottom < horizontalSeparationLine && playerBottom >= 200)
	{
		if (playerRight >= farLeftStart && playerRight < nearLeftStart)
			return Area::TOP_LEFT_FAR;
		else if (playerRight >= nearLeftStart && playerRight < nearRightStart)
			return Area::TOP_LEFT_NEAR;
		else if (playerRight >= nearRightStart && playerRight < farRightStart)
			return Area::TOP_RIGHT_NEAR;
		else if (playerRight >= farRightStart && playerRight <= farRightEnd)
			return Area::TOP_RIGHT_FAR;
	}
	else if (playerBottom >= horizontalSeparationLine) // 367
	{
		if (playerRight >= farLeftStart && playerRight < nearLeftStart)
			return Area::BOTTOM_LEFT_FAR;
		else if (playerRight >= nearLeftStart && playerRight < nearRightStart)
			return Area::BOTTOM_LEFT_NEAR;
		else if (playerRight >= nearRightStart && playerRight < farRightStart)
			return Area::BOTTOM_RIGHT_NEAR;
		else if (playerRight >= farRightStart && playerRight <= farRightEnd)
			return Area::BOTTOM_RIGHT_FAR;
	}
	return Area::OUTSIDE_AREA;
}

void Venus::CreateFireball()
{
	VenusBullet* fireball = new VenusBullet({ x, y }, playerArea, player);
	listFireball.push_back(fireball);
}

void Venus::SetAreaLimit()
{
	if (piranhaType == TypeOfFirePiranha::RED)
	{
		minPosY = RED_FIRE_PIRANHA_MIN_Y;
		farLeftStart = RED_FIRE_PIRANHA_FAR_LEFT_START;
		nearLeftStart = RED_FIRE_PIRANHA_NEAR_LEFT_START;
		nearRightStart = RED_FIRE_PIRANHA_NEAR_RIGHT_START;
		farRightStart = RED_FIRE_PIRANHA_FAR_RIGHT_START;
		farRightEnd = RED_FIRE_PIRANHA_FAR_RIGHT_END;
		safeZoneLeft = RED_FIRE_PIRANHA_SAFE_ZONE_LEFT;
		safeZoneRight = RED_FIRE_PIRANHA_SAFE_ZONE_RIGHT;
		safeZoneBottom = RED_FIRE_PIRANHA_SAFE_ZONE_BOTTOM;
	}
	else
	{
		minPosY = GREEN_FIRE_PIRANHA_MIN_Y;
		farLeftStart = GREEN_FIRE_PIRANHA_FAR_LEFT_START;
		nearLeftStart = GREEN_FIRE_PIRANHA_NEAR_LEFT_START;
		nearRightStart = GREEN_FIRE_PIRANHA_NEAR_RIGHT_START;
		farRightStart = GREEN_FIRE_PIRANHA_FAR_RIGHT_START;
		farRightEnd = GREEN_FIRE_PIRANHA_FAR_RIGHT_END;
		safeZoneLeft = GREEN_FIRE_PIRANHA_SAFE_ZONE_LEFT;
		safeZoneRight = GREEN_FIRE_PIRANHA_SAFE_ZONE_RIGHT;
		safeZoneBottom = GREEN_FIRE_PIRANHA_SAFE_ZONE_BOTTOM;
	}
}

bool Venus::CheckPlayerInSafeZone(float pl, float pt, float pr, float pb)
{
	return (pl < safeZoneRight
		&& pr > safeZoneLeft
		&& pt < safeZoneBottom
		&& pb > 0);
}
