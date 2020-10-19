#pragma once
#include <d3dx9.h>
#include "KeyboardHandler.h"

class Scene {
protected:
	KeyboardHandler* keyHandler;
	int id;
	LPCWSTR sceneFilePath;
public:
	Scene(int id, LPCWSTR filePath);

	KeyboardHandler* GetKeyEventHandler() { return keyHandler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef Scene* LPSCENE;

class SceneKeyHandler :public KeyboardHandler {
protected:
	Scene* scene;
public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	SceneKeyHandler(Scene* s) :KeyboardHandler() { scene = s; }
};



