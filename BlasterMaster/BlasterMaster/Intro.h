#pragma once
#include "GameObject.h"

#define Intro_IDLE 0

#define Intro_STATE_IDLE	100
#define TIME_INTRO

class CIntro : public GameObject
{
public:
	Animation* CurAnimation;

	CIntro();
	~CIntro();
	virtual void ChangeAnimation(STATEOBJECT state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	static CIntro* _instance;
	static CIntro* GetInstance();
};