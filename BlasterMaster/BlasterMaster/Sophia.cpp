#include <algorithm>
#include <assert.h>

#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"
#include "Game.h"
#include "Portal.h"
#include "Camera.h"
#include "Brick.h"
#include "Stair.h"
#include "DamageBrick.h"
#include "Orb1.h"
#include "Worm.h"
#include "Power.h"

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
#include "PlayerUpperState.h"
#include "PlayerDeadState.h"

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
	if (Allow[SOPHIA]) {
	
		GameObject::Update(dt);
		// Simple fall down

		vy += SOPHIA_GRAVITY * dt;
		
		state->Update();
		// change scene 
		

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
		// create bullet when DIK_S
		if (IsFiring) {
			bullet = new Bullet();
			bullet->typeBullet = BULLET_SMALL;
			if (!IsUp) {
				if (nx > 0) {
					bullet->SetPosition(x + SOPHIA_BBOX_WIDTH / 3, y + 7 / SOPHIA_BBOX_HEIGHT);
					bullet->ChangeAnimation(BULLET_BIG_MOVING_RIGHT);
				}
				else {
					bullet->SetPosition(player->x + SOPHIA_BBOX_WIDTH / 3, player->y + 7 / SOPHIA_BBOX_HEIGHT);
					bullet->ChangeAnimation(BULLET_BIG_MOVING_LEFT);
				}
			}
			else {
				if (player->nx != 0) {
					bullet->SetPosition(player->x + SOPHIA_BBOX_WIDTH / 3, player->y);
					bullet->ChangeAnimation(BULLET_BIG_MOVING_UP);
				}
			}
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
	
				/*if (dynamic_cast<Jason*>(e->obj)) {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}*/
				if (dynamic_cast<Brick*>(e->obj)) {
					
					if (e->nx != 0) {
						vx = 0;
					}
					if (e->ny == -1)
					{
						if (IsJumping) {
							vx = 0;
							RenderOneFrame = true;
						}
						vy = 0;
						IsJumping = false;
					}
					else if (e->ny == 1)
					{
  						vy = 0;
					}
				}

				else if (dynamic_cast<DamageBrick*>(e->obj)) {
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

				else if (dynamic_cast<Portal*>(e->obj))
				{
					if (e->nx != 0) x += dx;
					Portal* p = dynamic_cast<Portal*>(e->obj);
					IsTouchPortal = true;
					IsChangeScene = true;
					scene_id = p->scene_id;
				}

				else if (dynamic_cast<Stair*>(e->obj))
				{
					if (e->nx != 0) x += dx;
					Stair* p = dynamic_cast<Stair*>(e->obj);
				}

				// collison with monster

				else if (dynamic_cast<Enemy*>(e->obj)) {
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;

					health = health - 1;
				}

				else if (dynamic_cast<Power*>(e->obj)) {

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

void Sophia::ChangeScene() {
	if (IsTouchPortal && Allow[SOPHIA]) {
		switch (scene_id) {
		case 2:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				SetPosition(80, 1152);
			}
			if (nx < 0) {
				SetPosition(560, 72);
			}
			break;
		case 1:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				SetPosition(123 * BIT, 72 * BIT);
			}
			break;
		case 3:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx < 0) {
				SetPosition(27 * 16, 9 * 16);
			}
			else SetPosition(590, 100);
			break;
		case 4:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			SetPosition(4 * BIT, 54 * BIT);
			break;
		case 5:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			SetPosition(59 * BIT, 88 * BIT);
			break;
		case 6:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			SetPosition(68 * BIT, 24 * BIT);
			break;
		case 7:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			SetPosition(100 * BIT, 24 * BIT);
			break;
		case 8:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			SetPosition(91 * BIT, 40 * BIT);
			break;
		case 9:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			SetPosition(68 * BIT, 56 * BIT);
			break;

		}
	}
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
	CurAnimation = animationSet->Get(StateName);
}

void Sophia::Render() {
	int alpha = 255;
	if (IsRender && !IsTouchPortal) {
		if (!RenderBack) {
			CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
		}
		else {
			CurAnimation->RenderBack(x, y, alpha, idFrame, RenderOneFrame);
		}
		RenderBoundingBox();
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
}



void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (stateBoundingBox == SOPHIA_BOUNDING_BOX) {
		left = x;
		top = y;
		right = x + SOPHIA_BBOX_WIDTH;
		bottom = y + SOPHIA_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == SOPHIA_UP_BOUNDING_BOX) {
		left = x;
		top = y + SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT;
		right = x + SOPHIA_BBOX_WIDTH;
		bottom = top + SOPHIA_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == SOPHIA_OPEN_BOUNDING_BOX) {
		left = x;
		top = y;
		right = x + SOPHIA_OPEN_BBOX_WIDTH;
		bottom = top + SOPHIA_OPEN_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == SOPHIA_DEAD_BOUNDING_BOX) {
		left = x;
		top = y;
		right = x + SOPHIA_DEAD_BBOX_WIDTH;
		bottom = top + SOPHIA_DEAD_BBOX_HEIGHT;
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
		//oldCy = player->y;
		if (!IsJumping) {
			if (!IsUp) {
				ChangeAnimation(new PlayerJumpingState(), NORMAL);
				IsJumping = true;
			}
			else {
				ChangeAnimation(new PlayerUpwardJumpingState());
				IsJumping = true;
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
		if (Allow[SOPHIA] && !IsJumping && !IsUp) {
			if (!IsOpen) {
				IsOpen = true;
				ChangeAnimation(new PlayerOpenState());
				Allow[SOPHIA] = false;
				Allow[JASON] = true; // allow jason to get out of car
				playerSmall->IsRender = true;
				playerSmall->scene_id = scene_id;
				playerSmall->Reset(player->x + (SOPHIA_BBOX_WIDTH / 3), player->y + 1);
			}
		}
		break;
		// reset position of sophia
	case DIK_E:
		if (Allow[SOPHIA] || Allow[JASON]) {
			Allow[JASON] = false;
			Allow[SOPHIA] = false;
			Allow[BIG_JASON] = true;
			playerBig->IsRender = true;
			playerBig->Reset(player->x + (SOPHIA_BBOX_WIDTH / 3), player->y + 1);
		}
		break;
	case DIK_1:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		DebugOut(L"scene_id:%d", player->scene_id);
		if (player->scene_id != 1) {
			Game::GetInstance()->SwitchScene(1);
			player->scene_id = 1;
		}
		SetPosition(67 * BIT, 1164);
		break;
	case DIK_2:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 2) {
			Game::GetInstance()->SwitchScene(2);
			player->scene_id = 2;
		}
		SetPosition(4 * BIT, 1164);
		break;
	case DIK_3:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 3) {
			Game::GetInstance()->SwitchScene(3);
			player->scene_id = 3;
		}
		SetPosition(590, 100);
		break;
	case DIK_4:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 4) {
			Game::GetInstance()->SwitchScene(4);
			player->scene_id = 4;
		}
		SetPosition(4 * BIT, 54 * BIT);
		break;
	case DIK_5:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 5) {
			Game::GetInstance()->SwitchScene(5);
			player->scene_id = 5;
		}
		SetPosition(36 * BIT, 36 * BIT);
		break;
	case DIK_6:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 6) {
			Game::GetInstance()->SwitchScene(6);
			player->scene_id = 6;
		}
		SetPosition(68 * BIT, 24 * BIT);
		break;
	case DIK_7:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 7) {
			Game::GetInstance()->SwitchScene(7);
			player->scene_id = 7;
		}
		SetPosition(100 * BIT, 24 * BIT);
		break;
	case DIK_8:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 8) {
			Game::GetInstance()->SwitchScene(8);
			player->scene_id = 8;
		}
		SetPosition(91 * BIT, 40 * BIT);
		break;
	case DIK_9:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 9) {
			Game::GetInstance()->SwitchScene(9);
			player->scene_id = 9;
		}
		SetPosition(68 * BIT, 56 * BIT);
		break;
	}
}

void Sophia::OnKeyUp(int key) {
	switch (key) {
	case DIK_SPACE:
		//vy = SOPHIA_GRAVITY * dt * 10;
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
				//player->y = player->y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
				player->RenderOneFrame = true;
				//CurAnimation->currentFrame = 2;
				vx = 0;
				vy = 0;
			}
		}
		break;
	case DIK_LEFT:
		if (IsUp) {
			if (!IsJumping) {
				ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
				//player->y = player->y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
				player->RenderOneFrame = true;
				//CurAnimation->currentFrame = 2;
				vx = 0;
				vy = 0;
			}
		}
		break;
	}
}

void Sophia::Reset(float x, float y) {
	nx = 1;
	IsRender = true;
	IsDead = false;
	SetPosition(x,y);
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}

