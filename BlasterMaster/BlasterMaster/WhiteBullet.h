#pragma once
#include "Bullet.h"

#define WHITE_BULLET_MOVING_SPEED 0.02f
#define BULLET_TIME_EXPLOSIVE 150
// width and height of bounding box
#define WHITE_BULLET_BBOX_WIDTH 10
#define WHITE_BULLET_BBOX_HEIGHT 10

class WhiteBullet : public Bullet {
public:
	bool IsHitting = false;
	Animation* CurAnimation;
	WhiteBullet();
	~WhiteBullet();
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*>* coEnemy = NULL);
	void Render();
};