#pragma once
#include "Enemy.h"
#include "Sophia.h"
#include "Brick.h"

class CInsect : public Enemy
{
public:
	bool isWalk;
	Animation* CurAnimation;
	CInsect();
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};