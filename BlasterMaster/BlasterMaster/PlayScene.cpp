#include <iostream>
#include <fstream>

#include "PlayScene.h"
#include "debug.h"
#include "Textures.h"
#include "Sprites.h"
#include "Map.h"
#include "PlayerStandingState.h"
#include "PlayerMovingState.h"
#include "BulletMovingState.h"

using namespace std;

PlayScene::PlayScene(int id, LPCWSTR filePath) :
	Scene(id, filePath) {
	keyHandler = new PlaySceneKeyHandler(this);
	gameCamera = Camera::GetInstance();
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_CLEAR_ANIMATIONS_SETS	6
#define SCENE_SECTION_OBJECTS	7
#define SCENE_SECTION_SWITCH_SCENE		8

#define MAX_SCENE_LINE 1024

void PlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	Textures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = Textures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	Sprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new Animation();
	//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	Animations::GetInstance()->Add(ani_id, ani);
}

void PlayScene::_ParseSection_SWITCHSCENE(string line) {
	vector<string> tokens = split(line);
	int id_scene = atoi(tokens[0].c_str());
	Game::GetInstance()->SwitchScene(id_scene);
}

void PlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int types = atoi(tokens[0].c_str());
	int ani_set_id = atoi(tokens[1].c_str());

	TYPE type = static_cast<TYPE>(types);


	if (type == PLAYER)
	{
		TYPE type = static_cast<TYPE>(ani_set_id);
		LPANIMATION_SET set = new AnimationSet();
		for (int i = 2; i < tokens.size(); i += 2)
		{
			int ani_id = atoi(tokens[i].c_str());
			int state = atoi(tokens[i + 1].c_str());
			STATENAME stateName = static_cast<STATENAME>(state);
			set->Add(ani_id, stateName);
		}
		DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		AnimationSets::GetInstance()->Add(type, set);
	}
	else
	{
		TYPE type = static_cast<TYPE>(ani_set_id);
		LPANIMATION_SET set = new AnimationSet();
		for (int i = 2; i < tokens.size(); i += 2)
		{
			int ani_id = atoi(tokens[i].c_str());
			int types = atoi(tokens[i + 1].c_str());
			STATEOBJECT type = static_cast<STATEOBJECT>(types);
			set->Add(ani_id, type);
		}
		DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		AnimationSets::GetInstance()->Add(type, set);
	}
}

void PlayScene::_ParseSection_CLEARANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);
	STATEOBJECT idClear = static_cast<STATEOBJECT>(atoi(tokens[0].c_str()));
	AnimationSets::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation Set %d!\n", idClear);
}

void PlayScene::_ParseSection_OBJECTS(string line) {
	vector<string> tokens = split(line);
	//(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	TYPE  type = static_cast<TYPE>(object_type);

	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	//int id_state = atoi(tokens[3].c_str());
	int width;
	int height;
	x = x * BIT; // change value to 16 bit
	y = y * BIT; // change value to 16 bit

	// General object setup

	GameObject* obj = NULL;

	AnimationSets* animation_sets = AnimationSets::GetInstance();

	switch (type) {
	case BRICK: 
		width = (int)atoi(tokens[3].c_str()) * BIT;
		height = (int)atoi(tokens[4].c_str()) * BIT;
		obj = new Brick(width, height);
		break;
	case PORTAL:
	{
		float r = atof(tokens[3].c_str()) *BIT;
		float b = atof(tokens[4].c_str()) *BIT;
		int scene_id = atoi(tokens[5].c_str());
		Portal* portal = new Portal(x, y, r, b, scene_id);
		Portals.push_back(portal);
	}
	break;
	case GOOMBA:
	{
		obj = new Goomba();
		goomba = (Goomba*)obj;
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	
	if (type != SOPHIA && type != JASON && type != PORTAL)
		obj->SetPosition(x, y);

	if (type != SOPHIA && type != JASON && type != PORTAL)
		listObjects.push_back(obj);
}

void PlayScene::Load() {
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	//curren resource section path
	int section = SCENE_SECTION_UNKNOWN;
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);
		if (line[0] == '#') continue; // skip comment lines

		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[SWITCHSCENE]") {
			section = SCENE_SECTION_SWITCH_SCENE; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[CLEARANIMATIONSETS]") {
			section = SCENE_SECTION_CLEAR_ANIMATIONS_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		// data section
		switch (section) {
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_CLEAR_ANIMATIONS_SETS: _ParseSection_CLEARANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_SWITCH_SCENE: _ParseSection_SWITCHSCENE(line); break;
		}
	}
	f.close();

	Textures::GetInstance()->Add(ID_TEX_BBOX, L"Textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);

	player->Reset();
	player->IsWalkingComplete = true;

	loadDone = true;
	//goomba->Reset();
	//playerSmall->Reset();
	//playerSmall->IsRender = false;

}

void PlayScene::Update(DWORD dt) {
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < listObjects.size(); i++) {
		coObjects.push_back(listObjects[i]);
	}
	for (size_t i = 0; i < Portals.size(); i++) {
		coObjects.push_back(Portals[i]);
	}
	for (size_t i = 0; i < listObjects.size(); i++)
	{
		listObjects[i]->Update(dt, &coObjects);
	}
	player->Update(dt, &coObjects);
	playerSmall->Update(dt, &coObjects);
	
	// create bullet
	// SOPHIA
	if (player->IsFiring && GetTickCount() - player->timeStartAttack >= 180) {
		bullet = new Bullet();
		bullet->typeBullet = BULLET_SMALL;
		if (!player->IsUp) {
			if (player->nx > 0) {
				bullet->SetPosition(player->x + SOPHIA_BBOX_WIDTH, player->y + 7 / SOPHIA_BBOX_HEIGHT);
				bullet->ChangeAnimation(BULLET_SMALL_MOVING_RIGHT);
			}
			else {
				bullet->SetPosition(player->x, player->y + 7 / SOPHIA_BBOX_HEIGHT);
				bullet->ChangeAnimation(BULLET_SMALL_MOVING_LEFT);
			}
		}
		else {
			if (player->nx != 0) {
				bullet->SetPosition(player->x + SOPHIA_BBOX_WIDTH / 3, player->y);
				bullet->ChangeAnimation(BULLET_SMALL_MOVING_UP);
			}
		}
		if (bullets.size() < 9) {
			bullets.push_back(bullet);
		}
	}
	// JASON
	if (playerSmall->IsFiring && GetTickCount() - playerSmall->timeStartAttack >= 180) {
		bullet = new Bullet();
		bullet->typeBullet = JASON_BULLET_SMALL;
		if (playerSmall->nx > 0) {
			bullet->SetPosition(playerSmall->x + JASON_BBOX_WIDTH, playerSmall->y + JASON_BBOX_HEIGHT / 3);
			bullet->ChangeAnimation(JASON_BULLET_SMALL_MOVING);
		}
		else {
			bullet->SetPosition(playerSmall->x, playerSmall->y + JASON_BBOX_HEIGHT / 3);
			bullet->ChangeAnimation(JASON_BULLET_SMALL_MOVING);
		}

		if (bullets.size() < 3) {
			bullets.push_back(bullet);
		}
	}
	// update bullet
	for (int i = 0; i < bullets.size(); i++) {
		if (Allow[SOPHIA]) {
			if (bullets[i]->GetX() >= player->x + 150.0f || bullets[i]->GetX() <= player->x - 150.0f) {
				bullets.erase(bullets.begin() + i);
			}
			else if (bullets[i]->GetY() <= player->y - 100.0f) {
				bullets.erase(bullets.begin() + i);
			}
			else if (bullets[i]->GetStateObject() == BULLET_SMALL_HIT) {
				if (bullets[i]->CurAnimation->isLastFrame) {
					bullets[i]->CurAnimation->isLastFrame = false;
					bullets.erase(bullets.begin() + i);
				}
				else {
					bullets.erase(bullets.begin() + i);
				}
			}
		}
		else if (Allow[JASON]) {
			if (bullets[i]->GetX() >= playerSmall->x + 150.0f || bullets[i]->GetX() <= playerSmall->x - 150.0f) {
				bullets.erase(bullets.begin() + i);
			}
			else if (bullets[i]->GetY() <= playerSmall->y - 100.0f) {
				bullets.erase(bullets.begin() + i);
			}
			else if (bullets[i]->GetStateObject() == BULLET_SMALL_HIT) {
				if (bullets[i]->CurAnimation->isLastFrame) {
					bullets[i]->CurAnimation->isLastFrame = false;
					bullets.erase(bullets.begin() + i);
				}
			}
		}
	}

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(dt, &coObjects);
	}
	
	// skip the rest if scene was already unloaded (Car::Update might trigger PlayScene::Unload)

	// Update camera to follow player
	if (!gameCamera->isChangingMap) {
		gameCamera->Update();
	}
	else {
		if (player->nx < 0) {

			if ((gameCamera->camPosX + SCREEN_WIDTH / 2) > player->x) {
				//Camera::GetInstance()->camPosX -= 0.2 * dt;
				gameCamera->SetCamPos(gameCamera->camPosX - 0.2 * dt, gameCamera->camPosY);
				DebugOut(L"%d  ", gameCamera->camPosX);
			}
			else {
				Camera::GetInstance()->isChangingMap = false;
			}
		}
		else {
			if ((gameCamera->camPosX + SCREEN_WIDTH / 2) < player->x) {
				//Camera::GetInstance()->camPosX -= 0.2 * dt;
				gameCamera->SetCamPos(gameCamera->camPosX + 0.2 * dt, gameCamera->camPosY);
				DebugOut(L"%d  ", gameCamera->camPosX);
			}
			else {
				gameCamera->isChangingMap = false;
			}
		}
	}
}

void PlayScene::ChangeScene(float dt) {
	Camera::GetInstance()->isChangingMap = true;
	if (Camera::GetInstance()->GetCamPosX() + SCREEN_WIDTH / 2 < player->x) {
		Camera::GetInstance()->SetCamPos(player->x = 0.1 * dt - SCREEN_WIDTH / 2, player->y - SCREEN_HEIGHT / 2);
	}
}

void PlayScene::Render() {
	Map::GetInstance()->Render();

	for (int i = 0; i < listObjects.size(); i++) {
		listObjects[i]->Render();
	}
	for (int i = 0; i < Portals.size(); i++) {
		Portals[i]->Render();
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}
	player->Render();
	playerSmall->Render();
	//goomba->Render();
}

void PlayScene::Unload() {
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	for (int i = 0; i < Portals.size(); i++)
		delete Portals[i];
	listObjects.clear();
	Portals.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void PlaySceneKeyHandler::OnKeyDown(int KeyCode){
	Sophia* sophia = ((PlayScene*)scene)->GetSophia();
	Jason* jason = ((PlayScene*)scene)->GetJason();
	if (Allow[SOPHIA])
	{
		keyCode[KeyCode] = true;
		player->OnKeyDown(KeyCode);
	}
	else if (Allow[JASON])
	{
		keyCode[KeyCode] = true;
		playerSmall->OnKeyDown(KeyCode);
	}
}

void PlaySceneKeyHandler::OnKeyUp(int KeyCode) {
	Sophia* sophia = ((PlayScene*)scene)->GetSophia();
	Jason* jason = ((PlayScene*)scene)->GetJason();
	
	if (Allow[SOPHIA]) {
		keyCode[KeyCode] = false;
		player->OnKeyUp(KeyCode);
	}
	else if (Allow[JASON]) {
		keyCode[KeyCode] = false;
		playerSmall->OnKeyUp(KeyCode);
	}
}

void PlaySceneKeyHandler::KeyState(BYTE* states) {

}