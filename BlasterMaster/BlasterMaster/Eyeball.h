#pragma once
#include "GameObject.h"
#include "Enemy.h"

#define EYEBALL_MOVING_SPEED_X 0.05f
#define EYEBALL_MOVING_SPEED_Y 0.05f

class Eyeball : public Enemy
{
	Animation* CurAnimation;
	TYPE typeEyeball;
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeEyeball = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	bool isRender = false;
	Eyeball(int x, int y) {
		this->x = x;
		this->y = y;
		typeEyeball = EYEBALL;
		int ranX = rand() % 2; // - = 0, + = 1
		int ranY = rand() % 2;
		ranX == 0 ? this->nx = -1 : this->nx = 1;
		ranY == 0 ? this->ny = -1 : this->ny = 1;
		ChangeAnimation(EYEBALL_MOVE);
		vx = EYEBALL_MOVING_SPEED_X;
		vy = EYEBALL_MOVING_SPEED_Y;
	}
	virtual void Render();
	//void Reset(float x = 67 * BIT, float y = 72 * BIT);
};

