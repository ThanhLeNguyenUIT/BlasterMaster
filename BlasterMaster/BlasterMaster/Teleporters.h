#pragma once
#include "GameObject.h"
#include "Enemy.h"


class Teleporter : public Enemy
{
	Animation* CurAnimation;
	TYPE typeTeleporter;
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeTeleporter = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	bool isRender = false;
	Teleporter() {
		typeTeleporter = TELEPORTER;
		ChangeAnimation(TELEPORTERS_IDLE);
	}
	virtual void Render();
	//void Reset(float x = 67 * BIT, float y = 72 * BIT);
};

