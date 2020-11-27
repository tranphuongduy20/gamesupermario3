#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <map>
#include "Timer.h"
#include "CBrick.h"

#define MARIO_WALKING_SPEED		0.08f 
#define	MARIO_VMAX				0.15f
#define MARIO_WALKING_ACC		0.00015f

#define MARIO_JUMP_SPEED_Y		0.2f
#define MARIO_JUMP_SPEED_YMAX	0.2f
#define MARIO_JUMP_Y			0.02f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.0003f
#define MARIO_DIE_DEFLECT_SPEED	 0.2f

#define MARIO_VY_TO_CONFIRM_JUM 0.03f
#define MARIO_VY_FLY			0.1f
#define MARIO_STOP_FALLING		0.001f
#define MARIO_TYPE				350
#define SHOOT_ANIMATION_TIME	300

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_JUMP_MAX		500
#define MARIO_STATE_DIE				400
#define MARIO_STATE_CROUCH			600
#define MARIO_STATE_SKID_LEFT		700
#define MARIO_STATE_SKID_RIGHT		800
#define MARIO_STATE_RUN				900
#define MARIO_STATE_SPIN			1000
#define MARIO_STATE_FLY				1100
#define MARIO_STATE_KICK			1200
#define MARIO_STATE_BULLET			1300

#define MARIO_ANI_BIG_IDLE				0
#define MARIO_ANI_BIG_WALKING			1
#define MARIO_ANI_BIG_RUN				2
#define MARIO_ANI_SMALL_IDLE			3
#define MARIO_ANI_SMALL_WALKING			4
#define MARIO_ANI_SMALL_RUN				5
#define MARIO_ANI_SMALL_SKID			6
#define MARIO_ANI_BIG_SKID				7
#define MARIO_ANI_BIG_JUMP_UP			8
#define MARIO_ANI_SMALL_JUMP			9
#define MARIO_ANI_BIG_CROUCH			10
#define MARIO_ANI_RACCOON_IDLE			11
#define MARIO_ANI_RACCOON_WALKING		12
#define MARIO_ANI_RACCOON_RUN			13
#define MARIO_ANI_RACCOON_SKID			14
#define MARIO_ANI_RACCOON_JUMP_UP		15
#define MARIO_ANI_RACCOON_CROUCH		16
#define MARIO_ANI_RACCOON_SPIN			17
#define MARIO_ANI_BIG_WALK_RUN			18
#define MARIO_ANI_SMALL_WALK_RUN		19
#define MARIO_ANI_RACCOON_SPIN_SINGLE	20
#define MARIO_ANI_RACCOON_SPEEDUP		21
#define MARIO_ANI_FIRE_IDLE				22
#define MARIO_ANI_FIRE_WALKING			23
#define MARIO_ANI_FIRE_WALK_RUN			24
#define MARIO_ANI_FIRE_RUN				25
#define MARIO_ANI_FIRE_SKID				26
#define MARIO_ANI_FIRE_JUMP_UP			27
#define MARIO_ANI_FIRE_CROUCH			28
#define MARIO_ANI_RACCOON_FLY			29
#define MARIO_ANI_SMALL_DIE				30
#define MARIO_ANI_RACCOON_JUMP_DOWN		31
#define MARIO_ANI_RACCOON_FLY_SHEET		32
#define MARIO_ANI_BIG_JUMP_DOWN			33
#define MARIO_ANI_FIRE_JUMP_DOWN		34
#define MARIO_ANI_SMALL_KICK			35
#define MARIO_ANI_BIG_KICK				36
#define MARIO_ANI_RACCOON_KICK			37
#define MARIO_ANI_FIRE_KICK				38
#define MARIO_ANI_SMALL_IDLE_HOLD		39
#define MARIO_ANI_SMALL_HOLD			40
#define MARIO_ANI_BIG_IDLE_HOLD			41
#define MARIO_ANI_BIG_HOLD				42
#define MARIO_ANI_RACCOON_IDLE_HOLD		43
#define MARIO_ANI_RACCOON_HOLD			44
#define MARIO_ANI_FIRE_IDLE_HOLD		45
#define MARIO_ANI_FIRE_HOLD				46
#define MARIO_ANI_FIRE_THROW			47
#define MARIO_ANI_FIRE_FLY_BULLET		48




#define	MARIO_LEVEL_SMALL			51
#define	MARIO_LEVEL_BIG				52
#define	MARIO_LEVEL_RACCOON			53
#define	MARIO_LEVEL_FIRE			54

#define MARIO_SMALL_BBOX_WIDTH		13
#define MARIO_SMALL_BBOX_HEIGHT		15

#define MARIO_BIG_BBOX_WIDTH		15
#define MARIO_BIG_BBOX_HEIGHT		27

#define MARIO_RACCOON_BBOX_WIDTH	15
#define MARIO_RACCOON_BBOX_HEIGHT	27

#define MARIO_FIRE_BBOX_WIDTH		15
#define MARIO_FIRE_BBOX_HEIGHT		27

#define MARIO_UNTOUCHABLE_TIME 5000

#define	MARIO_ACCELERATION		0.005f

#define	MARIO_ACC		0.005f

#define	MARIO_SPEEEDUP		0.002f
#define PLAYER_IMMORTAL_DURATION 1000

#define HIGHT_LEVER1 50


class Player : public Entity
{
	static Player* instance;

public:
	vector<LPGAMEENTITY> listitems;
	int level;
	int lastnx;
	int untouchable;
	bool isGround;
	bool isWaitingForAni;
	DWORD untouchable_start;
	bool isCheckCanFly;
	float shootTime;

	bool isJumping;
	bool isJumpHandle;
	float backup_JumpY;
	bool isPressJump;
	bool isCrouch;
	bool isPressCrouch;
	bool isRun;
	bool isSpin;
	bool isFly;
	bool isAttack;
	bool isDie;
	bool isKick;
	bool isBullet;
	Entity* holdthing;

	int walkingDirection;
	bool isWaittingPressBtn;
	int startWalkingComplete;
	bool isWalkingComplete;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	Player(float x = 0.0f, float y = 0.0f);
	static Player* GetInstance();

	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects = NULL);
	virtual void Render();

	virtual void Collision_items(vector<LPGAMEENTITY>* listitem);


	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void GetInfoForBullet(int& direct, float& playerx, float& playery) { direct = nx; playerx = x; playery = y; }
	void GetInfo(float& playerx, float& playery) { playerx = x; playery = y; }
	void startWalkingDone() { startWalkingComplete = GetTickCount(); }
	void SetDirection(int direct) { direction = direct; }
	void Setvx(float vx) { vx = vx; }
	void Setvy(float vy) { vy = vy; }
	void SetPressS(bool press) { isPressJump = press; }
	void SetPressDown(bool pres) { isPressCrouch = pres; }
	void ResetBIG();
	void ResetRACCOON();
	void ResetFIRE();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
