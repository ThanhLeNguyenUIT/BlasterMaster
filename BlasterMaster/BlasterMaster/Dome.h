#pragma once
#include "GameObject.h"





class CDome : public GameObject
{


public:
	bool top;
	bool bottom;
	bool right;
	bool left;
	TYPE typeEnemy;
	Animation* CurAnimation;
	CDome();
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeEnemy = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};