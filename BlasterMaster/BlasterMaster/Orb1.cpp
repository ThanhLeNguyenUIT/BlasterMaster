#include "Orb1.h"
#include "GlobalConfig.h"
COrb1::COrb1()
{
	typeEnemy = ORB1;
	Reset();
}

void COrb1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;*/
}

void COrb1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
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
	x += vx*dt;
	y += vy*dt;
	
	if (vx < 0 && x < 64*16) {
		x = 64*16; vx = -vx;
		ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
	}

	if (vx > 0 && x > 80*16) {
		x = 80*16; vx = -vx;
		ChangeAnimation(ORB1_STATE_WALKING_LEFT);
	}
	
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
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
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
	default:
		break;
	}
}

void COrb1::Reset() {
	nx = 1;
	ny = 1;
	ChangeAnimation(ORB1_STATE_WALKING_RIGHT);
}
