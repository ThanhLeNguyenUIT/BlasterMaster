#pragma once
#include "GameObject.h"

#define BULLET_MOVING_SPEED 0.2f

#define BULLET_STATE_MOVING_RIGHT 100
#define BULLET_STATE_MOVING_LEFT 200
#define BULLET_STATE_HIT    300

#define BULLET_ANI_MOVING 800
#define BULLET_ANI_HIT    1

#define BULLET_BBOX_WIDTH 26
#define BULLET_BBOX_HEIGHT 8

class CBullet : public CGameObject {
	
public:
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};