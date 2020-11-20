#include "Orb1.h"
#include "Brick.h"
#include "Sophia.h"
#include "Bullet.h"
#include "GlobalConfig.h"
COrb1::COrb1()
{
	typeEnemy = ORB1;
	Reset();
}

void COrb1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 2;
	top = y;
	right = x + ORB1_BBOX_WIDTH;
	bottom = y + ORB1_BBOX_HEIGHT;
}

void COrb1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	DWORD timenow = GetTickCount();

	if (health == 0) {
		StateObject = ENEMY_DEAD;
	}

	if ((timenow - dt) % 800 == 0) {
		if (ny == -1)
		{
			ChangeAnimation(ORB1_STATE_TURN_TOP);
		}
		else if (ny == 1)
		{
			ChangeAnimation(ORB1_STATE_TURN_BOTTOM);
		}
	}
	else if ((timenow - dt) % 1000 == 0) {
		if (nx == 1)
		{
			ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
		}
		else if (nx == -1)
		{
			ChangeAnimation(ORB1_STATE_WALKING_LEFT);
		}
		vy = 0;
	}

	if (vx < 0 && x < 64 * 16) {
		x = 64 * 16; vx = -vx;
		ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
	}

	if (vx > 0 && x > 80 * 16) {
		x = 80 * 16; vx = -vx;
		ChangeAnimation(ORB1_STATE_WALKING_LEFT);
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<Brick*>(e->obj)) {
				if (e->nx > 0) {
					ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
				}
				else {
					ChangeAnimation(ORB1_STATE_WALKING_LEFT);
				}
				if (e->ny != 0) ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
			}
			
		}
	}
}

void COrb1::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void COrb1::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case ORB1_STATE_WALKING_RIGHT:
		vx = ORB1_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case ORB1_STATE_WALKING_LEFT:
		vx = -ORB1_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case ORB1_STATE_TURN_TOP:
		vy = -ORB1_WALKING_SPEED_TURN;
		vx = 0;
		ny = 1;
		break;
	case ORB1_STATE_TURN_BOTTOM:
		vy = ORB1_WALKING_SPEED_TURN;
		vx = 0;
		ny = -1;
		break;
	default:
		break;
	}
}

void COrb1::Reset() {
	nx = 1;
	ny = 1;
	ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
}
