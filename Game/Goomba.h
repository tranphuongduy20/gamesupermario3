#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"

#define GOOMBA_WALKING_SPEED 0.04f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING	0
#define GOOMBA_STATE_DIE		1
#define GOOMBA_STATE_DIE_FLY	2

#define GOOMBA_RED_STATE_HAS_WING_WALK		3
#define GOOMBA_RED_STATE_HAS_WING_FLY_LOW	4
#define GOOMBA_RED_STATE_HAS_WING_FLY_HIGH	5
#define GOOMBA_RED_STATE_NO_WING_WALK		6
#define GOOMBA_RED_STATE_NO_WING_DIE		7
#define GOOMBA_RED_STATE_NO_WING_DIE_FLY	8

#define GOOMBA_NORMAL 1
#define GOOMBA_RED 2

class Goomba : public Entity
{

public:
	bool hasWing = true;
	bool isGrounded;
	DWORD sulkyMario;  //doi mario bo ko them duoi nua
	Player* Mario;
	DWORD readyToFlyHigh;
	int countFly;
	vector <LPGAMEENTITY> listEffect;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	void SetSpeed();
	Goomba(float width, float height);
	void SetDirection();
	DWORD timeRenderAniDie;
	Goomba(Player* mario);
	virtual void SetState(int state);
};
