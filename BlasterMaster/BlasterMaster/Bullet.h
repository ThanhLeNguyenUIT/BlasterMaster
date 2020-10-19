#pragma once
#include "GameObject.h"

#define BULLET_MOVING_SPEED 0.2f

#define BULLET_STATE_MOVING_RIGHT		100
#define BULLET_STATE_MOVING_LEFT		200
#define BULLET_STATE_MOVING_UP			300
#define BULLET_STATE_HIT				400

// animtion set
#define SOPHIA_BULLET_ANIMATION_SET		4
#define SOPHIA_BULLET_ELECTRIC_SET		5
#define JASON_BULLET_SMALL_SET			6
// animation
#define SOPHIA_BULLET_SMALL_ANI_RIGHT	0
#define SOPHIA_BULLET_SMALL_ANI_LEFT	1
#define SOPHIA_BULLET_SMALL_ANI_UP		2
#define SOPHIA_BULLET_BIG_ANI_RIGHT		3
#define SOPHIA_BULLET_BIG_ANI_LEFT		4
#define SOPHIA_BULLET_BIG_ANI_UP		5
#define SOPHIA_BULLET_ANI_HIT			6
#define SOPHIA_BULLET_ELECTRIC			0
#define JASON_BULLET_SMALL				0
// width and height of bounding box
#define BULLET_SMALL_BBOX_WIDTH 8
#define BULLET_SMALL_BBOX_HEIGHT 6
#define BULLET_BIG_BBOX_WIDTH 22
#define BULLET_BIG_BBOX_HEIGHT 6

class Bullet;
typedef Bullet* LPBULLET;
class Bullet : public GameObject {
	
public:
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};