#include "Insect.h"
CInsect::CInsect()
{
	type = INSECT;
	width = INSECT_BBOX_WIDTH;
	height = INSECT_BBOX_HEIGHT;
	Reset();
}

void CInsect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + INSECT_BBOX_WIDTH;
	bottom = y + INSECT_BBOX_HEIGHT;
}

void CInsect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (health == 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}

	// turn off collision when die 
	if (StateObject != ENEMY_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);


	DWORD timenow = GetTickCount();

	if ((timenow - dt) % 400 == 0)
	{
		if (nx > 0 && this->StateObject != INSECT_STATE_JUMP_RIGHT)
		{
			ChangeAnimation(INSECT_STATE_JUMP_RIGHT);
		}
		else if (nx < 0 && this->StateObject != INSECT_STATE_JUMP_LEFT)
		{
			ChangeAnimation(INSECT_STATE_JUMP_LEFT);
		}

	}
	else if ((timenow - dt) % 500 == 0 && nx > 0)
	{
		ChangeAnimation(INSECT_STATE_WALKING_RIGHT);
	}
	else if ((timenow - dt) % 500 == 0 && nx < 0)
	{
		ChangeAnimation(INSECT_STATE_WALKING_LEFT);
	}

	if ((timenow - dt) % 1200 == 0)
	{
		nx = -nx;
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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
				if (e->ny < 0)
				{
					if (vx > 0)
					{
						ChangeAnimation(INSECT_STATE_JUMP_RIGHT);
					}
					else if (vx < 0)
					{
						ChangeAnimation(INSECT_STATE_JUMP_LEFT);
					}

				}
				if (e->ny > 0)
				{
					if (vx > 0)
					{
						ChangeAnimation(INSECT_STATE_WALKING_RIGHT);
					}
					else if (vx < 0)
					{
						ChangeAnimation(INSECT_STATE_WALKING_LEFT);
					}
				}
				if (e->nx > 0)
				{
					ChangeAnimation(INSECT_STATE_WALKING_RIGHT);
				}
				if (e->nx < 0)
				{
					ChangeAnimation(INSECT_STATE_WALKING_LEFT);
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CInsect::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void CInsect::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case INSECT_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case INSECT_STATE_JUMP_RIGHT:
		nx = 1;
		vy = -INSECT_WALKING_JUMP_Y;
		break;
	case INSECT_STATE_JUMP_LEFT:
		nx = -1;
		vy = -INSECT_WALKING_JUMP_Y;
		break;
	case INSECT_STATE_WALKING_RIGHT:
		nx = 1;
		vy = INSECT_WALKING_SPEED_Y;
		vx = INSECT_WALKING_SPEED_X;
		break;
	case INSECT_STATE_WALKING_LEFT:
		nx = -1;
		vy = INSECT_WALKING_SPEED_Y;
		vx = -INSECT_WALKING_SPEED_X;
		break;
	}
}

void CInsect::Reset() {
	isWalk = false;
	nx = -1;
	ChangeAnimation(INSECT_STATE_IDLE);
}

