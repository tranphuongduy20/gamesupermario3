#pragma once
#include "Entity.h"
#define LEAF_WALKING_SPEED 0.02f;

#define LEAF_BBOX_WIDTH		14
#define LEAF_BBOX_HEIGHT	16


#define LEAF_STATE_WALKING	100

#define LEAF_ANI_WALKING		0

class Leaf : public Entity
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	DWORD timeDelay;
	int alpha;
	float oldY;
	float oldX;
	bool isDeath;
	bool isCollis;
	bool isOnTop = false;
	bool isStart = false;
	Leaf(float posX, float posY);
	virtual void SetState(int state);
};

