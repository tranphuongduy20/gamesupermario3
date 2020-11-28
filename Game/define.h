#pragma once

#include <Windows.h>  
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "debug.h" 

#include <fstream> 
#include <string>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <iostream>

#define WIN_NAME L"Super Mario Bros 3"
#define WIN_TITLE L"Super Mario Bros 3"

#define BGColor D3DCOLOR_XRGB(255,255,200)
#define BGColorCrossing D3DCOLOR_XRGB(255,255,200)
#define SCREEN_WIDTH 330
#define SCREEN_HEIGHT 270
#define BOTTOM_SCREEN 450

#define MaxFrameRate 180	//default Frame Rate is the truth

#define SCENEGAME_GAMETIMEMAX		300

#define DIRECTINPUT_VERSION       0x0800
#define KEYBOARD_BUFFER_SIZE      1024

#define MAX_SCENE_LINE 1024

#define STAGE_1						500
#define STAGE_2_1					1000
#define STAGE_2_2					1500
#define STAGE_3_1					2000
#define STAGE_3_2					2500
#define STAGE_4						3000

#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_OBJECTS			1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_SCENEFILEPATH		6
#define SCENE_SECTION_TILEMAP			7
#define SCENE_SECTION_MAPTEXTURES		12
#define SCENE_SECTION_CLEARTEXTURES			8
#define SCENE_SECTION_CLEARSPRITES			9
#define SCENE_SECTION_CLEARANIMATIONS		10
#define SCENE_SECTION_CLEARANIMATION_SETS	11


#define ANIMATION_SET_BBOX					0
#define ANIMATION_SET_PLAYER				1
#define ANIMATION_SET_PLAYERHP				11
#define ANIMATION_SET_ITEM_POWERUP			12
#define ANIMATION_SET_ITEM_GUNUP			13
#define ANIMATION_SET_BRICK					20
#define ANIMATION_SET_GATE					26

#define BOT_CAM						250//cam o bot
#define BONUS_CAM					80 //lam cam muot

enum Area
{
	TOP_LEFT_FAR,
	TOP_LEFT_NEAR,
	TOP_RIGHT_FAR,
	TOP_RIGHT_NEAR,
	BOTTOM_LEFT_FAR,
	BOTTOM_LEFT_NEAR,
	BOTTOM_RIGHT_FAR,
	BOTTOM_RIGHT_NEAR,
	OUTSIDE_AREA,
};
//Nen define thanh nhieu lop type
//Vd Zombie thuoc EntityType, EnemyType
enum EnemyType
{
	CENTIPEDE = 1,
	GOLEM = 2,
	DOMES = 3,
	GUNNER = 4
};
enum EntityType
{
	//For Special Case
	NONE = -1,

	//Bounding Box
	BBOX = 0,

	//Player Zone 1-10
	PLAYER = 1,
	MORNINGSTAR = 2,
	DAGGER = 3,
	BOOMERANG = 4,
	AXE = 5,
	WATERPOTION = 6,
	STOPWATCH = 7,
	BONE = 9,

	//UI Zone 10-20
	BLACKBOARD = 10,
	PLAYERHP = 11,
	TEXTS = 12,
	UIEXTRASHOT = 13,

	//Static Obj Zone 20-40
	BRICK = 20,
	BREAKABLEBRICK = 21,
	LEAF = 22,
	CANDLE = 23,
	MOVINGPLATFORM = 24,
	STAIRS = 25,
	GATE = 26,
	BUSH = 27,
	COIN = 28,
	MUSH = 29,
	VENUS = 30,
	GOOMBA = 31,
	KOOPA = 32,
	MONEY = 33,
	CBRICK = 34,


	//Item Zone 40-70
	POWERUP = 40,
	GUNUP = 41,
	YUMMICHICKENLEG = 42,
	MONEYBAGS = 43,
	MONEYBAGRED = 44,
	MONEYBAGWHITE = 45,
	MONEYBAGBLUE = 46,
	UPGRADEMORNINGSTAR = 47,
	CRYSTALBALL = 48,
	INVIPOTION = 49,
	ITEMDAGGER = 50,
	ITEMSTOPWATCH = 51,
	CROSS = 52,
	CROWN = 53,
	ITEMEXTRASHOT = 54,
	ITEMBOOMERANG = 55,
	ITEMAXE = 56,
	ITEMWATERPOTION = 57,

	//Effect Zone 70-80
	FIREEFFECT = 70,
	HITEFFECT = 71,
	BRICKEXPLODEEFFECT = 72,
	ADDSCOREEFFECT = 73,

	//Enemies Zone 80-100
	ENEMY = 80 ,
	//GOLEM = 80,
	//CENTIPEDE = 81,
	//DOMES = 82,

	KNIGHT = 83,
	GHOST = 84,
	RAVEN = 85,
	HUNCHMAN = 86,
	SKELETON = 87,
	TLEBAT = 88,

	//Scene Zone 100-120
	TITLESCENE = 100,
	TITLEBAT = 101,
	STARTTEXT = 102,
	INTROSCENE = 103,
	INTROSIMON = 104,
	PLAYSCENE = 105,
	MAPSTAGE1 = 106,
	MAPSTAGE2_1 = 107,
	MAPSTAGE2_2 = 108,
	MAPSTAGE3_1 = 109,
	MAPSTAGE3_2 = 110,

	//Ex
	ITEMPOKEBALL = -9,
	POKEBALL = -10
};

class define
{
};

