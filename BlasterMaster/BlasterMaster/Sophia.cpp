#include <algorithm>
#include <assert.h>

#include "Sophia.h"
#include "Jason.h"
#include "Game.h"
#include "Portal.h"
#include "Camera.h"
#include "Brick.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerUpwardState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerOpenState.h"
#include "PlayerJumpTurningState.h"

#include "BulletMovingState.h"

Sophia* Sophia::_instance = NULL;

Sophia::Sophia() :GameObject() {
	IsUp = false;
	playerType = SOPHIA;
	Allow[SOPHIA] = true;
	Allow[JASON] = false;
}

Sophia::~Sophia() {

}

void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// Calculate dx, dy 
	GameObject::Update(dt);
	// Simple fall down
	
	vy += SOPHIA_GRAVITY * dt;
	if(Allow[SOPHIA])
		state->Update(); 

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);

	// time fire bullet
	if (GetTickCount() - timeStartAttack >= TIME_FIRING) {
		timeStartAttack = TIME_DEFAULT;
		IsFiring = false;
	}

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
		//vy = 999;
		// Collision logic with Enemies
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Jason*>(e->obj)) {
				if (e->nx != 0) x += dx;
				if (e->ny != 0) y += dy;
			}

			if (dynamic_cast<Brick*>(e->obj)) {
				if (e->nx != 0) {

					if (!IsJumping) {
						vx = 0;
					}
					else {
						if (this->nx == 1)
							vx = SOPHIA_MOVING_SPEED;
						else
							vx = -SOPHIA_MOVING_SPEED;
					}
				}
				if (e->ny == -1)
				{
					vy = 0;
					IsJumping = false;
				}
				else if (e->ny == 1)
				{
					vy = 0;
					ChangeAnimation(new PlayerFallingState());
				}
			}

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
			CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
		}
		else {
			CurAnimation->RenderBack(x, y, alpha, idFrame, RenderOneFrame);
		}
	}

	if (IsUp) {
		if (CurAnimation->IsFinish)
		{
			count++;
			idFrame++;
			if (idFrame >= 2) {
				idFrame = 0;
			}
		}
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}

	if(!IsTouchPortal)
		RenderBoundingBox();
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
		if (!IsJumping) {
			if (!IsUp) {
				ChangeAnimation(new PlayerJumpingState(), NORMAL);
				IsJumping = true;
			}
			else {
				ChangeAnimation(new PlayerUpwardJumpingState());
				IsJumping = true;
				RenderOneFrame = true;
			}
		}
		break;
	case DIK_A:
		Reset();
		break;
	case DIK_S:
		if (timeStartAttack == TIME_DEFAULT) {
			timeStartAttack = GetTickCount();
		}
		IsFiring = true;
		break;
	case DIK_Q:
		if (Allow[SOPHIA]) {
			if (!IsOpen) {
				IsOpen = true;
				ChangeAnimation(new PlayerOpenState());
				Allow[SOPHIA] = false;
				Allow[JASON] = true; // allow jason to get out of car
				playerSmall->IsRender = true;
				playerSmall->Reset(player->x + (SOPHIA_BBOX_WIDTH / 3), player->y);
			}
		}
		break;
	}
}

void Sophia::OnKeyUp(int key) {
	switch (key) {
	case DIK_SPACE:
		vy += SOPHIA_GRAVITY * dt * 10;
		//ChangeAnimation()
		break;
	case DIK_UP:
		IsUp = false;
		count = 0;
		CurAnimation->currentFrame = -1;
		if (!IsJumping)
			y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		ChangeAnimation(new PlayerStandingState());
		break;
	case DIK_RIGHT:
		if (IsUp) {
			if (!IsJumping) {
				ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
				RenderOneFrame = true;
				vx = 0;
				vy = 0;
			}
		}
		break;
	case DIK_LEFT:
		if (IsUp) {
			if (!IsJumping) {
				ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
				RenderOneFrame = true;
				vx = 0;
				vy = 0;
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

