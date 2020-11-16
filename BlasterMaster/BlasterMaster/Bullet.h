#pragma once
#include "GameObject.h"
#include "GlobalConfig.h"

#define BULLET_MOVING_SPEED 0.2f


// width and height of bounding box
#define BULLET_SMALL_BBOX_WIDTH 8
#define BULLET_SMALL_BBOX_HEIGHT 6
#define BULLET_BIG_BBOX_WIDTH 22
#define BULLET_BIG_BBOX_HEIGHT 6

class Bullet;
typedef Bullet* LPBULLET;
class Bullet : public GameObject {
public:
	DWORD timeStartCol = TIME_DEFAULT;
	bool isDead = false;
	bool IsHitting = false;
	Animation* CurAnimation;
	TYPE typeBullet;
	STATEOBJECT StateObject;
	void ChangeAnimation(STATEOBJECT StateObject);
	STATEOBJECT GetStateObject() { return this->StateObject; }
	//void SetType(TYPE type) { this->typeBullet = type; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};