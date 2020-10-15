#pragma once


#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#include "Textures.h"
#include "Sprites.h"
/*
	Sprite animation
*/
class CSprite;
class CAnimationFrame
{
	CSprite* sprite;
	DWORD time;

public:
	CAnimationFrame(CSprite* sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	CSprite* GetSprite() { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;

public:
	int currentFrame;
	bool isLastFrame;
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; isLastFrame = false; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255, int idFrame = 0, bool renderOneFrame = false, bool rev = false);
	int GetCurrentFrame() { return this->currentFrame; }
	void SetCurrentFrame(int currentFrame) { this->currentFrame = currentFrame; }
};

typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, CAnimation*> animations;

public:
	void Add(int id, CAnimation* ani);
	CAnimation* Get(int id);
	void LoadResources();
	static CAnimations* GetInstance();
};

