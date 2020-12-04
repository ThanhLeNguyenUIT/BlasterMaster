#include "Worm.h"
#include "Brick.h"

CWorm::CWorm(float x, float y)
{
	this->x = x;
	this->y = y;
	typeEnemy = WORM;
	Reset();

}

void CWorm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + WORM_BBOX_WIDTH;

	/*if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else*/
		bottom = y + WORM_BBOX_HEIGHT;
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	
	// turn off collision when die 
	//if (state != GOOMBA_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);

	float cxm, cym;
	player->GetPosition(cxm, cym);

	float cex5, cey5;
	this->GetPosition(cex5, cey5);

	double kc4 = sqrt((cex5 - cxm) * (cex5 - cxm) + (cey5 - cym) * (cey5 - cym));


	if (coEvents.size() == 0)
	{
		if (!isIdle && isWalking)
		{
			vy += WORM_GRAVITY;
			left = false;
		}
		if (isWalking)
		{
			if (cex5 <= cxm && this->StateObject != WORM_STATE_WALKING_RIGHT)
			{
				ChangeAnimation(WORM_STATE_WALKING_RIGHT);
			}
			else if (cex5 > cxm&& this->StateObject != WORM_STATE_WALKING_LEFT)
			{
				ChangeAnimation(WORM_STATE_WALKING_LEFT);
			}
			isDrop = false;
			isIdle = false;
			x += dx;
			y += dy;
		}

		if (kc4 <= 210 && isDrop)
		{
			if (cex5 > cxm&& this->StateObject != WORM_STATE_DROP_LEFT)
			{
				ChangeAnimation(WORM_STATE_DROP_LEFT);
			}
			else if (cex5 <= cxm && this->StateObject != WORM_STATE_DROP_RIGHT)
			{
				ChangeAnimation(WORM_STATE_DROP_RIGHT);
			}
			x += dx;
			y += dy;
		}
		if (left == true && vx == 0)
		{
			vx -= WORM_GRAVITY;
		}
		else if (left == true && vx != 0) {
			ChangeAnimation(WORM_STATE_WALKING_LEFT);
			left = false;
			x += dx;
			y += dy;
			isWalking = true;
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

				if (e->ny < 0)
				{
					if (cex5 < cxm && this->StateObject != WORM_STATE_WALKING_RIGHT)
					{
						ChangeAnimation(WORM_STATE_WALKING_RIGHT);
					}
					else if (cex5 >= cxm && this->StateObject != WORM_STATE_WALKING_LEFT)
					{
						ChangeAnimation(WORM_STATE_WALKING_LEFT);
					}
					isDrop = false;
					isWalking = true;
					isIdle = false;
					left = false;
				}
				if (e->nx > 0 && isWalking == true)
				{
					vy = -0.04;
					left = true;
					isWalking = false;
				}

			}
		}
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void CWorm::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	//RenderBoundingBox();
}

void CWorm::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case WORM_STATE_WALKING_LEFT:
		vx = -WORM_WALKING_SPEED;
		vy = 0;
		break;
	case WORM_STATE_WALKING_RIGHT:
		vx = WORM_WALKING_SPEED;
		vy = 0;
		break;
	case WORM_STATE_DROP_LEFT:
		vx = -WORM_WALKING_DROP_X;
		vy = WORM_WALKING_DROP_Y;
		break;
		
	case WORM_STATE_DROP_RIGHT:
		vx = WORM_WALKING_DROP_X;
		vy = WORM_WALKING_DROP_Y;
		break;
	case WORM_STATE_IDLE_LEFT:
		vx = 0;
		vy = 0;
		break;
	case WORM_STATE_IDLE_RIGHT:
		vx = 0;
		vy = 0;
		break;
	}
}

void CWorm::Reset() {
	nx = -1;
	ChangeAnimation(WORM_STATE_IDLE_LEFT);
	isIdle = true;
	isDrop = true;
	isWalking = false;
	left = false;
}

