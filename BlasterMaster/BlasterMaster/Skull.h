#pragma once
#include "GameObject.h"
#include "Sophia.h"


class CSkull : public GameObject
{
public:
	int ny;
	TYPE typeEnemy;
	Animation* CurAnimation;
	CSkull();
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeEnemy = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};