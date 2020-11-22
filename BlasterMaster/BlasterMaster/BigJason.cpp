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
#include "PlayerOpenState.h"

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

		//vy += BIG_JASON_GRAVITY * dt;
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
			y += min_ty * dy + ny * 0.1f;

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
					Portal* p = dynamic_cast<Portal*>(e->obj);
					IsTouchGate = true;
					scene_gate = p->scene_id;
					IsChangeScene = true;
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void BigJason::ChangeScene(int scene_gate) {
	if (Allow[BIG_JASON]) {
		switch (scene_gate) {
		case 10:
			SetPosition(87 * BIT, 71 * BIT);
			ny = -1;
			break;
		case 5:
			IsTouchGate = false;
			playerSmall->IsTouchGate = false;
			player->IsRender = true;
			playerSmall->IsRender = true;
			playerBig->IsRender = false;
			Allow[BIG_JASON] = false;
			Allow[JASON] = true;
			Allow[SOPHIA] = true;
			player->ChangeAnimation(new PlayerOpenState());
			playerSmall->ChangeAnimation(new PlayerStandingState());
			player->SetPosition(player->oldCx, player->oldCy);
			playerSmall->SetPosition(playerSmall->oldCx, playerSmall->oldCy - 10);
			Allow[SOPHIA] = false;
			break;
		}
	}
}

void BigJason::ChangeAnimation(PlayerState* newState, int stateChange) {
	delete state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	LPANIMATION_SET animationSet = animation_sets->Get(playerType);
	CurAnimation = animationSet->Get(StateName);
}

void BigJason::Render() {
	int alpha = 255;
	if (IsRender && !IsTouchGate) {
		CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
		RenderBoundingBox();
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
	case DIK_E:
		if (Allow[BIG_JASON]) {
			Allow[JASON] = false;
			Allow[SOPHIA] = true;
			Allow[BIG_JASON] = false;
			playerBig->IsRender = false;
			player->ChangeAnimation(new PlayerStandingState());
		}
		break;
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