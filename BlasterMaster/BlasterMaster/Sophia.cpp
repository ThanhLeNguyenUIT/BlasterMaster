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
#include "Enemy.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerOpenState.h"
#include "PlayerJumpTurningState.h"
#include "PlayerUpperState.h"
#include "PlayerDeadState.h"


Sophia* Sophia::_instance = NULL;

Sophia::Sophia(){
	health = 8;
	scene_id = 1;
	old_scene_id = 0;
	IsUp = false;
	type = SOPHIA;
	Allow[SOPHIA] = true;
	Allow[JASON] = false;
}

Sophia::~Sophia() {

}

void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* staticObject, vector<Enemy*>* coEnemy, vector<Item*>* coItem, vector<EnemyBullet*>* coBullet) {
	// Calculate dx, dy
	if (Allow[SOPHIA]) {
	
		GameObject::Update(dt);
		// Simple fall down
		vy += SOPHIA_GRAVITY * dt;
		// Update state
		state->Update();
		// Update count
		if (IsUp) {
			if (CurAnimation->IsFinish)
			{
				if (count < 3)
					count++;
			}
		}
		vector<LPCOLLISIONEVENT> coStaticObjects;
		vector<LPCOLLISIONEVENT> coStaticObjectsResult;
		coStaticObjects.clear();

		// turn off collision when die 
		if (StateName != SOPHIA_DEAD) {
			CalcPotentialCollisions(staticObject, coStaticObjects);
		}
		
		Fire();

		// change state die if health = 0
		if (health == 0) {
			IsDamaged = false;
			color = NULL;
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
		if (coStaticObjects.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coStaticObjects, coStaticObjectsResult, min_tx, min_ty, nx, ny);
			// block 
			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.1f;
			
			// Collision logic with Enemies
			for (UINT i = 0; i < coStaticObjectsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coStaticObjectsResult[i];
				if (dynamic_cast<Brick*>(e->obj)) {
					
					if (e->nx != 0) vx = 0;
					if (e->ny == -1)
					{
						if (IsJumping) {
							vx = 0;
							//RenderOneFrame = true;
						}
						vy = 0;
						IsJumping = false;
					}
					else if (e->ny == 1)
					{
  						vy = 0;
					}
				}
				if (dynamic_cast<DamageBrick*>(e->obj)) {
					if (e->nx != 0) vx = 0;
					if (e->ny != 0)
					{
						vy = 0;
						// damage
						if (timeDamaged == TIME_DEFAULT) {
							timeDamaged = GetTickCount();
						}
						IsJumping = false;
						if (GetTickCount() - timeDamaged >= 600) {
							//health = health - 1;
							timeDamaged = GetTickCount();
						}
					}
				}
				if (dynamic_cast<Portal*>(e->obj))
				{
					Portal* p = dynamic_cast<Portal*>(e->obj);
					IsTouchPortal = true;
					IsChangeScene = true;
					old_scene_id = scene_id;
					scene_id = p->scene_id;
					
					if ((scene_id == 1) || (scene_id == 4)) {
						Camera::GetInstance()->isChangingMap = false;
					}
					else {
						Camera::GetInstance()->isChangingMap = true;
						IsRender = false;
					}
					ChangeAnimation(new PlayerStandingState());
				}
				if (dynamic_cast<Stair*>(e->obj))
				{
					if (e->nx != 0) x += dx;
					Stair* p = dynamic_cast<Stair*>(e->obj);
				}	
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coStaticObjects.size(); i++) delete coStaticObjects[i];


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
					health = health - 1;
					timeDamaged = TIME_DEFAULT;
				}
			}
		}
		// Collison with enemy bullet
		for (int i = 0; i < coBullet->size(); i++) {
			if (CollisionWithObject(coBullet->at(i))) {
				if (coBullet->at(i)->GetStateObject() != BULLET_SMALL_HIT) {
					IsDamaged = true;
					health = health - 1;
				}
				coBullet->at(i)->ChangeAnimation(BULLET_SMALL_HIT);
			}
		}
		// Collison with item 
		for (int i = 0; i < coItem->size(); i++) {
			if (CollisionWithObject(coItem->at(i))) {
				coItem->at(i)->isDead = true;
				if (health < 8)
					health = health + 1;
			}
		}

	}
}

void Sophia::Fire() {
	// time fire bullet
	if (GetTickCount() - timeStartAttack >= TIME_FIRING) {
		timeStartAttack = TIME_DEFAULT;
		IsFiring = false;
	}
	// create bullet when DIK_S
	if (IsFiring) {
		bullet = new PlayerBullet();
		bullet->type = BULLET_SMALL;
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
}

void Sophia::ChangeScene() {
	if (IsTouchPortal && Allow[SOPHIA]) {
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
				SetPosition(122.6 * BIT, 72.6 * BIT);
			}
			break;
		case 4:
			ChangeAnimation(new PlayerStandingState());
			SetSpeed(0, 0);
			if (old_scene_id == 5) {
				player->nx = 1;
				SetPosition(3.6 * BIT, 6 * BIT);
			}
			else if (old_scene_id == 3) {
				player->nx = 1;
				SetPosition(3.6 * BIT, 54 * BIT);
			}
			break;
		case 2:
			//Set
			if (old_scene_id == 1)
			{
				ChangeAnimation(new PlayerStandingState());
				SetSpeed(0, 0);
				SetPosition(3.6 * BIT, 72.6 * BIT);
			}
			if (old_scene_id == 3) {
				ChangeAnimation(new PlayerStandingState());
				nx = -1;
				SetPosition(27.6 * BIT, 8.6 * BIT);

			}
			else if (old_scene_id == 5) {
				player->nx = -1;
				SetPosition(27.6 * BIT, 72.6 * BIT);
			}
			break;
		case 3:
			if (old_scene_id == 2) {
				player->nx = 1;
				SetPosition(35.6 * BIT, 8.6 * BIT);
			}
			else if (old_scene_id == 4) {
				player->nx = -1;
				SetPosition(59.6 * BIT, 8.6 * BIT);
			}
			break;
		case 5:
			if (old_scene_id == 6) {
				player->nx = -1;
				SetPosition(59.2 * BIT, 24.6 * BIT);
			}
			else if (old_scene_id == 4) {
				player->nx = -1;
				SetPosition(59.2 * BIT, 88.6 * BIT);
			}
			else if (old_scene_id == 9) {
				player->nx = -1;
				SetPosition(59.2 * BIT, 56.6 * BIT);
			}
			break;
		case 6:
			if (old_scene_id == 5) {
				nx = 1;
				SetPosition(67.2 * BIT, 24.6 * BIT);
			}
			else if (old_scene_id == 7) {
				player->nx = -1;
				SetPosition(91.2 * BIT, 24.6 * BIT);
			}
			break;
		case 7:
			if (old_scene_id == 6) {
				nx = 1;
				SetPosition(99.5 * BIT, 24.6 * BIT);
			}
			else if (old_scene_id == 8) {
				nx = 1;
				SetPosition(99.5 * BIT, 40.6 * BIT);
			}
			break;
		case 8:
			nx = -1;
			SetPosition(91.2 * BIT, 40.6 * BIT);
			break;
		case 9:
			nx = 1;
			SetPosition(67.2 * BIT, 56.6 * BIT);
			break;

		}
		IsTouchPortal = false;
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
	CheckState(stateChange);
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	state = newState;
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(StateName);
}

void Sophia::Render() {
	
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
		if (!RenderBack) {
			if(!IsDamaged)
				CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame);
			else 
				CurAnimation->Render(x, y, alpha, idFrame, RenderOneFrame, color);
		}
		else {
			CurAnimation->RenderBack(x, y, alpha, idFrame, RenderOneFrame);
		}
		//RenderBoundingBox();
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
	ChangeScene();
	ChangeAnimation(new PlayerStandingState());
	SetSpeed(0, 0);
}

