#pragma once
#include "Entity.h"

#define DISTANCE_TO_GUN_WIDTH   9
#define DISTANCE_TO_GUN_HEIGHT  2
#define DISTANCE_TO_BANG		4

class Bullet;
typedef Bullet* LPBULLET;
class Bullet : public Entity
{
public:
	bool isDone;
	int damage;
	int isTargetTop;
	int alpha;
	bool isCollision;
	float timeDelayed, timeDelayMax;

public:
	Bullet();
	~Bullet();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

	void Fire(int direct, float posX, float posY) { direction = direct; x = posX; y = posY; alpha = 255; isDone = false; isCollision = 0; }
	void ResetDelay() { timeDelayed = 0; }
	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
	int GetDamage() { return damage; }

};