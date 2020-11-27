//#include "Gunner.h"
//
//void Gunner::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x;
//	top = y;
//	right = x + GUNNER_BBOX_WIDTH;
//	bottom = y + GUNNER_BBOX_HEIGHT;
//}
//
//void Gunner::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
//{
//	// Calculate dx, dy 
//	Entity::Update(dt);
//#pragma region Xử lý vy
//	// Simple fall down
//	vy += GUNNER_GRAVITY * dt;
//
//
//#pragma endregion
//
//#pragma region Xử lý vx
//	if (vx < 0 && x < 0) {
//		x = 0; vx = -vx;
//	}
//
//	if (vx > 0 && x > 290) {
//		x = 290; vx = -vx;
//	}
//#pragma endregion
//
//
//
//#pragma region Xử lý va chạm
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//	vector<LPGAMEENTITY> bricks;
//
//	coEvents.clear();
//	bricks.clear();
//	for (UINT i = 0; i < coObjects->size(); i++)
//		if (coObjects->at(i)->GetType() == EntityType::BRICK)
//			bricks.push_back(coObjects->at(i));
//
//
//
//
//	// turn off collision when die 
//	if (state != GUNNER_STATE_DIE)
//		CalcPotentialCollisions(&bricks, coEvents);
//
//
//
//	// No collision occured, proceed normally
//	if (coEvents.size() == 0)
//	{
//		x += dx;
//		y += dy;
//	}
//	else
//	{
//		float min_tx, min_ty, nx = 0, ny;
//		float rdx = 0;
//		float rdy = 0;
//
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
//		
//
//		x += min_tx * dx + nx * 0.1f;
//		y += min_ty * dy + ny * 0.1f;
//	
//	}
//
//	// clean up collision events
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//}
//
//void Gunner::Render()
//{
//	if (vx > 0)
//		direction = 1;
//	else
//		direction = -1;
//
//	int ani = GUNNER_ANI_WALKING;
//	if (state == GUNNER_STATE_DIE) {
//		ani = GUNNER_ANI_DIE;
//	}
//	//DebugOut(L"[xxxxxx] direction: %s\n", direction);
//	animationSet->at(ani)->Render(direction, x, y);
//
//	RenderBoundingBox();
//}
//
//Gunner::Gunner()
//{
//	SetState(GUNNER_STATE_WALKING);
//}
//
//void Gunner::SetState(int state)
//{
//	Entity::SetState(state);
//	switch (state)
//	{
//	case GUNNER_STATE_DIE:
//		y += GUNNER_BBOX_HEIGHT - GUNNER_BBOX_HEIGHT_DIE + 1;
//		vx = 0;
//		vy = 0;
//		break;
//	case GUNNER_STATE_WALKING:
//		vx = -GUNNER_WALKING_SPEED;
//	}
//}
