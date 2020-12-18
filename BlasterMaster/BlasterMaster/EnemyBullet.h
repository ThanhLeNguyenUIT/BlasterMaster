#pragma once
#include "Bullet.h"

#define ENEMY_BULLET_MOVING_SPEED 0.08f
#define BULLET_TIME_EXPLOSIVE 150
#define MINE_BULLET_MOVING_SPEED	0.05f
#define MINE_BULLET_JUMPING_SPEED	0.08f
#define ENEMY_BULLET_GRAVITY	0.001f
#define CANON_BULLET_MOVING_SPEED	0.01f
// width and height of bounding box
#define BULLET_SMALL_BBOX_WIDTH 4
#define BULLET_SMALL_BBOX_HEIGHT 4
#define MINE_BULLET_BBOX_WIDTH 4
#define MINE_BULLET_BBOX_HEIGHT 4

class EnemyBullet : public Bullet {
public:
	EnemyBullet();
	~EnemyBullet();
	bool IsHitting = false;
	Animation* CurAnimation;
	void ChangeAnimation(STATEOBJECT StateObject);
	void SetType(TYPE type) { this->type = type; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*>* coEnemy = NULL);
	void Render();
};