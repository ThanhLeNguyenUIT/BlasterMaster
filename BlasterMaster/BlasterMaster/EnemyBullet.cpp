#pragma once
#include "EnemyBullet.h"
#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "Brick.h"


EnemyBullet::EnemyBullet() {

}

EnemyBullet::~EnemyBullet() {

}

void EnemyBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SMALL_BBOX_WIDTH;
	bottom = y + BULLET_SMALL_BBOX_HEIGHT;
}

void EnemyBullet::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (StateObject)
	{
	case ENEMY_BULLET_SMALL_MOVING:
		if (x - player->x < 0) {
			vx = ENEMY_BULLET_MOVING_SPEED;
			vy = ENEMY_BULLET_MOVING_SPEED;
		}
		else {
			vx = -ENEMY_BULLET_MOVING_SPEED;
			vy = ENEMY_BULLET_MOVING_SPEED;
		}
		break;
	case MINE_BULLET_JUMPING_RIGHT:
		vx = MINE_BULLET_MOVING_SPEED;
		vy = -MINE_BULLET_JUMPING_SPEED;
		nx = 1;
		break;
	case MINE_BULLET_JUMPING_LEFT:
		vx = -MINE_BULLET_MOVING_SPEED;
		vy = -MINE_BULLET_JUMPING_SPEED;
		nx = -1;
		break;
	case CANON_BULLET_MOVING_LEFT:
		vy = 0;
		vx = -CANON_BULLET_MOVING_SPEED;
		nx = -1;
		break;
	case CANON_BULLET_MOVING_RIGHT:
		vy = 0;
		vx = CANON_BULLET_MOVING_SPEED;
		nx = 1;
		break;
	case CANON_BULLET_MOVING_DOWN:
		vy = CANON_BULLET_MOVING_SPEED;
		vx = 0;
		ny = -1;
		break;
	case CANON_BULLET_MOVING_UP:
		vy = -CANON_BULLET_MOVING_SPEED;
		vx = 0;
		ny = 1;
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

void EnemyBullet::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void EnemyBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*>* coEnemy) {
	GameObject::Update(dt, coObjects);

	if (StateObject == MINE_BULLET_JUMPING_RIGHT || StateObject == MINE_BULLET_JUMPING_LEFT) {
		vy += ENEMY_BULLET_GRAVITY * dt;
	}
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
				if (StateObject == MINE_BULLET_JUMPING_LEFT || StateObject == MINE_BULLET_JUMPING_RIGHT) {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}
				else
				{
					ChangeAnimation(BULLET_SMALL_HIT);
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

