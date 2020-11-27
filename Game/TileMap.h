#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "debug.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Game.h"
#include "Camera.h"

#define SCREEN_WIDTH 350

class TileMap
{
	CSprites* sprites = CSprites::GetInstance();
	LPCWSTR filePath_data;
	LPCWSTR filePath_texture;

	int id;
	int num_row_on_tilemap, num_col_on_tilemap;
	int num_row_on_texture, num_col_on_textture;
	int tileset_width, tileset_height;

	vector<vector<LPSPRITE>> tilemap;

public:
	TileMap(int ID, LPCWSTR filePath_texture, LPCWSTR filePath_data, int num_row_on_texture, int num_col_on_textture, int num_row_on_tilemap, int num_col_on_tilemap, int tileset_width = 48, int tileset_height = 48);
	~TileMap();
	int GetWidthTileMap();
	void Load();
	void LoadMap();
	void Draw();
};

