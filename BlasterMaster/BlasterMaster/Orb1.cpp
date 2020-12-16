#include "Orb1.h"
#include "Brick.h"
#include "Sophia.h"
#include "Bullet.h"
#include "Power.h"
#include "Stair.h"

COrb1::COrb1()
{
	type = ORB1;
	width = ORB1_BBOX_WIDTH;
	height = ORB1_BBOX_HEIGHT;
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
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (StateObject != ENEMY_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);

	if (health <= 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}

	if (coEvents.size() == 0)
	{
		x += vx * dt;
		y += vy * dt;
		DWORD timenow = GetTickCount();

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
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.14f;
		y += min_ty * dy + ny * 0.14f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Brick
			{
				Brick* brick = dynamic_cast<Brick*>(e->obj);
				if (e->nx > 0)
				{
					ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
				}
				if (e->nx < 0)
				{
					ChangeAnimation(ORB1_STATE_WALKING_LEFT);
				}
			}
			if (dynamic_cast<Stair*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
	LPANIMATION_SET animationSet = animation_sets->Get(type);
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
	case ENEMY_DEAD:
		vx = 0;
		vy = 0;
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
