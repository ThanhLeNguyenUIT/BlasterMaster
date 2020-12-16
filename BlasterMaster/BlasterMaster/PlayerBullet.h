#pragma once
#include "Bullet.h"

#define BULLET_MOVING_SPEED 0.4f

#define BULLET_TIME_EXPLOSIVE 150
// width and height of bounding box
#define BULLET_SMALL_BBOX_WIDTH 4
#define BULLET_SMALL_BBOX_HEIGHT 4
#define BULLET_BIG_BBOX_WIDTH 22
#define BULLET_BIG_BBOX_HEIGHT 6



class PlayerBullet : public Bullet {
public:
	PlayerBullet();
	~PlayerBullet();
	bool IsHitting = false;
	Animation* CurAnimation;
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coStaticObjects, vector<Enemy*>* coEnemy);
	void Render();
};