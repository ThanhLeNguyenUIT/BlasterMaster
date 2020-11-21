#include "Skull.h"

CSkull::CSkull()
{
	typeEnemy = SKULL;
	Reset();
}

void CSkull::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + JUMPER_BBOX_WIDTH;

	if (state == JUMPER_STATE_DIE)
		bottom = y + JUMPER_BBOX_HEIGHT_DIE;
	else
		bottom = y + JUMPER_BBOX_HEIGHT;*/
}

void CSkull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	float cxm, cym;
	player->GetPosition(cxm, cym);

	float cex4, cey4;
	this->GetPosition(cex4, cey4);

	if (this->nx > 0 && cex4 >= cxm)
	{
		ChangeAnimation(SKULL_STATE_JUMP_LEFT);
	}
	else if (this->nx < 0 && cex4 <= cxm)
	{
	ChangeAnimation(SKULL_STATE_JUMP_RIGHT);
	}

	x += vx * dt;
	y += vy * dt;

	if (vx < 0 && x <80*16 ) {
		x = 80 * 16;
		vx = -vx;
		nx = 1;
	}

	if (vx > 0 && x > 103*16) {
		x = 103 * 16;
		vx = -vx;
		nx = -1;
	}
	if (y > 69*16)
	{
		y = 69 * 16;
	}
	if (y < 66*16)
	{
		y = 66 * 16;
	}

}

void CSkull::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}

void CSkull::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(typeEnemy);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case SKULL_STATE_JUMP_RIGHT:
		vx = 0;
		vy = -SKULL_JUMP_Y;
		break;
	case SKULL_STATE_JUMP_LEFT:
		vx = 0;
		vy = -SKULL_JUMP_Y;
		break;
	case SKULL_STATE_WALKING_LEFT:
		vx = -SKULL_WALKING_SPEED;
		break;
	case SKULL_STATE_WALKING_RIGHT:
		vx = SKULL_WALKING_SPEED;
		break;
	default:
		break;
	}
}

void CSkull::Reset() {
	nx = -1;
	ny = 1;
	ChangeAnimation(SKULL_STATE_WALKING_LEFT);
}


