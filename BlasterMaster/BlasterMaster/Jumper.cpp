#include "Jumper.h"
#include "Brick.h"

CJumper::CJumper()
{
	type = JUMPER;
	width = JUMPER_BBOX_WIDTH;
	height = JUMPER_BBOX_HEIGHT;
	Reset();
}

void CJumper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + JUMPER_BBOX_WIDTH;
	bottom = y + JUMPER_BBOX_HEIGHT;
}

void CJumper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (health == 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}
	// turn off collision when die 
	if (StateObject != ENEMY_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{

		/*if (x < 66 * 16)
		{
			x = 66 * 16;
			nx = 1;
			ChangeAnimation(JUMPER_STATE_WALKING_RIGHT);
		}*/
		x += vx * dt;
		y += vy * dt;
		vy += JUMPER_GRAVITY;

		float cxm, cym;
		player->GetPosition(cxm, cym);

		float cex, cey;
		this->GetPosition(cex, cey);

		/*double kc = sqrt((cex - cxm) * (cex - cxm) + (cey - cym) * (cey - cym));*/
		double kcx = abs(player->x - this->x);
		double kcy = abs(player->y - this->y);

		if (kcx <= 130 && kcy <= 30)
		{
			if (cex < cxm && nx > 0 && is == true /*&& cey >= 1158*/)
			{
				is = false;
				isJump = true;
				ChangeAnimation(JUMPER_STATE_JUMP_RIGHT);
			}
			else if (cex > cxm && nx < 0 && is == true /*&& cey >= 1158*/)
			{
				is = false;
				isJump = true;
				ChangeAnimation(JUMPER_STATE_JUMP_LEFT);
			}
			else if (cex > cxm && nx > 0 && this->StateObject != JUMPER_STATE_WALKING_RIGHT)
			{
				ChangeAnimation(JUMPER_STATE_WALKING_RIGHT);
			}
			else if (cex < cxm && nx < 0 && this->StateObject != JUMPER_STATE_WALKING_LEFT)
			{
				ChangeAnimation(JUMPER_STATE_WALKING_LEFT);
			}
		}
	/*	if (isJump == true)
		{
			if (nx > 0 && is == true)
			{
				is = false;
				ChangeAnimation(JUMPER_STATE_JUMP_RIGHT);
			}
			else if (nx < 0 && is == true)
			{
				is = false;
				ChangeAnimation(JUMPER_STATE_JUMP_LEFT);
			}
		}*/
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
				if (e->ny < 0)
				{
					is = true;
					isJump = false;
				}
				if (e->nx > 0)
				{
					ChangeAnimation(JUMPER_STATE_WALKING_RIGHT);
				}
				if (e->nx < 0)
				{
					ChangeAnimation(JUMPER_STATE_WALKING_LEFT);
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CJumper::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void CJumper::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case JUMPER_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case JUMPER_STATE_WALKING_RIGHT:
		nx = 1;
		vx = JUMPER_WALKING_SPEED;
		vy = 0;
		break;
	case JUMPER_STATE_WALKING_LEFT:
		nx = -1;
		vx = -JUMPER_WALKING_SPEED;

		vy = 0;
		break;
	case JUMPER_STATE_JUMP_RIGHT:
		nx = 1;
		vx = JUMPER_JUMP_X;
		vy = -JUMPER_JUMP_Y;
		break;
	case JUMPER_STATE_JUMP_LEFT:
		nx = -1;
		vx = -JUMPER_JUMP_X;
		vy = -JUMPER_JUMP_Y;
		break;
	}
}

void CJumper::Reset() {
	is = false;
	isJump = false;
	nx = 1;
	ny = 0;
	ChangeAnimation(JUMPER_STATE_IDLE);
}