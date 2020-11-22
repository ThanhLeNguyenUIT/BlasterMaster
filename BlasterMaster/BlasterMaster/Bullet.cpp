#pragma once
#include "Bullet.h"
#include "Jason.h"
#include "Brick.h"
#include "Gate.h"
#include "Portal.h"
#include "Orb1.h"
#include "Worm.h"

void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SMALL_BBOX_WIDTH;
	bottom = y + BULLET_SMALL_BBOX_HEIGHT;
}

void Bullet::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeBullet);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case BULLET_BIG_MOVING_RIGHT:
		vx = BULLET_MOVING_SPEED;
		break;
	case BULLET_BIG_MOVING_LEFT:
		vx = -BULLET_MOVING_SPEED;
		break;
	case BULLET_BIG_MOVING_UP:
		vy = -BULLET_MOVING_SPEED;
		break;
	case JASON_BULLET_SMALL_MOVING:
		if (playerSmall->nx > 0)
			vx = BULLET_MOVING_SPEED;
		else vx = -BULLET_MOVING_SPEED;
		break;
	case BULLET_SMALL_HIT:
		vx = 0;
		vy = 0;
		IsHitting = true;
		if (timeStartCol = TIME_DEFAULT) timeStartCol = GetTickCount();
		break;
	default:
		break;
	}
}

void Bullet::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt, coObjects);
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
				if (nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
				if (ny != 0) ChangeAnimation(BULLET_SMALL_HIT);
			}

			if (dynamic_cast<Enemy*>(e->obj)) {
				ChangeAnimation(BULLET_SMALL_HIT);
				Enemy* p = dynamic_cast<Enemy*>(e->obj);
				if (e->nx != 0) p->health = p->health - 1;
				if (e->ny != 0) p->health = p->health - 1;
			}

			if (dynamic_cast<Portal*>(e->obj)) {
				if (nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
				if (ny != 0) ChangeAnimation(BULLET_SMALL_HIT);
			}
			if (dynamic_cast<Gate*>(e->obj)) {
				if (nx != 0) ChangeAnimation(BULLET_SMALL_HIT);
				if (ny != 0) ChangeAnimation(BULLET_SMALL_HIT);
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

