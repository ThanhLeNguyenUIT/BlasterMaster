#pragma once
#include "Enemy.h"
#include "Sophia.h"

class CJumper : public Enemy
{
public:
	bool is;
	bool isJump;
	Animation* CurAnimation;
	CJumper(float x = 0.0f, float y = 0.0f);
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeEnemy = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};