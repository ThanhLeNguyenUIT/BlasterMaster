#pragma once
#include "Enemy.h"

class COrb1 : public Enemy
{
public:
	Animation* CurAnimation;
	COrb1();
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};