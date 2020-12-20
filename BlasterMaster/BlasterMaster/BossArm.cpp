#include "BossArm.h"
#include "Brick.h"
#include "Portal.h"
#include "Power.h"
#include "DamageBrick.h"


CBossArm::CBossArm(float x, float y, int typeArm, float _vx, float _vy)
{
	this->x = x;
	this->y = y;
	this->typeArm = typeArm;
	if (type == 1) {
		type = BOSS_ARM_LEFT;
	}
	else {
		type = BOSS_ARM_RIGHT;
	}
	SetSpeed(_vx, _vy);
	new_vx = _vx;
	new_vy = _vy;
	Reset();
}

void CBossArm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + 16;
	bottom = y + 17;*/
}

void CBossArm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (health == 0) {
		StateObject = ENEMY_DEAD;
	}

	// turn off collision when die 
	if (StateObject != ENEMY_DEAD)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		MoveFollow(x_follow, y_follow);
		x += dx;
		y += dy;


	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			delete e;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBossArm::Render()
{
	//int alpha = 255;
	CurAnimation->Render(x, y, alpha1);
	RenderBoundingBox();
}

void CBossArm::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

void CBossArm::MoveFollow(float x_follow, float y_follow) {
	if (x < x_follow) vx = new_vx;
	else if (x > x_follow) vx = -new_vx;
	else vx = 0;

	if (y < y_follow) vy = new_vy;
	else if (y > y_follow) vy = -new_vy;
	else vy = 0;
}

void CBossArm::Reset() {
	if (type == 1) {
		ChangeAnimation(BOSS_LEFT_ARM_NORMAL);
	}
	else ChangeAnimation(BOSS_RIGHT_ARM_NORMAL);
}

