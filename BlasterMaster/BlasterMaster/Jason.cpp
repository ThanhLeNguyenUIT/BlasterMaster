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
#include "Sound.h"

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
	health = 8;
	IsUp = false;
	IsJumping = false;
	type = JASON;
}

Jason::~Jason() {

}

void Jason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*>* coEnemy, vector<Item*>* coItem, vector<EnemyBullet*>* coBullet) {
	if (Allow[JASON]) {
		GameObject::Update(dt);

		// Simple fall down
		if(!IsTouchStair)
			vy += JASON_GRAVITY * dt;
		state->Update();
		
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		// update when touch stair
		if (IsTouchStair && y <= 25 * BIT) {
			ChangeAnimation(new PlayerStandingState());
			IsTouchStair = false;
		}
		// turn off collision when die 

		CalcPotentialCollisions(coObjects, coEvents);

		// time fire bullet
		if (GetTickCount() - timeStartAttack >= TIME_FIRING) {
			timeStartAttack = TIME_DEFAULT;
			IsFiring = false;
		}
		// create bullet when firing
		if (IsFiring) {
			bullet = new PlayerBullet();
			bullet->type = JASON_BULLET_SMALL;
			if (nx > 0) {
				bullet->SetPosition(x + JASON_BBOX_WIDTH / 4, y + JASON_BBOX_HEIGHT / 3);
				bullet->ChangeAnimation(JASON_BULLET_SMALL_MOVING);
			}
			else {
				bullet->SetPosition(x + JASON_BBOX_WIDTH / 4, y + JASON_BBOX_HEIGHT / 3);
				bullet->ChangeAnimation(JASON_BULLET_SMALL_MOVING);
			}
		}

		// change state die if health = 0
		if (health == 0) {
			ChangeAnimation(new PlayerDeadState());
		}
		if (IsDamaged) {
			if (timeDamaged == TIME_DEFAULT) {
				timeDamaged = GetTickCount();
			}
			if (GetTickCount() - timeDamaged >= 600) {
				IsDamaged = false;
				timeDamaged = TIME_DEFAULT;
			}
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
					//if (e->nx != 0) x += dx;
					Portal* p = dynamic_cast<Portal*>(e->obj);
					IsTouchPortal = true;
					scene_id = p->scene_id;
					Game::GetInstance()->SwitchScene(p->GetSceneId());
					ChangeScene();
				}

				if (dynamic_cast<Stair*>(e->obj))
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

			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		
		// Collision with enemy
		for (int i = 0; i < coEnemy->size(); i++) {
			if (CollisionWithObject(coEnemy->at(i))) {

				if (coEnemy->at(i)->type == ORB2 || coEnemy->at(i)->type == MINE) {
					coEnemy->at(i)->health = 0;
				}
				//isDamaged
				IsDamaged = true;
				// damage
				if (timeDamaged == TIME_DEFAULT) {
					timeDamaged = GetTickCount();
				}
				if (GetTickCount() - timeDamaged >= 600) {
					sound->Play(GSOUND::S_HEALTH, false);
					health = health - 1;
					timeDamaged = TIME_DEFAULT;
				}
			}
		}
		// Collison with enemy bullet
		for (int i = 0; i < coBullet->size(); i++) {
			if (CollisionWithObject(coBullet->at(i))) {
				if (coBullet->at(i)->GetStateObject() != BULLET_SMALL_HIT) {
					sound->Play(GSOUND::S_HEALTH, false);
					IsDamaged = true;
					health = health - 1;
				}
				coBullet->at(i)->ChangeAnimation(BULLET_SMALL_HIT);
			}
		}
		// Collison with item 
		for (int i = 0; i < coItem->size(); i++) {
			if (CollisionWithObject(coItem->at(i))) {
				sound->Play(GSOUND::S_ITEM, false);
				coItem->at(i)->isDead = true;
				if (health < 8)
					health = health + 1;
			}
		}
	}
}

void Jason::ChangeScene() {

	if (IsTouchPortal && Allow[JASON]) {
		switch (scene_id) {
		case 1:
			ChangeAnimation(new PlayerStandingState());
			//SetSpeed(0, 0);
			if (old_scene_id == 0) {
				nx = 1;
				SetPosition(x, y);
			}
			else if (old_scene_id == 2) {
				nx = -1;
				SetPosition(122 * BIT, 72.6 * BIT);
			}
			break;
		case 4:
			ChangeAnimation(new PlayerStandingState());
			SetSpeed(0, 0);
			if (old_scene_id == 5) {
				nx = 1;
				SetPosition(4 * BIT, 6.6 * BIT);
			}
			else if (old_scene_id == 3) {
				nx = 1;
				SetPosition(4 * BIT, 54.6 * BIT);
			}
			break;
		case 2:
			//Set
			if (old_scene_id == 1)
			{
				ChangeAnimation(new PlayerStandingState());
				SetPosition(4 * BIT, 72.6 * BIT);
			}
			if (old_scene_id == 3) {
				ChangeAnimation(new PlayerStandingState());
				nx = -1;
				SetPosition(28 * BIT, 8.6 * BIT);

			}
			else if (old_scene_id == 5) {
				nx = -1;
				SetPosition(27 * BIT, 72 * BIT);
			}
			break;
		case 3:
			if (old_scene_id == 2) {
				nx = 1;
				SetPosition(36 * BIT, 8 * BIT);
			}
			else if (old_scene_id == 4) {
				nx = -1;
				SetPosition(59 * BIT, 8 * BIT);
			}
			break;
		case 5:
			if (old_scene_id == 6) {
				nx = -1;
				SetPosition(58 * BIT, 24 * BIT);
			}
			else if (old_scene_id == 4) {
				nx = -1;
				SetPosition(59 * BIT, 88 * BIT);
			}
			else if (old_scene_id == 9) {
				nx = -1;
				SetPosition(59 * BIT, 56 * BIT);
			}
			break;
		case 6:
			if (old_scene_id == 5) {
				nx = 1;
				SetPosition(68 * BIT, 24 * BIT);
			}
			else if (old_scene_id == 7) {
				nx = -1;
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
		IsTouchPortal = false;
	}
}

void Jason::ChangeAnimation(PlayerState* newState, int stateChange) {
	delete state;
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(StateName);
}

void Jason::Render() {
	int alpha = 255;
	D3DCOLOR colorOrange = D3DCOLOR_ARGB(alpha, 248, 120, 88);
	D3DCOLOR colorGreen = D3DCOLOR_ARGB(alpha, 0, 157, 64);
	D3DCOLOR colorGrey = D3DCOLOR_ARGB(alpha, 188, 186, 182);

	if (IsDamaged) {
		if (countColor == 0) {
			color = colorOrange;
			countColor++;
		}
		else if (countColor == 1) {
			color = colorGreen;
			countColor++;
		}
		else {
			color = colorGrey;
			countColor = 0;
		}
	}

	if (IsRender && !IsTouchPortal) {
		if (!IsDamaged)
			CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
		else
			CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame, color);
		//RenderBoundingBox();
	}
}

void Jason::GetBoundingBox(float& left, float& top, float& right, float& bottom){
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
		sound->Stop(GSOUND::S_JUMP);
		sound->Play(GSOUND::S_JUMP, false);
		IsTouchStair = false;
		ChangeAnimation(new PlayerJumpingState());
		playerSmall->IsJumping = true;
		break;
	case DIK_3:
		SetPosition(565, 112);
		break;
	case DIK_Q: // get on the car
		if (Allow[JASON]){
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
		sound->Play(GSOUND::S_BULLET_SOPHIA, false);
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


