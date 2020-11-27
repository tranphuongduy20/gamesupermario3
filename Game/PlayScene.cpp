#include "PlayScene.h"
#include "Textures.h"

#define OBJECT_TYPE_MARIO		0
#define OBJECT_TYPE_BRICK		1
#define OBJECT_TYPE_GATE		2
#define OBJECT_TYPE_KOOPA		3
#define OBJECT_TYPE_CBRICK		4
#define OBJECT_TYPE_MUSHROOM	5
#define OBJECT_TYPE_LEAF		6
#define	OBJECT_TYPE_VENUS_RED	7
#define OBJECT_TYPE_VENUS_NO_FIRE 8
#define OBJECT_TYPE_VENUS_GREEN	9
#define OBJECT_TYPE_COIN		10
#define OBJECT_TYPE_GOOMBA		11
//#define OBJECT_TYPE_CENTIPEDE	10
//#define OBJECT_TYPE_GOLEM		11
//#define OBJECT_TYPE_GUNNER	12
//#define OBJECT_TYPE_DOMES		13
//#define HUD_Y					20

PlayScene::PlayScene() : Scene()
{
	keyHandler = new PlayScenceKeyHandler(this);
	LoadBaseObjects();
	ChooseMap(STAGE_1);
}

void PlayScene::LoadBaseObjects()
{
	texturesFilePath = ToLPCWSTR("Resources/Scene/base.txt");
	LoadBaseTextures();
	if (player == NULL)
	{
		player = new Player(200, 300);
		DebugOut(L"[INFO] player CREATED! \n");
	}
	if (bullet1 == NULL)
	{
		bullet1 = new MarioBullet();
		listBullets.push_back(bullet1);
		DebugOut(L"[INFO] Bullet1 CREATED! \n");
	}
	if (bullet2 == NULL)
	{
		bullet2 = new MarioBullet();
		listBullets.push_back(bullet2);
		DebugOut(L"[INFO] Bullet2 CREATED! \n");
	}
	if (tail == NULL)
	{
		tail = new RaccoonTail();
		DebugOut(L"[INFO] tail CREATED! \n");
	}
	/*if (gameHUD == NULL)
	{
		gameHUD = new HUD(player->GetHealth(), player->GetgunDam());
		DebugOut(L"[INFO] HUD CREATED! %d \n", player->GetHealth());
	}
	gameHUD = new HUD(player->GetHealth(), player->GetgunDam());
	
	if (bullet3 == NULL)
	{
		bullet3 = new MainJasonBullet();
		listBullets.push_back(bullet3);
		DebugOut(L"[INFO] Bullet3 CREATED! \n");
	}
	if (supBullet == NULL)
	{
		supBullet = new ElectricBullet();
		DebugOut(L"[INFO] supBullet CREATED! \n");
	}
	if (powerUp == NULL)
	{
		powerUp = new PowerUp(100,150);
		listItems.push_back(powerUp);
		DebugOut(L"[INFO] powerUp CREATED! \n");
	}
	if (gunUp == NULL)
	{
		gunUp = new GunUp(200, 150);
		listItems.push_back(gunUp);
		DebugOut(L"[INFO] gunUp CREATED! \n");
	}*/
}

void PlayScene::ChooseMap(int whatMap)
{
	idStage = whatMap;
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	int convertSimple = idStage / STAGE_1;
	sceneFilePath = listSceneFilePath[convertSimple - 1];
	LoadSceneObjects();
}

void PlayScene::Update(DWORD dt)
{
#pragma region Camera
	Game* game = Game::GetInstance();
	float cx, cy;
	player->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	/*if (player->Getx() + SCREEN_WIDTH / 2  >= mapWidth)
	{
		cx -= mapWidth - SCREEN_WIDTH / 2;
	}
	else
	{
		if (player->Getx() < SCREEN_WIDTH / 2)
			cx = 0;
		else
			cx -= SCREEN_WIDTH / 2;
	}*/
	if (player->Gety() < ((SCREEN_HEIGHT / 4) - BONUS_CAM/2))
		cy = 0;
	else if (player->Gety() <= (((float)mapHeight / 2) - BONUS_CAM))
		cy -= SCREEN_HEIGHT / 5;
	else if (player->Gety() > (((float)mapHeight / 2) - BONUS_CAM))
		cy = BOT_CAM;

	if (cx < 0)
	{
		cx = 0;
	}
	else if (cx + SCREEN_WIDTH >= tilemap->GetWidthTileMap())
	{
		cx = tilemap->GetWidthTileMap() - SCREEN_WIDTH;
	}

	game->SetCamPos(cx, cy);
#pragma endregion
	if (listItems.size() > 0)
		PlayerCollideItem();
	PlayerGotGate();
	PlayerTouchItem();
	PlayerTailAttackEnemy();

#pragma region Objects Updates
	vector<LPGAMEENTITY> coObjects;
	vector<LPGAMEENTITY> fullObjects;
	vector<LPGAMEENTITY> enemies;
	vector<LPGAMEENTITY> coObjects2;
	for (int i = 0; i < listObjects.size(); i++)
	{
		coObjects.push_back(listObjects[i]);
		fullObjects.push_back(listObjects[i]);
	}
	for (int i = 0; i < listEnemies.size(); i++)
	{
		fullObjects.push_back(listEnemies[i]);
		enemies.push_back(listEnemies[i]);
	}
	player->Update(dt, &fullObjects);
	for (int i = 0; i < listBullets.size(); i++)
		listBullets[i]->Update(dt, &fullObjects);
	for (int i = 0; i < listEnemies.size(); i++)
		listEnemies[i]->Update(dt, &coObjects);
	for (int i = 0; i < listObjects.size(); i++)
	{
		if (dynamic_cast<Brick*>(listObjects[i]))
		{ }
		else
			listObjects[i]->Update(dt, &fullObjects);
	}
	for (int i = 0; i < listLeaf.size(); i++)
		listLeaf[i]->Update(dt, &coObjects2);
	for (int i = 0; i < listitems.size(); i++)
		listitems[i]->Update(dt, &coObjects);
	tail->Update(dt, &fullObjects, player->x, player->y);
#pragma endregion

}

void PlayScene::PlayerTailAttackEnemy()
{
	for (UINT i = 0; i < listEnemies.size(); i++)
	{
		if (listEnemies[i]->GetType() == EntityType::GOOMBA)
		{
			if (tail->IsCollidingObject(listEnemies[i]))
				listEnemies[i]->SetState(GOOMBA_STATE_DIE_FLY);
			//if (player->)
		}
		else if (listEnemies[i]->GetType() == EntityType::KOOPA)
		{
			if (tail->IsCollidingObject(listEnemies[i]))
				listEnemies[i]->SetState(KOOPA_STATE_DIE_FLY);
		}
	}
}

bool PlayScene::PlayerPassingStage(float DistanceXWant, int directionGo)
{
	if (directionGo == 1)	//cua o ben phai
	{
		if (player->Getx() < DistanceXWant)
		{
			player->SetDirection(directionGo);
			player->SetState(MARIO_STATE_IDLE);
			return false;
		}
	}
	else
		if (directionGo == -1)	//cua o ben trai
		{
			if (player->Getx() > DistanceXWant)
			{
				player->SetDirection(directionGo);
				player->SetState(MARIO_STATE_IDLE);
				return false;
			}
		}
	return true;
}

void PlayScene::PlayerTouchItem()
{
	for (UINT i = 0; i < listitems.size(); i++)
	{ 
		if (listitems[i]->GetType() == EntityType::MUSH)
		{
			if (player->IsCollidingObject(listitems[i]) && player->level == MARIO_LEVEL_SMALL)
			{
				Mushroom* mush = dynamic_cast<Mushroom*>(listitems[i]);
				if (mush->isOnTop == false)
					listitems[i]->SetState(MUSHROOM_STATE_WALKING);
				else
				{
					player->SetLevel(MARIO_LEVEL_BIG);
					player->y -= 13;
					mush->isDone = true;
				}
				//player->vy = 0;
			}
		}
	}
	for (UINT i = 0; i < listLeaf.size(); i++)
	{

		if (listLeaf[i]->GetType() == EntityType::LEAF && player->level == MARIO_LEVEL_BIG)
		{
			if (player->IsCollidingObject(listLeaf[i]))
			{
				Leaf* leaf = dynamic_cast<Leaf*>(listLeaf[i]);
				if (leaf->isOnTop == false)
					listLeaf[i]->SetState(LEAF_STATE_WALKING);
				else
				{
					player->SetLevel(MARIO_LEVEL_RACCOON);
					leaf->isDeath = true;
				}
			}
		}
	}
}

void PlayScene::PlayerGotGate()
{
	Game* game = Game::GetInstance();
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetType() == EntityType::GATE)
		{
			if (player->IsCollidingObject(listObjects[i]))
			{
        		Gate* gate = dynamic_cast<Gate*>(listObjects[i]);
				int tempMap = gate->GetIdScene() * STAGE_1;
				float tempx = gate->newPlayerx;
				float tempy = gate->newPlayery;
				int tempState = gate->newPlayerState;
				bool tempNeed = gate->isNeedResetCam;
				/*if (idStage == STAGE_1)
				{
					if (!PlayerPassingStage(listObjects[i]->Getx() + 20.0f, 1))
						return;
				}
				else if (idStage == STAGE_2_2 && tempMap == STAGE_3_1)
				{
					if (!PlayerPassingStage(listObjects[i]->Getx(), -1))
						return;
				}
				else if (idStage == STAGE_3_2 && tempMap == STAGE_4)
				{
					if (!PlayerPassingStage(listObjects[i]->Getx() + 10.0f, 1))
						return;
				}*/
				Unload();
				if(tempNeed)
					game->SetCamPos(0, 0);
				ChooseMap(tempMap);
				player->SetPosition(tempx, tempy);
				player->Setvx(0);
				player->Setvy(0);
				player->SetState(tempState);
			}
		}
	}
}

void PlayScene::PlayerCollideItem()
{
	for (UINT i = 0; i < listItems.size(); i++)
	{
		if (!listItems[i]->GetIsDone())
		{
			if (player->IsCollidingObject(listItems[i]))
			{
				switch (listItems[i]->GetType())
				{
				/*case EntityType::POWERUP:
				{
					if (player->GetHealth() + POWER_HP_RESTORE <= MAX_HEALTH)
						player->AddHealth(POWER_HP_RESTORE);
					else
						player->SetHealth(MAX_HEALTH);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::GUNUP:
				{
					if (player->GetgunDam() + GUN_HP_RESTORE <= MAX_HEALTH)
						player->AddgunDam(GUN_HP_RESTORE);
					else
						player->SetgunDam(MAX_HEALTH);
					listItems[i]->SetIsDone(true);
					break;
				}*/
				default:
					break;
				}
			}
		}
	}
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	Player* player = ((PlayScene*)scence)->player;
	Bullet* bullet1 = ((PlayScene*)scence)->bullet1;
	Bullet* bullet2 = ((PlayScene*)scence)->bullet2;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listitems = ((PlayScene*)scence)->listitems;
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;
	vector<LPGAMEENTITY> listEnemies = ((PlayScene*)scence)->listEnemies;
	vector<LPGAMEENTITY> listLeaf = ((PlayScene*)scence)->listLeaf;
	vector<LPBULLET> listBullets = ((PlayScene*)scence)->listBullets;
	float x, y;
	int direction;
	player->GetInfoForBullet(direction, x, y);
	switch (KeyCode)
	{
	case DIK_S:
		player->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_Z:
		player->isAttack = true;
		break;
	case DIK_B:
		player->ResetBIG();
		break;
	case DIK_N:
		player->ResetRACCOON();
		break;
	case DIK_M:
		player->ResetFIRE();
		break;
	case DIK_A:
		player->isAttack = true;
		if (player->level == MARIO_LEVEL_FIRE)
		{
			player->isBullet = true;
			player->shootTime = GetTickCount64();
			for (int i = 0; i < listBullets.size(); i++)
			{
				if (listBullets[i]->isDone == true)
				{
					listBullets[i]->Fire(direction, x, y);
					break;
				}
			}
		}
		else if (player->level == MARIO_LEVEL_RACCOON)
		{
			//playScene->tail->Attack(x - 8, y + 19);
			playScene->tail->Attack();
		}
		break;
	case DIK_F6:
		for (int i = 0; i < listObjects.size(); i++)
		{
			if (listObjects[i]->GetBBARGB() == 0)
				listObjects[i]->SetBBARGB(200);
			else
				listObjects[i]->SetBBARGB(0);
		}
		for (int i = 0; i < listEnemies.size(); i++)
		{
			if (listEnemies[i]->GetBBARGB() == 0)
				listEnemies[i]->SetBBARGB(200);
			else
				listEnemies[i]->SetBBARGB(0);
		}
		for (int i = 0; i < listLeaf.size(); i++)
		{
			if (listLeaf[i]->GetBBARGB() == 0)
				listLeaf[i]->SetBBARGB(200);
			else
				listLeaf[i]->SetBBARGB(0);
		}
		for (int i = 0; i < listitems.size(); i++)
		{
			if (listitems[i]->GetBBARGB() == 0)
				listitems[i]->SetBBARGB(200);
			else
				listitems[i]->SetBBARGB(0);
		}


		if (player->GetBBARGB() == 0)
			player->SetBBARGB(200);
		else
			player->SetBBARGB(0);

		if (bullet1->GetBBARGB() == 0)
			bullet1->SetBBARGB(200);
		else
			bullet1->SetBBARGB(0);

		if (bullet2->GetBBARGB() == 0)
			bullet2->SetBBARGB(200);
		else
			bullet2->SetBBARGB(0);
		break;
	}
}

void PlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	Player* player = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObj = ((PlayScene*)scence)->listObjects;
	float posX, posY;
	switch (KeyCode)
	{
	case DIK_S:
		player->SetPressS(false);
		break;
	case DIK_RIGHT:
		player->startWalkingDone();
		player->walkingDirection = 1;
		break;
	case DIK_LEFT:
		player->startWalkingDone();
		player->walkingDirection = -1;
		break;
	case DIK_DOWN:
		player->isCrouch = false;
		break;
	case DIK_A:
		if (player->holdthing)
		{
			player->holdthing->nx = -player->nx;
			player->isKick = true;
			player->holdthing->SetState(KOOPA_STATE_TROOPA_SPIN);
		}
		player->isRun = false;
		break;
	}
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{
	Player* player = ((PlayScene*)scence)->player;
	Bullet* bullet1 = ((PlayScene*)scence)->bullet1;
	Bullet* bullet2 = ((PlayScene*)scence)->bullet2;

	//Bullet* bullet3 = ((PlayScene*)scence)->bullet3;
	//Bullet* supBullet = ((PlayScene*)scence)->supBullet;

	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;
	vector<LPGAMEITEM> listItems = ((PlayScene*)scence)->listItems;
	vector<LPBULLET> listBullets = ((PlayScene*)scence)->listBullets;
	if (player->GetState() == MARIO_STATE_DIE) return;

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT) && !player->isWalkingComplete)
	{
		player->SetState(MARIO_STATE_WALKING_RIGHT);
		//player->isKick = false;
		if (Game::GetInstance()->IsKeyDown(DIK_A))
		{
			player->isRun = true;
		}
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_LEFT) && !player->isWalkingComplete)
	{
		player->SetState(MARIO_STATE_WALKING_LEFT);
		//player->isKick = false;
		if (Game::GetInstance()->IsKeyDown(DIK_A))
		{
			player->isRun = true;
		}
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		player->SetState(MARIO_STATE_CROUCH);
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_Z))
	{
		player->SetState(MARIO_STATE_SPIN);
	}
	else
	{
		if (player->isJumping)
			return;
		player->SetState(MARIO_STATE_IDLE);
		player->isCrouch = false;
	}

	if (Game::GetInstance()->IsKeyDown(DIK_S))
	{
		player->SetPressS(true);
	}

}

void PlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void PlayScene::_ParseSection_CLEARTEXTURES(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CTextures::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Texture %d!\n", idClear);
}

void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str()) + l;
	int b = atoi(tokens[4].c_str()) + t;
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void PlayScene::_ParseSection_CLEARSPRITES(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CSprites::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Sprite %d!\n", idClear);
}

void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void PlayScene::_ParseSection_CLEARANIMATIONS(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	//CAnimations::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation %d!\n", idClear);
}

void PlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void PlayScene::_ParseSection_CLEARANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	//CAnimationSets::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation Set %d!\n", idClear);
}

void PlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	wstring filePath_texture = ToWSTR(tokens[1]);
	wstring filePath_data = ToWSTR(tokens[2]);
	int num_row_on_texture = atoi(tokens[3].c_str());
	int num_col_on_textture = atoi(tokens[4].c_str());
	int num_row_on_tilemap = atoi(tokens[5].c_str());
	int num_col_on_tilemap = atoi(tokens[6].c_str());
	int tileset_width = atoi(tokens[7].c_str());
	int tileset_height = atoi(tokens[8].c_str());
	//int widthGrid = atoi(tokens[9].c_str());
	//int heightGrid = atoi(tokens[10].c_str());
	//boardscore = new BoardScore();
	//grid = new Grid();
	//grid->Resize(widthGrid, heightGrid);
	//grid->PushGrid(allObject);
	tilemap = new TileMap(ID, filePath_texture.c_str(), filePath_data.c_str(), num_row_on_texture, num_col_on_textture, num_row_on_tilemap, num_col_on_tilemap, tileset_width, tileset_height);
}

void PlayScene::_ParseSection_SCENEFILEPATH(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	listSceneFilePath.push_back(ToLPCWSTR(tokens[0]));
	mapWidth = atoi(tokens[1].c_str());
	mapHeight = atoi(tokens[2].c_str());
	//Hien tai chi lay mapWidth/Height cua list cuoi cung` :P co the dem vo tung file scene rieng de phan biet (hoac khong can, camera co chay toi duoc dau)
}

void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	Entity* obj = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new Player(x, y);
		player = (Player*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK:
	{
		obj = new Brick(atof(tokens[4].c_str()),atof(tokens[5].c_str()));
		obj->SetPosition(x, y);
		
		listObjects.push_back(obj);
		DebugOut(L"[test] add brick !\n");
		break;
	}
	case OBJECT_TYPE_CBRICK:
	{
		obj = new CBrick(x,y,atof(tokens[4].c_str()), atof(tokens[5].c_str()));
		//obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		
		obj->SetAnimationSet(ani_set);
		listObjects.push_back(obj);
		DebugOut(L"[test] add cbrick !\n");
		break;
	}
	case OBJECT_TYPE_KOOPA:
	{
		obj = new Koopa();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add koopa !\n");
		break;
	}
	case OBJECT_TYPE_VENUS_RED:
	{
		obj = new Venus(player, 1);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add venus !\n");
		break;
	}
	case OBJECT_TYPE_VENUS_GREEN:
	{
		obj = new Venus(player, 2);
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add venus !\n");
		break;
	}
	case OBJECT_TYPE_VENUS_NO_FIRE:
	{
		obj = new VenusNoFire();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add venus !\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA:
	{
		obj = new Goomba();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listEnemies.push_back(obj);
		DebugOut(L"[test] add goomba !\n");
		break;
	}
	case OBJECT_TYPE_MUSHROOM:
	{
		obj = new Mushroom(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listitems.push_back(obj);
		DebugOut(L"[test] add mushroom !\n");
		break;
	}
	case OBJECT_TYPE_LEAF:
	{
		obj = new Leaf(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listLeaf.push_back(obj);
		//listObjects.push_back(obj);
		DebugOut(L"[test] add leaf !\n");
		break;
	}
	case OBJECT_TYPE_COIN:
	{
		obj = new Coin(atof(tokens[4].c_str()), atof(tokens[5].c_str()));
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		listObjects.push_back(obj);
		DebugOut(L"[test] add coin !\n");
		break;
	}
	case OBJECT_TYPE_GATE:
	{
		int switchId = atoi(tokens[3].c_str());
		float playerPosX = atoi(tokens[4].c_str());
		float playerPosY = atoi(tokens[5].c_str());
		int playerState = atoi(tokens[6].c_str());
		int isResetCamera = atoi(tokens[7].c_str());
		obj = new Gate(x, y, switchId, playerPosX, playerPosY, playerState, isResetCamera);
		listObjects.push_back(obj);
		DebugOut(L"[test] add gate !\n");
		break;
	}

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

}

void PlayScene::LoadBaseTextures()
{
	DebugOut(L"[INFO] Start loading TEXTURES resources from : %s \n", texturesFilePath);

	ifstream f;
	f.open(texturesFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]")
		{
			section = SCENE_SECTION_OBJECTS;
			continue;
		}
		if (line == "[SCENE]") {
			section = SCENE_SECTION_SCENEFILEPATH; continue;
		}
		/*if (line == "[MAPTEXTURES]") {
			section = SCENE_SECTION_MAPTEXTURES; continue;
		}*/

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_SCENEFILEPATH: _ParseSection_SCENEFILEPATH(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading TEXTURES resources %s\n", texturesFilePath);
}

void PlayScene::LoadSceneObjects()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[CLEARTEXTURES]") {
			section = SCENE_SECTION_CLEARTEXTURES; continue;
		}
		if (line == "[CLEARSPRITES]") {
			section = SCENE_SECTION_CLEARSPRITES; continue;
		}
		if (line == "[CLEARANIMATIONS]") {
			section = SCENE_SECTION_CLEARANIMATIONS; continue;
		}
		if (line == "[CLEARANIMATIONSETS]") {
			section = SCENE_SECTION_CLEARANIMATION_SETS; continue;
		}
		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_CLEARTEXTURES: _ParseSection_CLEARTEXTURES(line); break;
		case SCENE_SECTION_CLEARSPRITES: _ParseSection_CLEARSPRITES(line); break;
		case SCENE_SECTION_CLEARANIMATIONS: _ParseSection_CLEARANIMATIONS(line); break;
		case SCENE_SECTION_CLEARANIMATION_SETS: _ParseSection_CLEARANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP:	_ParseSection_TILEMAP(line); break;
		}
	}

	f.close();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\bbox.png", D3DCOLOR_XRGB(255, 255, 0));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Unload()
{
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	listObjects.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

//Item* PlayScene::RandomItem(float x, float y)
//{
//
//	int bagrandom = rand() % 100;
//	int random = rand() % 100;
//	if (random <= 30)
//		return new PowerUp(x, y);
//	else if (30 < random && random <= 60)
//		return new PowerUp(x, y);
//	else if (60< random && random <= 100)
//		return new PowerUp(x, y);
//}
//
//Item* PlayScene::DropItem(EntityType createrType, float x, float y, int idCreater)
//{
//	if (createrType == ENEMY)
//		return new PowerUp(x, y);
//	return new PowerUp(x, y);
//}

void PlayScene::Render()
{
	tilemap->Draw();
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Render();
	for (int i = 0; i < listitems.size(); i++)
		listitems[i]->Render();
	for (int i = 0; i < listLeaf.size(); i++)
		listLeaf[i]->Render();
	for (int i = 0; i < listEnemies.size(); i++)
		listEnemies[i]->Render();
	player->Render();
	//supBullet->Render();
	for (int i = 0; i < listBullets.size(); i++)
		listBullets[i]->Render();
	tail->Render();
	//gameHUD->Render(player);
}

