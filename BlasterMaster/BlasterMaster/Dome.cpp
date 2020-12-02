#include "Dome.h"
#include "Brick.h"
#include "Portal.h"
#include "Enemy.h"
#include "Power.h"

CDome::CDome(float x, float y)
{
	this->x = x;
	this->y = y;
	typeEnemy = DOME;
	Reset();
}

void CDome::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOME_BBOX_WIDTH;
	bottom = y + DOME_BBOX_HEIGHT;
}

void CDome::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (health <= 0) {
		StateObject = ENEMY_DEAD;
	}
	// turn off collision when die 
	if (StateObject != ENEMY_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{

		if (bottom == true)
		{
			vy += DOME_GRAVITY_X;
		}

		if (left == true)
		{
			vx -= DOME_GRAVITY_Y;
		}

		if (top == true && vy == 0)
		{
			vy -= DOME_GRAVITY_Y;
		}

		else if (top == true && vy < 0)
		{
			ChangeAnimation(DOME_STATE_WALKING_LEFT);
			x += dx;
			y += dy;
			bottom = false;
			right = false;
			left = true;
			top = false;
		}

		if (right == true && vx == 0)
		{
			vx += DOME_GRAVITY_X;
		}
		else if (right == true && vx != 0)
		{
			ChangeAnimation(DOME_STATE_WALKING_TOP);
			x += dx;
			y += dy;
			bottom = false;
			right = false;
			left = false;
			top = true;

		}
	}
	else
	{
		bottom = false;
		top = false;
		right = false;
		left = false;
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
				// flip down
				if (e->ny > 0)
				{
					bottom = false;
					right = false;
					left = false;
					top = true;
					if (this->GetState() != DOME_STATE_WALKING_TOP)
					{
						ChangeAnimation(DOME_STATE_WALKING_TOP);
					}
				}
				//flip up
				else if (e->ny < 0)
				{
					bottom = true;
					top = false;
					right = false;
					left = false;
					if (this->GetState() != DOME_STATE_WALKING_BOTTOM)
					{
						ChangeAnimation(DOME_STATE_WALKING_BOTTOM);
					}
				}
				else if (e->nx < 0)
				{
					bottom = false;
					top = false;
					right = true;
					left = false;
					if (this->GetState() != DOME_STATE_WALKING_RIGHT)
					{
						ChangeAnimation(DOME_STATE_WALKING_RIGHT);
					}
				}
				else if (e->nx > 0)
				{
					left = true;
					bottom = false;
					top = false;
					right = false;
					if (this->GetState() != DOME_STATE_WALKING_LEFT)
					{
						ChangeAnimation(DOME_STATE_WALKING_LEFT);
					}
				}

			}

			if (dynamic_cast<Portal*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}

			if (dynamic_cast<Enemy*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0)	y += dy;
			}
			if (dynamic_cast<Power*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0)	y += dy;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CDome::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	//RenderBoundingBox();
}

void CDome::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case DOME_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case DOME_STATE_WALKING_BOTTOM:
		vx = -DOME_WALKING_SPEED;
		vy = 0;
		break;
	case DOME_STATE_WALKING_TOP:
		vx = DOME_WALKING_SPEED;
		vy = 0;
		break;
	case DOME_STATE_WALKING_LEFT:
		vy = -DOME_WALKING_SPEED;
		vx = 0;
		break;
	case DOME_STATE_WALKING_RIGHT:
		vy = DOME_WALKING_SPEED;
		vx = 0;
		break;
	}
}

void CDome::Reset() {
	top = false;
	right = false;
	bottom = true;
	left = false;
	ChangeAnimation(DOME_STATE_IDLE);
}