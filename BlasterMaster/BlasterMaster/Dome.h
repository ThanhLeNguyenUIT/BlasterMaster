#pragma once
#include "Enemy.h"
#include "Sophia.h"

class CDome : public Enemy
{
public:
	bool top;
	bool bottom;
	bool right;
	bool left;
	bool drop;
	Animation* CurAnimation;
	CDome(int state);
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();

};