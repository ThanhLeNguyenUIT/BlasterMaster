#pragma once
#include "Enemy.h"
#include "Sophia.h"

class CInsect : public Enemy
{
public:
	bool isWalk;
	Animation* CurAnimation;
	CInsect(float x = 0.0f, float y = 0.0f);
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeEnemy = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};