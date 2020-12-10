#pragma once
#include "GameObject.h"
#include "GlobalConfig.h"
#include "Enemy.h"

#define BULLET_MOVING_SPEED 0.4f

#define BULLET_TIME_EXPLOSIVE 150
// width and height of bounding box
#define BULLET_SMALL_BBOX_WIDTH 4
#define BULLET_SMALL_BBOX_HEIGHT 4
#define BULLET_BIG_BBOX_WIDTH 22
#define BULLET_BIG_BBOX_HEIGHT 6

class Bullet;
typedef Bullet* LPBULLET;
class Bullet : public GameObject {
public:
	DWORD timeStartCol = TIME_DEFAULT;
	bool IsHitting = false;
	Animation* CurAnimation;
	TYPE typeBullet;
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	void SetType(TYPE type) { this->typeBullet = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*> coEnemy);
	virtual void Render();
};