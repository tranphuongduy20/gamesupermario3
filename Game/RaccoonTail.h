#pragma once
#include "Entity.h"
#include "define.h"

#define TAIL_BB_WIDTH	32
#define TAIL_BB_HEIGHT	5
#define TIME_DELAY_MAX	200
class RaccoonTail : public Entity
{
public:
	RaccoonTail();
	bool isAttack;
	DWORD timeDelay;
	DWORD timeDelayMax;
	//CTail(D3DXVECTOR2 position, int nx);
	~RaccoonTail();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects, float x, float y);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void Attack();
};
