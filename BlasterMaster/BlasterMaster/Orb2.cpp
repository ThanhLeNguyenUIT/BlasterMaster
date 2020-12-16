#include "Orb2.h"
#include "GlobalConfig.h"
#include "Brick.h"
COrb2::COrb2()
{
	type = ORB2;
	width = ORB2_BBOX_WIDTH;
	height = ORB2_BBOX_HEIGHT;
	Reset();
}

void COrb2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 0.1;
	right = x + ORB2_BBOX_WIDTH;
	bottom = y + ORB2_BBOX_HEIGHT + 0.1;
}

void COrb2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (health <= 0) {
		ChangeAnimation(ORB2_STATE_EXPLOSE);
		if (GetTickCount() - timeStartCol >= BULLET_TIME_EXPLOSIVE) {
			StateObject = ENEMY_DEAD;
			isDead = true;
		}
	}

	if (coEvents.size() == 0)
	{
		float cx = 0, cy = 0;
		if (Allow[SOPHIA])
			player->GetPosition(cx, cy);
		else if (Allow[JASON])
			playerSmall->GetPosition(cx, cy);

		double kc = sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));

		if (kc <= 110 && cy >= y)
		{
			if (x < cx)
			{
				ChangeAnimation(ORB2_STATE_TURN_RIGHT);
			}
			else if (x > cx)
			{
				ChangeAnimation(ORB2_STATE_TURN_LEFT);
			}
			else if (x == cx)
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
		// block every object first!
		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

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
				if (e->nx < 0)
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
	LPANIMATION_SET animationSet = animation_sets->Get(type);
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
	case ORB2_STATE_EXPLOSE:
		vx = 0;
		vy = 0;
		if (timeStartCol = TIME_DEFAULT) timeStartCol = GetTickCount();
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
