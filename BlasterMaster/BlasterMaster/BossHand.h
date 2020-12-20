#pragma once
#include "Enemy.h"

#define BOSS_HAND_WALKING_SPEED_X 0.05f
#define BOSS_HAND_WALKING_SPEED_Y 0.05f

class CBossHand : public Enemy
{
	int typeHand;
	float x_boss, y_boss;
	int alpha1 = 255;
public:
	bool isStop = false;
	Animation* CurAnimation;
	CBossHand(float x, float y, int type, float x_boss, float y_boss);
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Reset();
	void Move();
	void setAlpha(int a) { this->alpha1 = a; }
	void SetBossPos(float  x_boss, float y_boss) {
		this->x_boss = x_boss;
		this->y_boss = y_boss;
	}
};