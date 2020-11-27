#pragma once
#include "Entity.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define	CBRICK_STATE_COLLISION 10

class CBrick : public Entity
{
	float frameW, frameH;

public:
	float oldY;
	bool isColliCbrick;
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CBrick(float posX, float posY, float frameW, float frameH);
	~CBrick();
};

