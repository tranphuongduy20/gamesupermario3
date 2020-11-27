#pragma once
#pragma once
#include "Entity.h"
#include "Player.h"

#define  VENUS_BOX_WIDTH	16
#define  VENUS_BOX_HEIGHT	24

#define VENUS_STATE_SHOOT_45		0
#define VENUS_STATE_SHOOT_45_MORE	1
#define VENUS_STATE_MOVE_DOWN		2
#define	VENUS_STATE_MOVE_UP			3

class VenusNoFire : public Entity
{
	int stateLocal;
public:
	float start_x;	
	float start_y;
	DWORD timewaittoshoot = GetTickCount64();
	DWORD timetomovedown;
	bool moveup = true;
	bool not_in_pipeline = false;
	bool fight;
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
};

