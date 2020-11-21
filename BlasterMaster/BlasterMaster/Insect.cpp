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

	DWORD timenow = GetTickCount();

	if ((timenow - dt) % 400 == 0) 
	{
		if (nx > 0 && this->StateObject!= INSECT_STATE_JUMP_RIGHT)
		{
			ChangeAnimation(INSECT_STATE_JUMP_RIGHT);
		}
		else if (nx < 0 && this->StateObject != INSECT_STATE_JUMP_LEFT)
		{
			ChangeAnimation(INSECT_STATE_JUMP_LEFT);
		}
		
	}
	else if(nx>0)
	{
		ChangeAnimation(INSECT_STATE_WALKING_RIGHT);
	}
	else if (nx < 0) 
	{
		ChangeAnimation(INSECT_STATE_WALKING_LEFT);
	}

	x += (vx * dt) / 3;
	y += vy * dt;

	if (vx < 0 && x < 73*16) {
		x = 73 * 16; 
		ChangeAnimation(INSECT_STATE_JUMP_RIGHT);
	}

	if (vx > 0 && x > 79*16) {
		x = 79 * 16; 
		ChangeAnimation(INSECT_STATE_JUMP_LEFT);
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
	nx = 1;
	ChangeAnimation(INSECT_STATE_WALKING_RIGHT);
}

