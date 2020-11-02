#include <algorithm>
#include <assert.h>

#include "Sophia.h"
#include "Jason.h"
#include "Game.h"
#include "Portal.h"
#include "Camera.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerUpwardState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerOpenState.h"

#include "BulletMovingState.h"

Sophia* Sophia::_instance = NULL;

Sophia::Sophia() :GameObject() {
	IsUp = false;
	IsJumping = false;
	playerType = SOPHIA;
	allow[SOPHIA] = true;
	allow[JASON] = false;
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

		x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.3f;

		if (!IsJumping) {
			if (nx != 0) vx = 0;
		}
		else if (nx != 0) {
			if (nx == -1)
				vx = SOPHIA_MOVING_SPEED;
			else
				vx = -SOPHIA_MOVING_SPEED;
		}
		
		if (ny == -1) {
			vy = 0;
			IsJumping = false;
		}
		if (ny == 1)
		{
			vy = 0;
			if (!IsUp)
				ChangeAnimation(new PlayerFallingState());
		}

		// Collision logic with Enemies
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			//{
			//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -MARIO_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{
			//		if (untouchable == 0)
			//		{
			//			if (goomba->GetState() != GOOMBA_STATE_DIE)
			//			{
			//				if (level > MARIO_LEVEL_SMALL)
			//				{
			//					level = MARIO_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(MARIO_STATE_DIE);
			//			}
			//		}
			//	}
			//} // if Goomba
			if (dynamic_cast<Portal*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				Portal* p = dynamic_cast<Portal*>(e->obj);
				IsTouchPortal = true;
				scene_id = p->scene_id;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Sophia::CheckState(int stateChange) {
	if (stateChange == STAND_TO_MOVE) {
		idFrame = CurAnimation->currentFrame * 2;
	}
	if (stateChange == MOVE_TO_NORMAL) {
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
	if (stateChange == NORMAL) {
		idFrame = CurAnimation->currentFrame;
	}
	if (stateChange == UPWARD_TO_NORMAL) {
		
	}
	/*if (stateChange == TURN_TO_NORMAL) {
		if (nx > 0) {
			for (int i = 0; i < 4; i++) {
				if (state->StateName == static_cast<STATENAME>(i + 22))
					idFrame = i;
			}
		}
		else {
			for (int i = 3; i >= 0; i--) {
				if (state->StateName == static_cast<STATENAME>(25-i))
					idFrame = i;
			}
		}
	}*/
}

void Sophia::ChangeAnimation(PlayerState* newState, int stateChange) {
	delete state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	CheckState(stateChange);
	LPANIMATION_SET animationSet = animation_sets->Get(playerType);
	CurAnimation = animationSet->Get(newState->StateName);
}

void Sophia::Render() {
	int alpha = 255;
	if (!IsTouchPortal) {
		if (!RenderBack) {
			CurAnimation->Render(x, y, alpha, idFrame, renderOneFrame);
		}
		else {
			CurAnimation->RenderBack(x, y, alpha, idFrame, renderOneFrame);
		}
	}

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
	else if (stateBoundingBox == SOPHIA_OPEN_BOUNDING_BOX) {
		right = x + SOPHIA_OPEN_BBOX_WIDTH;
		bottom = y + SOPHIA_OPEN_BBOX_HEIGHT;
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
					ChangeAnimation(new PlayerJumpingState(), NORMAL);
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
					ChangeAnimation(new PlayerUpwardJumpingMovingState(), UPWARD_TO_NORMAL);
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -SOPHIA_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState(), UPWARD_TO_NORMAL);
				}
				else
				{
					ChangeAnimation(new PlayerUpwardJumpingState(),UPWARD_TO_NORMAL);
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
	case DIK_Q:
		if (!IsOpen) {
			vx = 0;
			vy = 0;
			IsOpen = true;
			ChangeAnimation(new PlayerOpenState());
			allow[SOPHIA] = false;
			allow[JASON] = true; // allow jason to get out of car
			playerSmall->Reset(player->x, player->y);
			playerSmall->IsRender = true;
		}
		else {
			IsOpen = false;
			player->y = player->y + (SOPHIA_OPEN_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
			ChangeAnimation(new PlayerStandingState());
		}
		break;
	}
}

void Sophia::OnKeyUp(int key) {
	switch (key) {
	case DIK_UP:
		IsUp = false;
		CurAnimation->currentFrame = -1;
		if (!player->IsJumping)
			y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		if (nx > 0) {
			for (int i = 0; i < 4; i++) {
				if (state->StateName == static_cast<STATENAME>(i + 12))
					idFrame = i;
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				if (state->StateName == static_cast<STATENAME>(i + 16))
					idFrame = i;
			}
		}
		ChangeAnimation(new PlayerStandingState());
		break;
	case DIK_RIGHT:
		if (IsUp) {
			if (!IsJumping) {
				idFrame = 3;
				CurAnimation->currentFrame = -1;
				ChangeAnimation(new PlayerUpwardState(), NORMAL);
				y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
			}
		}
		break;
	case DIK_LEFT:
		if (IsUp) {
			if (!IsJumping) {
				idFrame = 3;
				CurAnimation->currentFrame = -1;
				ChangeAnimation(new PlayerUpwardState(), NORMAL);
				y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
			}
		}
		break;
	}
}

void Sophia::Reset(float x, float y) {
	nx = 1;
	SetPosition(x,y);
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}

