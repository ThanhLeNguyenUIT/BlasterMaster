#pragma once
#include "Enemy.h"


class Teleporter : public Enemy
{
	Animation* CurAnimation;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	int startX;
	int startY;
	bool isRender = false;
	Teleporter(float x, float y) {
		width = 24;
		height = 32;
		this->startX = x;
		this->startY = y;
		type = TELEPORTER;
		ChangeAnimation(TELEPORTERS_IDLE);
	}
	virtual void Render();
};

