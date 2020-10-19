#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
//#include "SceneManager.h"
#include "Camera.h"
#include "Sophia.h"
#include "Bullet.h"

#include "GlobalConfig.h"


class PlayScene : public Scene {
protected:
	Bullet* bullet;
	Sophia* sophia;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPBULLET> listBullets;
	Camera* gameCamera;
	//Sophia* sophia;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	//Get stage objects' link and tilemap resources
	//void _ParseSection_SCENEFILEPATH(string line);
public:
	PlayScene(int id, LPCWSTR filePath);
	/*void LoadBaseObjects();
	void LoadBaseTextures();*/
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Sophia* GetPlayer() { return sophia; }

	//friend class PlaySceneKeyHandler;
};

class PlaySceneKeyHandler : public SceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	PlaySceneKeyHandler(Scene* s) :SceneKeyHandler(s) {};
};

