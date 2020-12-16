#include "Mine.h"

CMine::CMine()
{
	health = 1;
	type = MINE;
	width = MINE_BBOX_WIDTH;
	height = MINE_BBOX_HEIGHT;
	Reset();
}

void CMine::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 6;
	right = x + MINE_BBOX_WIDTH;
	bottom = y + 6 + MINE_BBOX_HEIGHT;
}

void CMine::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (health <= 0) {
		StateObject = ENEMY_DEAD;
		isDead = true;
	}
}

void CMine::Render()
{
	int alpha = 255;
	CurAnimation->Render(x, y + 6, alpha);
	RenderBoundingBox();
}

void CMine::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
	switch (this->StateObject)
	{
	case MINE_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	}
}

void CMine::Reset() {
	nx = 1;
	ChangeAnimation(MINE_STATE_IDLE);
}

