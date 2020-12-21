#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "DamageBrick.h"
#include "Stair.h"
#include "Camera.h"
#include "HUD.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "Bullet.h"
#include "Portal.h"
#include "Gate.h"
#include "Orb1.h"
#include "Worm.h"
#include "Floater.h"
#include "Power.h"
#include "Hover.h"
#include "Thunder.h"
#include "Dome.h"
#include "Jumper.h"
#include "Insect.h"
#include "Orb2.h"
#include "Skull.h"
#include "Mine.h"
#include "Canon.h"
#include "Teleporter.h"
#include "EyeBall.h"
#include "WhiteBullet.h"
#include "EnemyBullet.h"
#include "Boss.h"

#include "Intro.h"
#include "End.h"
#include "End2.h"
#include "End3.h"

#include "Grid.h"
#include "GlobalConfig.h"
#include "Sound.h"

using namespace std;

class PlayScene : public Scene {
protected:
	CIntro* Intro;
	End* end;
	End2* end2;
	End3* end3;
	Camera* gameCamera;
	vector<Bullet*> listBullets;
	vector<EnemyBullet*> listEnemyBullets;
	vector<LPGAMEOBJECT> listObjects;
	vector<Enemy*> listEnemies;
	vector<Item*> listItems;
	vector<End*> listEnds;
	vector<End2*> listEnd2;
	vector<End3*> listEnd3;
	Power* power;
	Thunder* thunder;
	Hover* hover;
	int item = 0;
	DWORD timeEnter = TIME_DEFAULT;
	DWORD timeBoss = TIME_DEFAULT;
	DWORD timeEnd = TIME_DEFAULT;
	float movingX = 0;
	//Sophia* sophia;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_CLEARANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_SWITCHSCENE(string line);
	void _ParseSection_MAP(string line);

	//Get stage objects' link and tilemap resources
	//void _ParseSection_SCENEFILEPATH(string line);
public:

	vector<LPGAMEOBJECT> HolderObjects;
	vector<LPGAMEOBJECT> staticObject;

	PlayScene(int id, LPCWSTR filePath);
	/*void LoadBaseObjects();
	void LoadBaseTextures();*/
	virtual void Load();
	virtual void Update(DWORD dt);
	void UpdateBullet(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void ChangeScene();
	bool randomItem(){
		return 0 + (rand() % (1 - 0 + 1)) == 1;
	}
	//friend class PlaySceneKeyHandler;
};

class PlaySceneKeyHandler : public SceneKeyHandler{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	PlaySceneKeyHandler(Scene* s) :SceneKeyHandler(s) {};
};

