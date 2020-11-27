#pragma once

#include "Entity.h"
#include "debug.h"

#define KOOPA_WALKING_SPEED 0.03f;

#define KOOPA_BBOX_WIDTH		16
#define KOOPA_BBOX_HEIGHT		25
#define KOOPA_BBOX_HEIGHT_DIE	15

#define KOOPA_STATE_WALKING			100
#define KOOPA_STATE_DIE				200
#define KOOPA_STATE_TROOPA_SPIN		300
#define KOOPA_STATE_DIE_FLY			400

#define KOOPA_ANI_RED_WALKING		0
#define KOOPA_ANI_RED_DIE			1
#define KOOPA_ANI_RED_TROOPA_SPIN	2
#define KOOPA_ANI_RED_DIE_FLY		3
#define KOOPA_ANI_GREEN_WALKING		4
#define KOOPA_ANI_GREEN_DIE			5
#define KOOPA_ANI_GREEN_TROOPA_SPIN	6
#define KOOPA_ANI_GREEN_DIE_FLY		7

#define KOOPA_RED					50
#define KOOPA_GREEN					51
#define KOOPA_GREEN_FLY				52
#define KOOPA_RED_FLY				53


class Koopa : public Entity
{
	int level;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	bool isDeath;
	Koopa();
	virtual void SetState(int state);
	void SetLevel(int l) { level = l; }
};

