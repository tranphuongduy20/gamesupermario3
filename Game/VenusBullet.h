#pragma once
#include "Entity.h"
#include "Player.h"
#define BULLET_ANI_FIRE				0
#define BULLET_ANI_BANG				1
#define DISTANCE_TO_BANG			5

#define BULLET_GRAVITY					0.0005f
#define BULLET_DELAY				1500

#define SHOOT_ANIMATION_TIME		300

#define FIREBALL_BBOX_WIDTH		8
#define FIREBALL_BBOX_HEIGHT	8
#define FIREBALL_SPEED			0.15f
#define FIREBALL_TO_RIGHT		0
#define FIREBALL_TO_LEFT		1

#define PIRANHA_MAX_EXISTING_TIME_AFTER_DEATH	500
#define PIRANHA_FIREBALL_SPEED_X				0.05f
class VenusBullet : public Bullet
{
public:

	Player* player;

	VenusBullet(D3DXVECTOR2 piranhaPos, Area playerArea, Player* player);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects, Player* player);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();

	void SetRoute(Area playerArea);
	void SetNx(Area playerArea);
	void CreateEffect();
};
typedef VenusBullet* LPVENUSBULLET;

