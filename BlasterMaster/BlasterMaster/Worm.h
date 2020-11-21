#pragma once
#include "GameObject.h"
#include "GlobalConfig.h"
#include "Sophia.h"

class CWorm : public GameObject
{
	

public:
	bool isIdle;
	bool isDrop;
	bool isWalking;
	TYPE typeEnemy;
	Animation* CurAnimation;
	CWorm(float x = 0.0f, float y = 0.0f);
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeEnemy = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
};