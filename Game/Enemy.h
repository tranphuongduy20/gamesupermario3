#pragma once
#include "Entity.h"
class Enemy: public Entity
{
protected:
	//int HP;
	bool isDamaged;
	int DamageofEnemy;
	bool isActive;
	bool isArmor;
	bool isBoss;
	bool isDeath;
	//int health;
	LPGAMEENTITY target;
	EnemyType enemyType;

public:
	Enemy();
	~Enemy();
	virtual void Render()=0;
	virtual bool IsContain(RECT rect1, RECT rect2);
	virtual float GetDistance(D3DXVECTOR2 pos, D3DXVECTOR2 target);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* objects = NULL) = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;


};

