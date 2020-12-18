#include "EyeBall.h"
#include "Brick.h"


void EyeBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 16;
}

void EyeBall::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);

}

void EyeBall::Render() {
	//Reset();
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void EyeBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	//int old_nx=1, old_ny=1;
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	//if (coEvents.size() == 0)
	//{


	if (health == 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//	// block 
	x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	y += min_ty * dy + ny * 0.4f;

	//if (nx != 0) vx = 0;
	//if (ny != 0) vy = 0;

	DWORD timenow = GetTickCount();
	if ((timenow - dt) % 200 == 0) {
		if ((vx == 0) && (vy == 0)) {
			int ranX = rand() % 2; // - = 0, + = 1
			int ranY = rand() % 2;
			ranX == 0 ? this->nx = -1 : this->nx = 1;
			ranY == 0 ? this->ny = -1 : this->ny = 1;
			ChangeAnimation(EYEBALL_MOVE);
			vx = this->nx * EYEBALL_MOVING_SPEED_X;
			vy = this->ny * EYEBALL_MOVING_SPEED_Y;
		}
		else if ((vx != 0) && (vy != 0) && rand() % 2 == 0) {
			vx = 0;
			vy = 0;
			//this->nx = 0;
			//this->ny = 0;
			ChangeAnimation(EYEBALL_IDLE);
		}
	}

	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<Brick*>(e->obj)) // if e->obj is Brick
		{
			Brick* brick = dynamic_cast<Brick*>(e->obj);
			if (e->ny > 0 && e->nx == 0)
			{
				if (this->vx > 0)
				{
					//ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					vx = EYEBALL_MOVING_SPEED_X;
					vy = EYEBALL_MOVING_SPEED_Y;
					this->nx = 1;
					this->ny = 1;
				}
				else if (this->vx < 0)
				{
					//ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
					vx = -EYEBALL_MOVING_SPEED_X;
					vy = EYEBALL_MOVING_SPEED_Y;
					this->nx = -1;
					this->ny = 1;
				}
			}
			else if (e->ny < 0 && e->nx == 0)
			{
				if (this->vx > 0)
				{
					vx = EYEBALL_MOVING_SPEED_X;
					vy = -EYEBALL_MOVING_SPEED_Y;
					//ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
					this->nx = 1;
					this->ny = -1;
				}
				else if (this->vx < 0)
				{
					//ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
					vx = -EYEBALL_MOVING_SPEED_X;
					vy = -EYEBALL_MOVING_SPEED_Y;
					this->nx = -1;
					this->ny = -1;
				}
			}
			else if (e->nx > 0 && e->ny == 0)
			{
				if (this->vy > 0)
				{
					//ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_BOTTOM);
					vx = EYEBALL_MOVING_SPEED_X;
					vy = EYEBALL_MOVING_SPEED_Y;
					this->nx = 1;
					this->ny = 1;
				}
				else if (this->vy < 0)
				{
					vx = EYEBALL_MOVING_SPEED_X;
					vy = -EYEBALL_MOVING_SPEED_Y;
					this->nx = 1;
					this->ny = -1;
					//ChangeAnimation(FLOATER_STATE_WALKING_RIGHT_TOP);
				}
			}
			else if (e->nx < 0 && e->ny == 0)
			{
				if (this->vy > 0)
				{
					vx = -EYEBALL_MOVING_SPEED_X;
					vy = EYEBALL_MOVING_SPEED_Y;
					this->nx = -1;
					this->ny = 1;
					//ChangeAnimation(FLOATER_STATE_WALKING_LEFT_BOTTOM);
				}
				else if (this->vy < 0)
				{
					vx = -EYEBALL_MOVING_SPEED_X;
					vy = -EYEBALL_MOVING_SPEED_Y;
					this->nx = this->ny = -1;
					//ChangeAnimation(FLOATER_STATE_WALKING_LEFT_TOP);
				}
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

