#pragma once
#include "Enemy.h"

class CBossArm : public Enemy
{
	int typeArm;
	float new_vx, new_vy; // xet van toc cho tay con boss
	float x_follow, y_follow;
	int alpha1 = 255;
	float old_vx, old_vy;
public:
	Animation* CurAnimation;
	//bool isStop = false;
	CBossArm(float x, float y, int type, float _vx, float _vy);
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	//void Render();
	void Render();
	void Reset();
	void setAlpha(int a) { this->alpha1 = a; }
	void SetXYFollow(float x_follow, float y_follow) {
		this->x_follow = x_follow;
		this->y_follow = y_follow;
	}
	void MoveFollow(float x_follow, float y_follow);

	bool Stop(float x_stop, float y_stop) {
		if (x == x_stop && y == y_stop) return true;
		return false;
	}
	void SetOldSpeed() {
		old_vx = vx;
		old_vy = vy;
	}
	void GetOldSpeed(float old_vx, float old_vy) {
		old_vx = this->old_vx;
		old_vy = this->old_vy;
	}
};
