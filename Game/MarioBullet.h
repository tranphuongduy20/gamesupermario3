#pragma once
#include "Bullet.h"
#include <math.h>

#define ANIMATION_SET_BULLET		50
#define BULLET_BBOX_WIDTH			8
#define BULLET_BBOX_HEIGHT			9


#define BULLET_ANI_FIRE				0
#define BULLET_ANI_BANG				1
#define DISTANCE_TO_BANG			5

#define BULLET_SPEED					0.15f
#define BULLET_DEFLECT_SPEED_Y			0.13f
#define BULLET_GRAVITY					0.0005f
#define BULLET_DELAY				1500

#define SHOOT_ANIMATION_TIME		300



class MarioBullet : public Bullet
{
public:
	MarioBullet();
	~MarioBullet();


	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects);
	void Render();
};
typedef MarioBullet* LPMARIOBULLET;
