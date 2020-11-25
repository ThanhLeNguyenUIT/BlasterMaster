#include <algorithm>
#include <assert.h>


#include "BigJason.h"
#include "Game.h"
#include "Portal.h"
#include "Camera.h"
#include "Brick.h"
#include "Gate.h"

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

				if (dynamic_cast<Gate*>(e->obj)) {
					Gate* g = dynamic_cast<Gate*>(e->obj);
					scene_gate = g->scene_id;
					if (e->nx != 0) {
						x += dx;
						IsTouchGate = true;
						sceneHistory.push_back(scene_gate);
					}
					if (e->ny != 0) {
						y += dy;
						IsTouchGate = true;
						sceneHistory.push_back(scene_gate);
					}
				}
			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
}

void BigJason::ChangeScene(int scene_gate) {
	scene_id = scene_gate;
	if (Allow[BIG_JASON]) {
		switch (scene_gate) {
		case 10:
			SetPosition(87.5 * BIT, 71.5 * BIT);
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
		case 11:
			if (sceneHistory[0] == 11 && sceneHistory.size() == 1) {
				SetPosition(8 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 12) {
				SetPosition(12 * BIT, 119 * BIT);
			}
			break;
		case 12:
			if (sceneHistory.rbegin()[1] == 11) {
				SetPosition(19 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 13) {
				SetPosition(28 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 21) {
				SetPosition(23 * BIT, 114 * BIT);
			}
			break;
		case 13:
			if (sceneHistory.rbegin()[1] == 12) {
				SetPosition(35 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 14) {
				SetPosition(44 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 20) {
				SetPosition(39 * BIT, 114 * BIT);
			}
			break;
		case 14:
			if (sceneHistory.rbegin()[1] == 13) {
				SetPosition(51 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 15) {
				SetPosition(60 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 19) {
				SetPosition(55 * BIT, 115 * BIT);
			}
			break;
		case 15:
			if (sceneHistory.rbegin()[1] == 14) {
				SetPosition(67 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 16) {
				SetPosition(76 * BIT, 119 * BIT);
			}
			break;
		case 16:
			if (sceneHistory.rbegin()[1] == 15) {
				SetPosition(83 * BIT, 119 * BIT);
			}
			break;
		case 17:
			if (sceneHistory.rbegin()[1] == 18) {
				SetPosition(83 * BIT, 103 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 28) {
				SetPosition(87 * BIT, 99 * BIT);
			}
			break;
		case 18:
			if (sceneHistory.rbegin()[1] == 19) {
				SetPosition(67 * BIT, 103 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 17) {
				SetPosition(76 * BIT, 103 * BIT);
			}
			break;
		case 19:
			if (sceneHistory.rbegin()[1] == 14) {
				SetPosition(55 * BIT, 106 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 18) {
				SetPosition(60 * BIT, 103 * BIT);
			}
			break;
		case 20:
			if (sceneHistory.rbegin()[1] == 13) {
				SetPosition(39 * BIT, 106 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 25) {
				SetPosition(39 * BIT, 99 * BIT);
			}
			break;
		case 21:
			if (sceneHistory.rbegin()[1] == 12) {
				SetPosition(23 * BIT, 106 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 22) {
				SetPosition(19 * BIT, 103 * BIT);
			}
			break;
		case 22:
			if (sceneHistory.rbegin()[1] == 21) {
				SetPosition(12 * BIT, 103 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 23) {
				SetPosition(7 * BIT, 99 * BIT);
			}
			break;
		case 23:
			if (sceneHistory.rbegin()[1] == 22) {
				SetPosition(7 * BIT, 90 * BIT);
			}
			break;
		case 24:
			if (sceneHistory.rbegin()[1] == 25) {
				SetPosition(28 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 32) {
				SetPosition(23 * BIT, 83 * BIT);
			}
			break;
		case 25:
			if (sceneHistory.rbegin()[1] == 20) {
				SetPosition(39 * BIT, 90 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 26) {
				SetPosition(44 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 24) {
				SetPosition(35 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 31) {
				SetPosition(39 * BIT, 83 * BIT);
			}
			break;
		case 26:
			if (sceneHistory.rbegin()[1] == 25) {
				SetPosition(51 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 27) {
				SetPosition(60 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 30) {
				SetPosition(55 * BIT, 83 * BIT);
			}
			break;
		case 27:
			if (sceneHistory.rbegin()[1] == 26) {
				SetPosition(67 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 29) {
				SetPosition(71 * BIT, 83 * BIT);
			}
			break;
		case 28:
			if (sceneHistory.rbegin()[1] == 17) {
				SetPosition(87 * BIT, 90 * BIT);
			}
			break;
		case 29:
			if (sceneHistory.rbegin()[1] == 27) {
				SetPosition(71 * BIT, 74 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 38) {
				SetPosition(71 * BIT, 67 * BIT);
			}
			break;
		case 30:
			if (sceneHistory.rbegin()[1] == 26) {
				SetPosition(55 * BIT, 74 * BIT);
			}
		case 31:
			if (sceneHistory.rbegin()[1] == 25) {
				SetPosition(39 * BIT, 74 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 36) {
				SetPosition(39 * BIT, 67 * BIT);
			}
			break;
		case 32:
			if (sceneHistory.rbegin()[1] == 24) {
				SetPosition(23 * BIT, 74 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 33) {
				SetPosition(19 * BIT, 71 * BIT);
			}
			break;
		case 33:
			if (sceneHistory.rbegin()[1] == 32) {
				SetPosition(12 * BIT, 71 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 34) {
				SetPosition(7 * BIT, 67 * BIT);
			}
			break;
		case 34:
			if (sceneHistory.rbegin()[1] == 33) {
				SetPosition(7 * BIT, 58 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 35) {
				SetPosition(12 * BIT, 55 * BIT);
			}
			break;
		case 35:
			if (sceneHistory.rbegin()[1] == 34) {
				SetPosition(19 * BIT, 55 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 36) {
				SetPosition(28 * BIT, 55 * BIT);
			}
			break;
		case 36:
			if (sceneHistory.rbegin()[1] == 35) {
				SetPosition(35 * BIT, 55 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 31) {
				SetPosition(39 * BIT, 58 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 37) {
				SetPosition(44 * BIT, 55 * BIT);
			}
			break;
		case 37:
			if (sceneHistory.rbegin()[1] == 36) {
				SetPosition(51 * BIT, 55 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 39) {
				SetPosition(55 * BIT, 51 * BIT);
			}
			break;
		case 38:
			if (sceneHistory.rbegin()[1] == 29) {
				SetPosition(71 * BIT, 58 * BIT);
			}
			break;
		case 39:
			if (sceneHistory.rbegin()[1] == 37) {
				SetPosition(55 * BIT, 42 * BIT);
			}
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

void BigJason::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
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
	case DIK_RIGHT:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	case DIK_LEFT:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	case DIK_UP:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	case DIK_DOWN:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	}
}

void BigJason::OnKeyUp(int key) {
	switch (key) {
	case DIK_RIGHT:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	case DIK_LEFT:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	case DIK_UP:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	case DIK_DOWN:
		if (Allow[BIG_JASON] && IsTouchGate) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
		}
		break;
	}

}

void BigJason::Reset(float x, float y) {
	nx = 1;
	SetPosition(x, y);
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}