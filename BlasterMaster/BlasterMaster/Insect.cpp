#include "Insect.h"
CInsect::CInsect()
{
	typeEnemy = INSECT;
	Reset();
}

void CInsect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;*/
}

void CInsect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	double kc = sqrt((this->x - player->x) * (this->x - player->x) + (this->y - player->y) * (this->y - player->y));

	if (kc <= 120)
	{
		isWalk = true;
	}
	if (kc >= 200 && isWalk == true)
	{
		isWalk = false;
	}
	if (isWalk == true)
	{
		DWORD timenow = GetTickCount();

		if ((timenow - dt) % 1200 == 0)
		{
			if (nx > 0)
			{
				ChangeAnimation(INSECT_STATE_JUMP_LEFT);
			}
			else if (nx < 0)
			{
				ChangeAnimation(INSECT_STATE_JUMP_RIGHT);
			}
		}else if ((timenow - dt) % 400 == 0)
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
		else if (nx > 0)
		{
			ChangeAnimation(INSECT_STATE_WALKING_RIGHT);
		}
		else if (nx < 0)
		{
			ChangeAnimation(INSECT_STATE_WALKING_LEFT);
		}

		x += vx * dt;
		y += vy * dt;
	}
	

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
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
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

