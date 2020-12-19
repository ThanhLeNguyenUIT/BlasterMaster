#pragma once
#include "GameObject.h"

class End3 : public GameObject
{
public:
	Animation* CurAnimation;
	End3();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void ChangeAnimation(STATEOBJECT state);
};