#pragma once
#include "Entity.h"
#include "Enemy.h"
#define GOOMBA_WALKING_SPEED 0.04f;

#define GOOMBA_BBOX_WIDTH		16
#define GOOMBA_BBOX_HEIGHT		15
#define GOOMBA_BBOX_HEIGHT_DIE	9

#define GOOMBA_STATE_WALKING	100
#define GOOMBA_STATE_DIE		200
#define GOOMBA_STATE_DIE_FLY	300

#define GOOMBA_ANI_WALKING		0
#define GOOMBA_ANI_DIE			1
#define GOOMBA_ANI_DIE_FLY		2

class Goomba : public Entity
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	bool isDeath;
	DWORD timerenderanidie;
	Goomba();
	virtual void SetState(int state);
};

