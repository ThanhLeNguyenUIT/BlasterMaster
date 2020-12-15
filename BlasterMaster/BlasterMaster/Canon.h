#pragma once
#include "GameObject.h"
#include "Enemy.h"



class Canon : public Enemy
{
	Animation* CurAnimation;
	TYPE typeCanon;
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeCanon = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	bool isRender = false;
	Canon(int x, int y) {
		this->x = x;
		this->y = y;
		typeCanon = CANON;
		ChangeAnimation(CANON_MOVING);
	}
	virtual void Render();
	//void Reset(float x = 67 * BIT, float y = 72 * BIT);
};

