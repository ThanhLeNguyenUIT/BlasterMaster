#include "Orb2.h"
#include "GlobalConfig.h"
#include "Brick.h"
COrb2::COrb2()
{
	typeEnemy = ORB2;
	Reset();
}

void COrb2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y+0.1;
	right = x + ORB2_BBOX_WIDTH;

	/*if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else*/
		bottom = y + ORB2_BBOX_HEIGHT+0.1;
}

void COrb2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		float cxm, cym;
		player->GetPosition(cxm, cym);

		float cex, cey;
		this->GetPosition(cex, cey);

		double kc = sqrt((cex - cxm) * (cex - cxm) + (cey - cym) * (cey - cym));

		if (kc <= 110 && cym>=cey)
		{
			if (cex < cxm)
			{
				ChangeAnimation(ORB2_STATE_TURN_RIGHT);
			}
			else if (cex > cxm)
			{
				ChangeAnimation(ORB2_STATE_TURN_LEFT);
			}
			else if (cex == cxm)
			{
				ChangeAnimation(ORB2_STATE_TURN_BOTTOM);
			}
		}

		x += vx * dt;
		y += vy * dt;
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
		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/


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
					ChangeAnimation(ORB2_STATE_WALKING_RIGHT);
				}
				else if (e->nx < 0)
				{
					ChangeAnimation(ORB2_STATE_WALKING_LEFT);
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void COrb2::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void COrb2::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case ORB2_STATE_WALKING_LEFT:
		nx = -1;
		vx = -ORB2_WALKING_SPEED;
		vy = 0;
		break;
	case ORB2_STATE_WALKING_RIGHT:
		nx = 1;
		vx = ORB2_WALKING_SPEED;
		vy = 0;
		break;
	case ORB2_STATE_TURN_LEFT:
		nx = -1;
		vy = ORB2_WALKING_TURN_Y;
		vx = -ORB2_WALKING_TURN_X;
		break;
	case ORB2_STATE_TURN_RIGHT:
		nx = 1;
		vy = ORB2_WALKING_TURN_Y;
		vx = ORB2_WALKING_TURN_X;
		break;
	case ORB2_STATE_TURN_BOTTOM:
		nx = 1;
		vx = 0;
		vy = ORB2_WALKING_TURN_Y;
		break;
	default:
		break;
	}
}

void COrb2::Reset() {
	nx = -1;
	ny = 1;
	ChangeAnimation(ORB2_STATE_WALKING_LEFT);
}
