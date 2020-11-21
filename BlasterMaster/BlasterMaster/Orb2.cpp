#include "Orb2.h"
#include "GlobalConfig.h"
COrb2::COrb2()
{
	typeEnemy = ORB2;
	Reset();
}

void COrb2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;*/
}

void COrb2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	float cxm, cym;
	player->GetPosition(cxm, cym);

	float cex, cey;
	this->GetPosition(cex, cey);

	double kc = sqrt((cex - cxm) * (cex - cxm) + (cey - cym) * (cey - cym));

	if (kc <= 120)
	{
		if (cex < cxm)
		{
			//state = ORB2_STATE_TURN_RIGHT;
			ChangeAnimation(ORB2_STATE_TURN_RIGHT);
		}
		else if (cex > cxm)
		{
			//state = ORB2_STATE_TURN_LEFT;
			ChangeAnimation(ORB2_STATE_TURN_LEFT);
		}
		else if (cex == cxm)
		{
			//state = ORB2_STATE_TURN_BOTTOM;
			ChangeAnimation(ORB2_STATE_TURN_BOTTOM);
		}
		//ChangeAnimation(state);
	}

	x += vx * dt;
	y += vy * dt;

	if (vx < 0 && x < 64 * 16) {
		x = 64 * 16; vx = -vx;
		ChangeAnimation(ORB2_STATE_WALKING_RIGHT);
	}

	if (vx > 0 && x > 80 * 16) {
		x = 80 * 16; vx = -vx;
		ChangeAnimation(ORB2_STATE_WALKING_LEFT);
	}
	if (y <= 65*16 || y >= 73*16) {
		vy = -vy;
		if (y <= 65 * 16)
		{
			y = 65 * 16;
		}
		else if (y >= 73 * 16)
		{
			y = 73 * 16;
		}

	}
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
		vy = ORB2_WALKING_TURN;
		vx = -ORB2_WALKING_TURN;
		break;
	case ORB2_STATE_TURN_RIGHT:
		nx = 1;
		vy = ORB2_WALKING_TURN;
		vx = ORB2_WALKING_TURN;
		break;
	case ORB2_STATE_TURN_BOTTOM:
		nx = 1;
		vx = 0;
		vy = ORB2_WALKING_TURN;
		break;
	default:
		break;
	}
}

void COrb2::Reset() {
	nx = 1;
	ny = 1;
	ChangeAnimation(ORB2_STATE_WALKING_RIGHT);
}
