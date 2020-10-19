#include <iostream>
#include <fstream>

#include "PlayScene.h"
#include "debug.h"
#include "Textures.h"
#include "Sprites.h"
#include "Map.h"
#include "PlayerStandingState.h"

using namespace std;

PlayScene::PlayScene(int id, LPCWSTR filePath) :
	Scene(id, filePath) {
	keyHandler = new PlaySceneKeyHandler(this);
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_CAR			0
#define OBJECT_TYPE_BRICK		1

#define MAX_SCENE_LINE 1024

//void PlayScene::LoadBaseObjects() {
//	if (car == NULL) {
//		car = player;
//		DebugOut(L"[INFO] CAR CREATED! \n");
//	}
//	gameCamera = Camera::GetInstance();
//}

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

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new Animation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}
	//DebugOut(L"AddAniMation id: %d", ani_id);
	Animations::GetInstance()->Add(ani_id, ani);
}

void PlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new AnimationSet();

	Animations* animations = Animations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	AnimationSets::GetInstance()->Add(ani_set_id, s);
}

void PlayScene::_ParseSection_OBJECTS(string line) {
	vector<string> tokens = split(line);

	//(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	AnimationSets* animation_sets = AnimationSets::GetInstance();

	GameObject* obj = NULL;
	switch (object_type) {
		// switch cac' loai quai vat va brick
	case OBJECT_TYPE_CAR:
		if (sophia != NULL)
		{
			DebugOut(L"[ERROR] CAR object was created before!\n");
			return;
		}
		obj = player;
		sophia = (Sophia*)obj;
		sophia->ChangeAnimation(new PlayerStandingState());
		//player->SetPosition(x, y);
		//sophia = (Sophia*)obj; // maybe error

		DebugOut(L"[INFO] CAR object created!\n");
		break;
	case OBJECT_TYPE_BRICK: obj = new Brick(); break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	obj->SetPosition(x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
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
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
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
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}
	f.close();

	Textures::GetInstance()->Add(ID_TEX_BBOX, L"Textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Update(DWORD dt) {
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < listObjects.size(); i++){
		coObjects.push_back(listObjects[i]);
	}
	for (size_t i = 1; i < listObjects.size(); i++)
	{
		listObjects[i]->Update(dt, &coObjects);
	}
	sophia->Update(dt, &coObjects);
	// skip the rest if scene was already unloaded (Car::Update might trigger PlayScene::Unload)
	//if (sophia == NULL) return;

	// Update camera to follow player

	float cx, cy;
	player->GetPosition(cx, cy);

	Game* game = Game::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	gameCamera = Camera::GetInstance();
	gameCamera->SetCamPos(cx, 0.0f/*cy*/);
}

void PlayScene::Render() {
	for (int i = 0; i < listObjects.size(); i++) {
		listObjects[i]->Render();
	}
}

void PlayScene::Unload() {
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];

	listObjects.clear();
	//player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void PlaySceneKeyHandler::OnKeyDown(int KeyCode){
	Sophia* sophia = ((PlayScene*)scene)->GetPlayer();
	keyCode[KeyCode] = true;
	sophia->OnKeyDown(KeyCode);
}

void PlaySceneKeyHandler::OnKeyUp(int KeyCode) {
	Sophia* sophia = ((PlayScene*)scene)->GetPlayer();
	keyCode[KeyCode] = true;
	sophia->OnKeyUp(KeyCode);
}

void PlaySceneKeyHandler::KeyState(BYTE* states) {

}