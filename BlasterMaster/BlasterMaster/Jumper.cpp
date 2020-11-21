#include "Jumper.h"

CJumper::CJumper()
{
	typeEnemy = JUMPER;
	Reset();
}

void CJumper::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + JUMPER_BBOX_WIDTH;

	if (state == JUMPER_STATE_DIE)
		bottom = y + JUMPER_BBOX_HEIGHT_DIE;
	else
		bottom = y + JUMPER_BBOX_HEIGHT;*/
}

void CJumper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 
	float cxm, cym;
	player->GetPosition(cxm, cym);

	float cex, cey;
	this->GetPosition(cex, cey);

	double kc = sqrt((cex - cxm) * (cex - cxm) + (cey - cym) * (cey - cym));

	if (kc <= 100)
	{
		if (cex < cxm && nx > 0 && cey >= 1158)
		{
			ChangeAnimation(JUMPER_STATE_JUMP_RIGHT);
		}
		else if (cex > cxm && nx < 0 && cey >= 1158)
		{
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
	

	x += vx * dt;
	y += vy * dt;

	vy += JUMPER_GRAVITY;



	if (vx < 0 && x < 66*16) {
		x = 66 * 16;
		ChangeAnimation(JUMPER_STATE_WALKING_RIGHT);
	}

	if (vx > 0 && x > 84*16) {
		x = 84 * 16;
		ChangeAnimation(JUMPER_STATE_WALKING_LEFT);
	}
	if (y > 72*16+6)
	{
		y = 72 * 16 + 6;
	}
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
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
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
	nx = -1;
	ny = 0;
	ChangeAnimation(JUMPER_STATE_WALKING_LEFT);
}