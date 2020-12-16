#pragma once
#include "WhiteBullet.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "Brick.h"


WhiteBullet::WhiteBullet() {

	type = WHITE_BULLET;
}
WhiteBullet::~WhiteBullet() {

}

void WhiteBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + WHITE_BULLET_BBOX_WIDTH;
	bottom = y + WHITE_BULLET_BBOX_HEIGHT;
}

void WhiteBullet::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (StateObject)
	{
	case WHITE_BULLET_MOVING_RIGHT:
		vx = WHITE_BULLET_MOVING_SPEED;
		nx = 1;
		break;
	case WHITE_BULLET_MOVING_LEFT:
		vx = -WHITE_BULLET_MOVING_SPEED;
		nx = -1;
		break;
	case BULLET_SMALL_HIT:
		vx = 0;
		vy = 0;
		if (timeStartCol == TIME_DEFAULT) timeStartCol = GetTickCount();
		break;
	default:
		break;
	}
}

void WhiteBullet::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void WhiteBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*>* coEnemy) {
	GameObject::Update(dt, coObjects);

	vy += SOPHIA_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) {
				/*if (e->nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
				if (e->ny == -1) vy = 0;*/
				ChangeAnimation(BULLET_SMALL_HIT);
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

