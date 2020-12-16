#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprites.h"

/*
Sprite animation
*/
class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
	void SetSpriteId(int id) { this->sprite->id = id; }
	int GetSpriteId() { return sprite->id; }
};

typedef AnimationFrame* LPANIMATION_FRAME;

class Animation
{
	
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;
public:
	DWORD lastFrameTime;
	bool IsFinish = false;
	int currentFrame = 0;
	bool isLastFrame;
	Animation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	int GetCurrentFrame() { return this->currentFrame; } 	
	void SetCurrentFrame(int currentFrame) { this->currentFrame = currentFrame; }
	void Render(float x, float y, int alpha = 255, int idFrame = 0, bool renderOneFrame = false, D3DCOLOR color = NULL);
	void RenderBack(float x, float y, int alpha = 255, int idFrame = 0, bool renderOneFrame = false);
};

typedef Animation* LPANIMATION;

class Animations
{
	static Animations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id );
	void Clear();
	
	static Animations* GetInstance();
};

class AnimationSet {
	unordered_map<int, LPANIMATION> animations;
public:
	void Add(int aniId, STATENAME StateName);
	void Add(int aniId, STATEOBJECT StateObject);
	LPANIMATION Get(STATENAME NameState);
	LPANIMATION Get(STATEOBJECT type);
};


typedef AnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class AnimationSets
{
	static AnimationSets* __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	AnimationSets();
	void Add(TYPE type, LPANIMATION_SET ani);
	LPANIMATION_SET Get(TYPE type);
	void ClearAt(STATEOBJECT state);
	static AnimationSets* GetInstance();
};