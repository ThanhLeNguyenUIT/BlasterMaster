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
#include "PlayerUpperState.h"
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
	if (Game::GetInstance()->loadDone) {
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
				//vy = 999;
				// Collision logic with Enemies
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (e->obj != NULL) {
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
							}
						}

						if (dynamic_cast<Portal*>(e->obj))
						{
							old_scene_id = scene_id;
							Portal* p = dynamic_cast<Portal*>(e->obj);
							IsTouchPortal = true;
							scene_id = p->scene_id;
							if ((scene_id == 1) || (scene_id == 4)) {
								Camera::GetInstance()->isChangingMap = false;
							}
							else {
								Camera::GetInstance()->isChangingMap = true;
							}
							ChangeAnimation(new PlayerStandingState());
							Game::GetInstance()->SwitchScene(p->GetSceneId());
						}
						delete coEventsResult[i];
					}
				}
			}
			// clean up collision events
			//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
}

void Sophia::ChangeScene(DWORD dt) {
		/*switch (scene_id) {
		case 1:
			IsTouchPortal = false;
			if (nx > 0) {
				SetPosition(123 * BIT, 72 * BIT);
			}
			break;
		case 2:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				if (old_scene_id == 3) {
					SetPosition(27 * BIT, 8 * BIT);
				}
				else if (old_scene_id == 5) {
					SetPosition(27 * BIT, 72 * BIT);
				}
				else if (old_scene_id == 1) {
					SetPosition(5 * BIT, 72 * BIT);
				}
			}
			break;
		case 3:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				if (old_scene_id == 4)SetPosition(59 * BIT, 8 * BIT);
				else if (old_scene_id == 2) SetPosition(37 * BIT, 8 * BIT);
			}
			break;
		case 4:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				if (old_scene_id == 5) SetPosition(5 * BIT, 6 * BIT);
				else if (old_scene_id == 3) SetPosition(5 * BIT, 54 * BIT);
			}
			break;
		case 5:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				if (old_scene_id == 6) SetPosition(58 * BIT, 24 * BIT);
				else if (old_scene_id == 4) SetPosition(59 * BIT, 88 * BIT);
				else if (old_scene_id == 9) SetPosition(59 * BIT, 56 * BIT);
			}
			break;
		case 6:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				if (old_scene_id == 5) SetPosition(68 * BIT, 24 * BIT);
				else if (old_scene_id == 7) SetPosition(91 * BIT, 24 * BIT);
			}
			break;
		case 7:
			ChangeAnimation(new PlayerStandingState());
			IsTouchPortal = false;
			if (nx > 0) {
				if (old_scene_id == 6) SetPosition(100 * BIT, 24 * BIT);
				else if (old_scene_id == 8) SetPosition(100 * BIT, 40 * BIT);
			}
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
		}*/
	//}

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
	if (!IsTouchPortal && IsRender) {
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
	RenderBoundingBox();
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
		top = y + SOPHIA_OPEN_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT;
		right = x + SOPHIA_BBOX_WIDTH;
		bottom = top + SOPHIA_BBOX_HEIGHT;
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
				vy = 0;
				Allow[SOPHIA] = false;
				Allow[JASON] = true; // allow jason to get out of car
				playerSmall->IsRender = true;
				playerSmall->Reset(player->x + (SOPHIA_BBOX_WIDTH / 3), player->y + 1);
			}
		}
		break;
		// reset position of sophia
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
		IsTouchPortal = false;
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
		IsTouchPortal = false;
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
		IsTouchPortal = false;
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
		IsTouchPortal = false;
		break;
	case DIK_5:
		nx = 1;
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (player->scene_id != 5) {
			Game::GetInstance()->SwitchScene(5);
			player->scene_id = 5;
		}
		SetPosition(59 * BIT, 88 * BIT);
		IsTouchPortal = false;
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
		IsTouchPortal = false;
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
		IsTouchPortal = false;
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
		IsTouchPortal = false;
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
		IsTouchPortal = false;
		break;
	}

}

void Sophia::OnKeyUp(int key) {
	switch (key) {
	case DIK_SPACE:
		vy = SOPHIA_GRAVITY * dt * 10;
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
		right = true;
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
		if (!right) {
			if (IsUp) {
				if (!IsJumping) {
					ChangeAnimation(new PlayerUpwardMovingState(), NORMAL);
					RenderOneFrame = true;
					vx = 0;
					vy = 0;
				}
			}
		}
		break;
	}
}

void Sophia::Reset(float x, float y) {
	switch (scene_id)
	{
	case 1:
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (old_scene_id == 0) {
			nx = 1;
			SetPosition(x, y);
		}
		else if (old_scene_id == 2) {
			nx = -1;
			SetPosition(122*BIT,72*BIT);
		}
		break;
	case 4:
		ChangeAnimation(new PlayerStandingState());
		SetSpeed(0, 0);
		if (old_scene_id == 5) {
			player->nx = 1;
			SetPosition(5 * BIT, 6 * BIT);
		}
		else if (old_scene_id == 3) {
			player->nx = 1;
			SetPosition(5 * BIT, 54 * BIT);
		}
		break;
	case 2:
		//Set
		if (old_scene_id == 1)
		{
			ChangeAnimation(new PlayerStandingState());
			SetSpeed(0, 0);
			SetPosition(4 * BIT, 72 * BIT);
			//player->IsTouchPortal = false;
		}
		if (old_scene_id == 3) {
			ChangeAnimation(new PlayerStandingState());
			nx = -1;
			SetPosition(26*BIT,8*BIT);

		}
		else if (old_scene_id == 5) {
			player->nx = -1;
			//ChangeAnimation(new PlayerStandingState());
			SetPosition(27 * BIT, 72 * BIT);
		}	
		break;
	case 3:
		if (old_scene_id == 2) {
			player->nx = 1;
			SetPosition(36*BIT, 8*BIT);
		}
		else if (old_scene_id == 4){
			player->nx = -1;
			SetPosition(59*BIT,8*BIT);
		}
		break;
	case 5:
		if (old_scene_id == 6) {
			player->nx = -1;
			SetPosition(58 * BIT, 24 * BIT);
		}
		else if (old_scene_id == 4) {
			player->nx = -1;
			SetPosition(59 * BIT, 88 * BIT);
		}
		else if (old_scene_id == 9) {
			player->nx = -1;
			SetPosition(59 * BIT, 56 * BIT);
		}
		break;
	case 6:
		if (old_scene_id == 5) {
			nx = 1;
			SetPosition(68 * BIT, 24 * BIT);
		}
		else if (old_scene_id == 7) {
			player->nx = -1;
			SetPosition(91 * BIT, 24 * BIT);
		}
		break;
	case 7:
		if (old_scene_id == 6) {
			nx = 1;
			SetPosition(100 * BIT, 24 * BIT);
		}
		else if (old_scene_id == 8) {
			nx = 1;
			SetPosition(100 * BIT, 40 * BIT);
		}
		break;
	case 8:
		nx = -1;
		SetPosition(91 * BIT, 40 * BIT);
		break;
	case 9:
		nx = 1;
		SetPosition(68 * BIT, 56 * BIT);
		break;

	}
	player->IsTouchPortal = false;
}
