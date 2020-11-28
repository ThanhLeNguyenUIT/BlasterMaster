#include <algorithm>
#include <assert.h>


#include "Jason.h"
#include "Game.h"
#include "Portal.h"
#include "Stair.h"
#include "Gate.h"
#include "Camera.h"
#include "Brick.h"
#include "DamageBrick.h"
#include "Worm.h"
#include "Orb1.h"
#include "Power.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerCrawlingState.h"
#include "PlayerClimbingState.h"
#include "PlayerDeadState.h"
#include "BulletMovingState.h"

Jason* Jason::_instance = NULL;

Jason::Jason() {
	IsUp = false;
	IsJumping = false;
	playerType = JASON;
}

Jason::~Jason() {

}

void Jason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (Allow[JASON]) {
		GameObject::Update(dt);

		// Simple fall down
		if (!IsTouchStair)
			vy += JASON_GRAVITY * dt;
		state->Update();
		if (IsTouchStair && y <= 25 * BIT) {
			ChangeAnimation(new PlayerStandingState());
			IsTouchStair = false;
		}
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
		// change state die if health = 0
		if (health == 0) {
			ChangeAnimation(new PlayerDeadState());
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
				if (player != NULL) {
					if (dynamic_cast<Sophia*>(e->obj)) {
						if (e->nx != 0) x += dx;
						if (e->ny != 0) y += dy;
					}
				}

				if (dynamic_cast<Brick*>(e->obj)) {
					if (!IsTouchStair) {
						if (e->nx != 0) vx = 0;
						if (e->ny == -1)
						{
							vy = 0;
							IsJumping = false;
						}
						else if (e->ny == 1)
						{
							vy = 0;
						}
					}
					else {
						if (e->nx != 0) vx = 0;
						if (e->ny == 1) y += dy;
						if (e->ny == -1) {
							ChangeAnimation(new PlayerStandingState());

						}
					}
				}
				if (dynamic_cast<DamageBrick*>(e->obj)) {
					if (e->nx != 0) vx = 0;
					if (e->ny == -1)
					{
						// damage
						if (timeDamaged == TIME_DEFAULT) {
							timeDamaged = GetTickCount();
						}
						vy = 0;
						IsJumping = false;
						if (GetTickCount() - timeDamaged >= 300) {
							health = health - 1;
							timeDamaged = GetTickCount();
						}
					}
					else if (e->ny == 1)
					{
						vy = 0;
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

				else if (dynamic_cast<Stair*>(e->obj))
				{
					Stair* p = dynamic_cast<Stair*>(e->obj);
					if (e->nx != 0) {
						x += dx;
						if (!IsJumping)
							IsTouchStair = true;
					}
					if (e->ny == 1) {
						y += dy;
					}
					if (e->ny == -1) {
						vy = 0;
						IsTouchStair = true;
					}
				}

				if (dynamic_cast<Gate*>(e->obj)) {
					Gate* p = dynamic_cast<Gate*>(e->obj);
					scene_gate = p->scene_id;
					if (e->nx != 0) {
						x += dx;
						IsTouchGate = true;
					}
					if (e->ny != 0) {
						y += dy;
						IsTouchGate = true;
					}
					if (e->nx == 0 || e->ny == 0) {
						IsTouchGate = true;
					}
				}

				if (dynamic_cast<Enemy*>(e->obj)) {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;

					health = health - 1;
				}

				if (dynamic_cast<Power*>(e->obj)) {

					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;

					Power* p = dynamic_cast<Power*>(e->obj);
					p->IsTouch = true;
					if (health < 8)
						health = health + 1;
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Jason::ChangeScene() {

	if (IsTouchPortal && Allow[JASON]) {
		switch (scene_id) {
		case 2:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				SetPosition(80, 1165);
			}
			if (nx < 0) {
				SetPosition(560, 1165);
			}
			break;
		case 1:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				SetPosition(123 * BIT, 1165);
			}
			break;
		case 3:
			// change scene from scene 2 to scene 1
			if (x >= 560 && nx > 0) {
				ChangeAnimation(new PlayerStandingState());
				IsTouchPortal = false;
			}
			else if (x <= 432 && nx < 0) {
				ChangeAnimation(new PlayerStandingState());
				IsTouchPortal = false;
			}
			break;
		case 4:
			if (x >= 1088 && nx > 0) {
				ChangeAnimation(new PlayerStandingState());
				IsTouchPortal = false;
			}
			else if (x <= 960 && nx < 0) {
				ChangeAnimation(new PlayerStandingState());
				IsTouchPortal = false;
			}
			break;
		/*case 5:
			if (y > 25 * BIT) {
				ChangeAnimation(new PlayerStandingState());
				IsTouchPortal = false;
				SetPosition(36 * BIT, 25 * BIT);
			}*/
		}

	}
}

void Jason::ChangeAnimation(PlayerState* newState, int stateChange) {
	delete state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	LPANIMATION_SET animationSet = animation_sets->Get(playerType);
	CurAnimation = animationSet->Get(StateName);
}

void Jason::Render() {
	int alpha = 255;
	if (IsRender && !IsTouchPortal) {
		CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
		RenderBoundingBox();
	}
}

void Jason::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;

	if (stateBoundingBox == JASON_BOUNDING_BOX) {
		right = x + JASON_BBOX_WIDTH;
		bottom = y + JASON_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == JASON_CRAWLING_BOUNDING_BOX) {
		right = x + JASON_CRAWLING_BBOX_WIDTH;
		bottom = y + JASON_CRAWLING_BBOX_HEIGHT;
	}
}

Jason* Jason::GetInstance() {
	if (_instance == NULL) {
		_instance = new Jason();
	}
	return _instance;
}

void Jason::OnKeyDown(int key) {
	switch (key) {
	case DIK_SPACE:
		IsTouchStair = false;
		ChangeAnimation(new PlayerJumpingState());
		playerSmall->IsJumping = true;
		break;
	case DIK_3:
		SetPosition(565, 112);
		break;
	case DIK_Q: // get on the car
		if (Allow[JASON]) {
			if (x >= player->x && x <= player->x + SOPHIA_BBOX_WIDTH) {
				playerSmall->ChangeAnimation(new PlayerJumpingState());
				IsRender = false;
				player->IsOpen = false;
				Allow[JASON] = false;
				Allow[SOPHIA] = true;
				Allow[BIG_JASON] = false;
				player->y = player->y + (SOPHIA_OPEN_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
				player->ChangeAnimation(new PlayerStandingState());
			}
		}
		break;
	case DIK_S:
		if (timeStartAttack == TIME_DEFAULT) {
			timeStartAttack = GetTickCount();
		}
		IsFiring = true;
		break;
	case DIK_DOWN:
		if (!IsCrawling) {
			ChangeAnimation(new PlayerCrawlingState());
			RenderOneFrame = true;
			IsCrawling = true;
		}
		if (IsTouchStair) {
			ny = -1;
			ChangeAnimation(new PlayerClimbingState());
		}
		if (IsTouchGate) {
			IsCrawling = false;
			player->oldCx = player->x;
			player->oldCy = player->y;
			playerSmall->oldCx = playerSmall->x;
			playerSmall->oldCy = playerSmall->y;
			playerBig->scene_gate = scene_gate;
			Game::GetInstance()->SwitchScene(scene_gate);
			Allow[JASON] = false;
			Allow[SOPHIA] = false;
			Allow[BIG_JASON] = true;
			player->IsRender = false;
			playerSmall->IsRender = false;
			playerBig->IsRender = true;
			playerBig->ChangeScene(playerBig->scene_gate);
		}
		break;
	case DIK_UP:
		if (IsCrawling) {
			playerSmall->y -= (JASON_BBOX_HEIGHT - JASON_CRAWLING_BBOX_HEIGHT);
			ChangeAnimation(new PlayerStandingState());
			IsCrawling = false;
		}
		if (IsTouchStair) {
			ny = 1;
			ChangeAnimation(new PlayerClimbingState());
		}
		break;
	}
}

void Jason::OnKeyUp(int key) {
	switch (key) {
	case DIK_UP:
		if (IsTouchStair) {
			ChangeAnimation(new PlayerClimbingState());
			RenderOneFrame = true;
			vy = 0;
		}
		break;
	case DIK_DOWN:
		if (IsTouchStair) {
			ChangeAnimation(new PlayerClimbingState());
			RenderOneFrame = true;
			vy = 0;
		}
		break;
	}
}

void Jason::Reset(float x, float y) {
	nx = 1;
	SetPosition(x, y);
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}


