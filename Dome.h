#pragma once
#include "Enemy.h"

class CDome : public Enemy
{
public:
	bool top;
	bool bottom;
	bool right;
	bool left;
	Animation* CurAnimation;
	CDome(float x = 0.0f, float y = 0.0f);
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};