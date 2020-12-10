#pragma once
#include "Enemy.h"


class CWorm : public Enemy
{
public:
	bool isIdle;
	bool isDrop;
	bool isWalking;
	bool isInArea = false;
	Animation* CurAnimation;
	CWorm(float x = 0.0f, float y = 0.0f);
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};