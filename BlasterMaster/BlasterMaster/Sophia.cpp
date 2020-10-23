#include <algorithm>
#include <assert.h>

#include "Sophia.h"
#include "Game.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
//#include "PlayerDeadState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"

#include "BulletMovingState.h"

Sophia* Sophia::_instance = NULL;

Sophia::Sophia() :GameObject() {
	IsUp = false;
	IsJumping = false;
	playerType = SOPHIA;
}

Sophia::~Sophia() {

}

void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Calculate dx, dy 
	GameObject::Update(dt);

	// Simple fall down

	vy += SOPHIA_GRAVITY * dt;

	state->Update(); 

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(dt, coObjects);
	}
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->GetStateObject() == BULLET_SMALL_HIT) {
			bullets.erase(bullets.begin() + i);
		}
	}

	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);



	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 


		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny == -1) {
			vy = 0;
			IsJumping = false;
		}
		if (ny == 1)
		{
			y += dy;
			IsJumping = true;
		}

		// Collision logic with Enemies

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Sophia::ChangeAnimation(PlayerState* newState, int stateChange) {
	delete state;

	if (stateChange == STAND_TO_MOVE) {
		idFrame = CurAnimation->currentFrame * 2;
	}
	if (stateChange == MOVE_TO_STAND) {
		//DebugOut(L"frame %d", CurAnimation->currentFrame);
		if (CurAnimation->currentFrame == 0 || CurAnimation->currentFrame == 4) {
			idFrame = 0;
		}
		else if (CurAnimation->currentFrame == 1 || CurAnimation->currentFrame == 5) {
			idFrame = 1;
		}
		else if (CurAnimation->currentFrame == 2 || CurAnimation->currentFrame == 6) {
			idFrame = 2;
		}
		else if (CurAnimation->currentFrame == 3 || CurAnimation->currentFrame == 7) {
			idFrame = 3;
		}
	}
	if (stateChange == BACK_TO_NORMAL) {
		idFrame = CurAnimation->currentFrame;
	}

	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	LPANIMATION_SET animationSet = animation_sets->Get(playerType);
	CurAnimation = animationSet->Get(newState->StateName);
}

void Sophia::Render() {
	int alpha = 255;

	CurAnimation->Render(x, y, alpha, idFrame, renderOneFrame);

	RenderBoundingBox();

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}
}

void Sophia::Fire() {
	bullet = new Bullet();
	bullet->typeBullet = BULLET_SMALL;
	if (!IsUp) {
		if (nx > 0) {
			bullet->SetPosition(x + SOPHIA_BBOX_WIDTH, y + 7 / SOPHIA_BBOX_HEIGHT);
			bullet->ChangeAnimation(BULLET_SMALL_MOVING_RIGHT);
		}
		else {
			bullet->SetPosition(x, y + 7 / SOPHIA_BBOX_HEIGHT);
			bullet->ChangeAnimation(BULLET_SMALL_MOVING_LEFT);
		}
	}
	else {
		if (nx != 0) {
			bullet->SetPosition(x + SOPHIA_BBOX_WIDTH / 3, y);
			bullet->ChangeAnimation(BULLET_SMALL_MOVING_UP);
		}
	}

	if (bullets.size() < 3) {
		bullets.push_back(bullet);
	}
}

void Sophia::DeleteBullet() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->GetX() >= x + 150.0f || bullets[i]->GetX() <= x - 150.0f) {
			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i]->GetY() <= y - 100.0f) {
			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i]->GetStateObject() == BULLET_SMALL_HIT) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (stateBoundingBox == SOPHIA_BOUNDING_BOX) {
		right = x + SOPHIA_BBOX_WIDTH;
		bottom = y + SOPHIA_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == SOPHIA_UP_BOUNDING_BOX) {
		right = x + SOPHIA_UP_BBOX_WIDTH;
		bottom = y + SOPHIA_UP_BBOX_HEIGHT;
	}

}

Sophia* Sophia::GetInstance() {
	if (_instance == NULL) {
		_instance = new Sophia();
	}
	return _instance;
}


void Sophia::OnKeyDown(int key) {
	switch (key) {
	case DIK_SPACE:
		if (!IsUp) {
			if (!IsJumping)
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = SOPHIA_MOVING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerJumpingMovingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -SOPHIA_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerJumpingMovingState());
				}
				else
				{
					ChangeAnimation(new PlayerJumpingState(), BACK_TO_NORMAL);
				}
			}
		}
		else {
			if (!IsJumping)
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = SOPHIA_MOVING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -SOPHIA_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState());
				}
				else
				{
					ChangeAnimation(new PlayerUpwardJumpingState());
				}
			}
		}
		break;
	case DIK_A:
		Reset();
		break;
	case DIK_S:
		Fire();
		DeleteBullet();
		break;
	}
}

void Sophia::OnKeyUp(int key) {
	switch (key) {
	case DIK_UPARROW:
		IsUp = false;
		CurAnimation->currentFrame = -1;
		y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		ChangeAnimation(new PlayerStandingState());
		break;
	case DIK_RIGHT:
		if (IsUp) {
			if (!IsJumping) {
				ChangeAnimation(new PlayerUpwardState(), BACK_TO_NORMAL);
				y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
			}
		}
	}
}

void Sophia::Reset(float x, float y) {
	SetPosition(x,y);
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}

