#include <algorithm>
#include <assert.h>


#include "BigJason.h"
#include "Game.h"
#include "Portal.h"
#include "Camera.h"
#include "Brick.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerCrawlingState.h"

#include "BulletMovingState.h"

BigJason* BigJason::_instance = NULL;

BigJason::BigJason() {
	IsUp = false;
	IsJumping = false;
	playerType = BIG_JASON;
}

BigJason::~BigJason() {

}

void BigJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (Allow[BIG_JASON]) {
		GameObject::Update(dt);

		// Simple fall down

		vy += BIG_JASON_GRAVITY * dt;
		DebugOut(L"vy: %f\n", player->vy);
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

			// Collision logic with Enemies

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Sophia*>(e->obj)) {
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
								vx = BIG_JASON_MOVING_SPEED;
							else
								vx = -BIG_JASON_MOVING_SPEED;
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
						//ChangeAnimation(new PlayerFallingState());
					}
				}

				if (dynamic_cast<Portal*>(e->obj))
				{
					if (e->nx != 0) x += dx;
					Portal* p = dynamic_cast<Portal*>(e->obj);
					IsTouchPortal = true;
					scene_id = p->scene_id;
					Game::GetInstance()->SwitchScene(p->GetSceneId());
					ChangeScene();
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void BigJason::ChangeScene() {

	if (IsTouchPortal && Allow[BIG_JASON]) {
		switch (scene_id) {
		
		}
	}
}

void BigJason::ChangeAnimation(PlayerState* newState, int stateChange) {
	delete state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	LPANIMATION_SET animationSet = animation_sets->Get(playerType);
	CurAnimation = animationSet->Get(newState->StateName);
}

void BigJason::Render() {
	int alpha = 255;
	if (IsRender && !IsTouchPortal) {
		CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
		RenderBoundingBox();
	}

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}

}

void BigJason::GetBoundingBox(float& left, float& top, float& right, float& bottom){
	left = x;
	top = y;

	if (stateBoundingBox == BIG_JASON_BOUNDING_BOX) {
		right = x + BIG_JASON_BBOX_WIDTH;
		bottom = y + BIG_JASON_BBOX_HEIGHT;
	}
}

BigJason* BigJason::GetInstance() {
	if (_instance == NULL) {
		_instance = new BigJason();
	}
	return _instance;
}

void BigJason::OnKeyDown(int key) {
	switch (key) {
	}
}

void BigJason::OnKeyUp(int key) {
	
}

void BigJason::Reset(float x, float y) {
	nx = 1;
	SetPosition(x, y);
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}


