#include "BossHand.h"
#include "Brick.h"
#include "Portal.h"
#include "Power.h"
#include "DamageBrick.h"
#include "Boss.h"
#include "time.h"




CBossHand::CBossHand(float x, float y, int typeHand, float x_boss, float y_boss)
{
	this->x = x;
	this->y = y;
	this->typeHand = typeHand;
	if (typeHand == 1) {
		type = BOSS_HAND_LEFT;
	}
	else {
		type = BOSS_HAND_RIGHT;
	}
	Reset();
}

void CBossHand::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + 18;
	bottom = y + 32;*/
}

void CBossHand::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	Move();
	this->x += dx;
	this->y += dy;
}

void CBossHand::Render()
{
	//int alpha = 255;
	CurAnimation->Render(x, y, alpha1);
	RenderBoundingBox();
}

void CBossHand::ChangeAnimation(STATEOBJECT StateObject) {
	this->StateObject = StateObject;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(this->StateObject);
}

void CBossHand::Reset() {
	//nx = 1;
	if (typeHand == 1) {
		ChangeAnimation(BOSS_LEFT_HAND_NORMAL);
		SetSpeed(BOSS_HAND_WALKING_SPEED_X, BOSS_HAND_WALKING_SPEED_Y);
	}
	else {
		ChangeAnimation(BOSS_RIGHT_HAND_NORMAL);
		SetSpeed(BOSS_HAND_WALKING_SPEED_X, BOSS_HAND_WALKING_SPEED_Y);
	}
}


void CBossHand::Move() {
	float left_hand_min_x = x_boss - 46;
	float left_hand_max_x = x_boss + 10;
	float hand_max_y = y_boss + 90;
	float hand_min_y = y_boss - 40;
	float right_hand_min_x = x_boss + 32;
	float right_hand_max_x = x_boss + 98;

	if (typeHand == 1) {
		if (x >= left_hand_max_x)
			vx = -BOSS_HAND_WALKING_SPEED_X;
		if (x <= left_hand_min_x) {
			vx = BOSS_HAND_WALKING_SPEED_X;
		}
		if (vy == 0) {
			if (y > y_boss) vy = -BOSS_HAND_WALKING_SPEED_Y;
			if (y <= y_boss) vy = BOSS_HAND_WALKING_SPEED_Y;
			//isStop = false;
		}
	}
	else {
		if (x >= right_hand_max_x)
			vx = -BOSS_HAND_WALKING_SPEED_X;
		if (x <= right_hand_min_x) {
			vx = BOSS_HAND_WALKING_SPEED_X;
		}
		if (vy == 0) {
			if (y > y_boss) vy = -BOSS_HAND_WALKING_SPEED_Y;
			if (y <= y_boss) vy = BOSS_HAND_WALKING_SPEED_Y;
			//isStop = false;
		}
	}
	if (y >= hand_max_y || y <= hand_min_y) {
		int rand1 = 0;
		while (rand1 == 0) {
			rand1 = rand() % 1 + (-1);
		}
		vx = rand1 * BOSS_HAND_WALKING_SPEED_X;
		vy = 0;
	}
}