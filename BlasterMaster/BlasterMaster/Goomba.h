#pragma once
#include "GameObject.h"



class Goomba : public GameObject
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
	Goomba() {
		typeCanon = GOOMBA;
		ChangeAnimation(GOOMBA_MOVE);
	}
	virtual void Render();
	void Reset(float x = 67 * BIT, float y = 72 * BIT);
};
