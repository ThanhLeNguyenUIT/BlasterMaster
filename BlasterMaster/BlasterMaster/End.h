#pragma once
#include "GameObject.h"

class End : public GameObject
{
public:
	Animation* CurAnimation;
	End();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void ChangeAnimation(STATEOBJECT state);
};