#include "VenusNoFire.h"
#include "debug.h"


//CGiantPiranhaPlant::CGiantPiranhaPlant(float x, float y) : CGameObject()
//{
//	start_x = x;
//	start_y = y;
//	this->x = x;
//	this->y = y;
//}
void VenusNoFire::Render()
{
	animationSet->at(state)->Render(nx, x, y);

	RenderBoundingBox();
}

void VenusNoFire::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case VENUS_STATE_SHOOT_45:
		fight = false;
		break;
	case VENUS_STATE_SHOOT_45_MORE:
		//fight = false;
		break;
	case VENUS_STATE_MOVE_UP:
		vy = -0.15f;
		moveup = false;
		break;
	case VENUS_STATE_MOVE_DOWN:
		vy = 0.15f;
		moveup = true;
		break;
	}
}

void VenusNoFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + VENUS_BOX_WIDTH;
	bottom = y + VENUS_BOX_HEIGHT;
}

void VenusNoFire::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{

	Entity::Update(dt, coObjects);
	y += dy;

	//y += (y == start_y - 32  && moveup ) ? 0 : dy;

	//if (start_y == 0) start_y = y;
	////y += dy;
	if (y > 361 && y < 384)
		vy += MARIO_GRAVITY / 3 * dt;
	else vy = 0;

	if (moveup && GetTickCount64() - timewaittoshoot > 3000)
	{
		fight = false;
		DebugOut(L"a");
		SetState(VENUS_STATE_MOVE_UP);
	}
	else if (GetTickCount64() - timewaittoshoot > 4000 && !fight)
	{

		SetState(VENUS_STATE_SHOOT_45_MORE);
		fight = true;
		DebugOut(L"b");
		//timetomovedown=0;
	}
	else if (GetTickCount64() - timewaittoshoot > 5000 && !moveup)
	{
		DebugOut(L"c");
		SetState(VENUS_STATE_MOVE_DOWN);
		timewaittoshoot = GetTickCount64();
	}

	if (y >= 384)
	{
		y = 384;

	}
	if (y <= 361)
	{
		y = 361;
	}
}



