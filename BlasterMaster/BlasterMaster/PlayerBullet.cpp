#pragma once
#include "PlayerBullet.h"
#include "Jason.h"
#include "BigJason.h"
#include "Brick.h"
#include "Gate.h"
#include "Portal.h"
#include "Orb1.h"
#include "Worm.h"
#include "Power.h"
#include "Stair.h"
#include "Boss.h"
#include "Sound.h"

PlayerBullet::PlayerBullet() {
	sound->Play(GSOUND::S_BULLET_SOPHIA, false);
}

PlayerBullet::~PlayerBullet() {

}

void PlayerBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_SMALL_BBOX_WIDTH;
	bottom = y + BULLET_SMALL_BBOX_HEIGHT;
}

void PlayerBullet::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
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
		sound->Stop(GSOUND::S_BULLET_EXPLODE);
		sound->Play(GSOUND::S_BULLET_EXPLODE, false);
		vx = 0;
		vy = 0;
		IsHitting = true;
		if (timeStartCol == TIME_DEFAULT) timeStartCol = GetTickCount();
		break;
	case BIG_JASON_BULLET_MOVING_RIGHT:
		vx = BULLET_MOVING_SPEED;
		vy = 0;
		break;
	case BIG_JASON_BULLET_MOVING_LEFT:
		vx = -BULLET_MOVING_SPEED;
		vy = 0;
		break;
	case BIG_JASON_BULLET_MOVING_UP:
		vy = -BULLET_MOVING_SPEED;
		vx = 0;
		break;
	case BIG_JASON_BULLET_MOVING_DOWN:
		vy = BULLET_MOVING_SPEED;
		vx = 0;
		break;
	case BIG_JASON_BULLET_HIT:
		sound->Stop(GSOUND::S_BULLET_EXPLODE);
		sound->Play(GSOUND::S_BULLET_EXPLODE, false);
		vx = 0;
		vy = 0;
		IsHitting = true;
		if (timeStartCol == TIME_DEFAULT) timeStartCol = GetTickCount();
		break;
	case BIG_JASON_GRENADE:
		if (playerBig->nx > 0 && playerBig->ny == 0)
			vx = BULLET_MOVING_SPEED;
		else if (playerBig->nx < 0 && playerBig->ny == 0)
			vx = -BULLET_MOVING_SPEED;
		else if (playerBig->nx == 0 && playerBig->ny > 0)
			vy = -BULLET_MOVING_SPEED;
		else if (playerBig->nx == 0 && playerBig->ny < 0)
			vy = BULLET_MOVING_SPEED;
		break;
	case BIG_JASON_GRENADE_EXPLOSE:
		vx = 0;
		vy = 0;
		IsHitting = true;
		if (timeStartCol = TIME_DEFAULT) timeStartCol = GetTickCount();
		break;
	default:
		break;
	}
}

void PlayerBullet::Render() {
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void PlayerBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* staticObjects, vector<Enemy*>* coEnemy) {
	GameObject::Update(dt, staticObjects);
	vector<LPCOLLISIONEVENT> coStaticObjects;
	vector<LPCOLLISIONEVENT> coStaticObjectsResult;
	coStaticObjects.clear();
	if (StateObject != BULLET_SMALL_HIT)
		CalcPotentialCollisions(staticObjects, coStaticObjects);

	if (coStaticObjects.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coStaticObjects, coStaticObjectsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;




		// Collision logic with Goombas
		for (UINT i = 0; i < coStaticObjectsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coStaticObjectsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) {
				if (Allow[JASON] || Allow[SOPHIA])
					ChangeAnimation(BULLET_SMALL_HIT);
				else if (Allow[BIG_JASON])
					ChangeAnimation(BIG_JASON_BULLET_HIT);
			}

			if (dynamic_cast<Power*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}

			if (dynamic_cast<Portal*>(e->obj)) {
				if (Allow[JASON] || Allow[SOPHIA])
					ChangeAnimation(BULLET_SMALL_HIT);
				else if (Allow[BIG_JASON])
					ChangeAnimation(BIG_JASON_BULLET_HIT);
			}
			if (dynamic_cast<Gate*>(e->obj)) {
				if (Allow[JASON] || Allow[SOPHIA])
					ChangeAnimation(BULLET_SMALL_HIT);
				else if (Allow[BIG_JASON])
					ChangeAnimation(BIG_JASON_BULLET_HIT);
			}
			if (dynamic_cast<Stair*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
		}
	}

	for (UINT i = 0; i < coStaticObjects.size(); i++) delete coStaticObjects[i];

	for (int i = 0; i < coEnemy->size(); i++) {
		if (CollisionWithObject(coEnemy->at(i))) {
			if (StateObject != BULLET_SMALL_HIT)
				coEnemy->at(i)->health -= 1;
			if (Allow[JASON] || Allow[SOPHIA])
				ChangeAnimation(BULLET_SMALL_HIT);
			else if (Allow[BIG_JASON])
				ChangeAnimation(BIG_JASON_BULLET_HIT);
		}
	}

	if(CollisionWithObject(boss) && boss->isDead == false){
		ChangeAnimation(BIG_JASON_BULLET_HIT);
		boss->IsDamaged = true;
		if (boss->timeDamaged == TIME_DEFAULT) {
			boss->timeDamaged = GetTickCount();
		}
		if (GetTickCount() - boss->timeDamaged >= 200) {
			boss->healthBoss = boss->healthBoss - 1;
			boss->timeDamaged = TIME_DEFAULT;
		}
	}
}

