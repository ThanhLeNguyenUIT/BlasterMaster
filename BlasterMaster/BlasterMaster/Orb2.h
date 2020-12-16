#pragma once
#include "Enemy.h"
#include "Sophia.h"
#include "Jason.h"


class COrb2 : public Enemy
{
public:
	bool isHit = false;
	Animation* CurAnimation;
	COrb2();
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};