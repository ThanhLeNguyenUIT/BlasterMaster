#include <algorithm>
#include <assert.h>


#include "BigJason.h"
#include "Game.h"
#include "Portal.h"
#include "Camera.h"
#include "Brick.h"
#include "Gate.h"
#include "Enemy.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"
#include "PlayerCrawlingState.h"
#include "PlayerDeadState.h"
#include "PlayerOpenState.h"

#include "BulletMovingState.h"

BigJason* BigJason::_instance = NULL;

BigJason::BigJason() {
	health = 8;
	IsUp = false;
	IsJumping = false;
	type = BIG_JASON;
}

BigJason::~BigJason() {

}

void BigJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<Enemy*>* coEnemy, vector<Item*>* coItem, vector<EnemyBullet*>* coBullet) {
	if (Allow[BIG_JASON]) {
		GameObject::Update(dt);

		// Simple fall down
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
		// create bullet when DIK_S
		if (IsFiring) {
			bullet = new PlayerBullet();
			bullet->type = BIG_JASON_BULLET;
			if (nx > 0) {
				bullet->SetPosition(x + BIG_JASON_BBOX_WIDTH / 3, y + BIG_JASON_BBOX_HEIGHT / 2);
				bullet->ChangeAnimation(BIG_JASON_BULLET_MOVING_RIGHT);
			}
			else if (nx < 0 ) {
				bullet->SetPosition(x + BIG_JASON_BBOX_WIDTH / 3, y + BIG_JASON_BBOX_HEIGHT / 2);
				bullet->ChangeAnimation(BIG_JASON_BULLET_MOVING_LEFT);
			}
			else if (ny > 0) {
				bullet->SetPosition(x + 7 / BIG_JASON_BBOX_WIDTH, y + 7 / BIG_JASON_BBOX_HEIGHT);
				bullet->ChangeAnimation(BIG_JASON_BULLET_MOVING_UP);
			}
			else if (ny < 0 ) {
				bullet->SetPosition(x + 7 / BIG_JASON_BBOX_WIDTH / 2, y + BIG_JASON_BBOX_HEIGHT / 2);
				bullet->ChangeAnimation(BIG_JASON_BULLET_MOVING_DOWN);
			}
		}
		// change state die if health = 0
		/*if (health == 0) {
			ChangeAnimation(new PlayerDeadState());
		}*/
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
					}
				}

				if (dynamic_cast<Gate*>(e->obj)) {
					Gate* g = dynamic_cast<Gate*>(e->obj);
					scene_gate = g->scene_id;
					Camera::GetInstance()->isInTransition = true;
					if (e->nx != 0) {
						x += dx;
						IsTouchGate = true;
						sceneHistory.push_back(scene_gate);
						if (scene_gate == 5 || scene_gate == 9 || scene_gate == 8) {
							IsChangeScene = true;
							Camera::GetInstance()->isInTransition = false;
						}
					}
					if (e->ny != 0) {
						y += dy;
						IsTouchGate = true;
						sceneHistory.push_back(scene_gate);
						if (scene_gate == 5 || scene_gate == 9 || scene_gate == 8) {
							IsChangeScene = true;
							Camera::GetInstance()->isInTransition = false;
						}
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

void BigJason::ChangeScene(int scene_gate) {
	scene_id = scene_gate;
	if (Allow[BIG_JASON]) {
		switch (scene_gate) {
		case 53:
			SetPosition(118 * BIT, 70 * BIT);
			break;
		case 40:
			if (sceneHistory.size() == 1) {
				SetPosition(5 * BIT, 7 * BIT);
			}
			else SetPosition(28 * BIT, 7 * BIT);
			break;
		case 41:
			SetPosition(35 * BIT, 7 * BIT);
			break;
		case 50:
			if (sceneHistory.size() == 1) {
				SetPosition(5 * BIT, 23 * BIT);
			}
			else SetPosition(28 * BIT, 39 * BIT);
			break;
		case 51:
			SetPosition(35 * BIT, 39 * BIT);
			break;
		case 10:
			SetPosition(87.5 * BIT, 71.5 * BIT);
			break;
		case 5:
		case 8:
		case 9:
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
			sceneHistory.clear();
			sceneHistory.push_back(11);
			break;
		case 11:
			if (sceneHistory[0] == 11 && sceneHistory.size() == 1) {
				SetPosition(8 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 12) {
				SetPosition(13 * BIT, 119 * BIT);
			}
			break;
		case 12:
			if (sceneHistory.rbegin()[1] == 11) {
				SetPosition(18 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 13) {
				SetPosition(29 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 21) {
				SetPosition(23 * BIT, 114 * BIT);
			}
			break;
		case 13:
			if (sceneHistory.rbegin()[1] == 12) {
				SetPosition(34 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 14) {
				SetPosition(45 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 20) {
				SetPosition(39 * BIT, 114 * BIT);
			}
			break;
		case 14:
			if (sceneHistory.rbegin()[1] == 13) {
				SetPosition(50 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 15) {
				SetPosition(61 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 19) {
				SetPosition(55 * BIT, 115 * BIT);
			}
			break;
		case 15:
			if (sceneHistory.rbegin()[1] == 14) {
				SetPosition(66 * BIT, 119 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 16) {
				SetPosition(77 * BIT, 119 * BIT);
			}
			break;
		case 16:
			if (sceneHistory.rbegin()[1] == 15) {
				SetPosition(82 * BIT, 119 * BIT);
			}
			break;
		case 17:
			if (sceneHistory.rbegin()[1] == 18) {
				SetPosition(82 * BIT, 103 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 28) {
				SetPosition(87 * BIT, 99 * BIT);
			}
			break;
		case 18:
			if (sceneHistory.rbegin()[1] == 19) {
				SetPosition(66 * BIT, 103 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 17) {
				SetPosition(77 * BIT, 103 * BIT);
			}
			break;
		case 19:
			if (sceneHistory.rbegin()[1] == 14) {
				SetPosition(55 * BIT, 106 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 18) {
				SetPosition(61 * BIT, 103 * BIT);
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
				SetPosition(18 * BIT, 103 * BIT);
			}
			break;
		case 22:
			if (sceneHistory.rbegin()[1] == 21) {
				SetPosition(13 * BIT, 103 * BIT);
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
				SetPosition(29 * BIT, 87 * BIT);
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
				SetPosition(45 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 24) {
				SetPosition(34 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 31) {
				SetPosition(39 * BIT, 83 * BIT);
			}
			break;
		case 26:
			if (sceneHistory.rbegin()[1] == 25) {
				SetPosition(50 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 27) {
				SetPosition(61 * BIT, 87 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 30) {
				SetPosition(55 * BIT, 83 * BIT);
			}
			break;
		case 27:
			if (sceneHistory.rbegin()[1] == 26) {
				SetPosition(66 * BIT, 87 * BIT);
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
				SetPosition(18 * BIT, 71 * BIT);
			}
			break;
		case 33:
			if (sceneHistory.rbegin()[1] == 32) {
				SetPosition(13 * BIT, 71 * BIT);
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
				SetPosition(13 * BIT, 55 * BIT);
			}
			break;
		case 35:
			if (sceneHistory.rbegin()[1] == 34) {
				SetPosition(18 * BIT, 55 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 36) {
				SetPosition(29 * BIT, 55 * BIT);
			}
			break;
		case 36:
			if (sceneHistory.rbegin()[1] == 35) {
				SetPosition(34 * BIT, 55 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 31) {
				SetPosition(39 * BIT, 58 * BIT);
			}
			else if (sceneHistory.rbegin()[1] == 37) {
				SetPosition(45 * BIT, 55 * BIT);
			}
			break;
		case 37:
			if (sceneHistory.rbegin()[1] == 36) {
				SetPosition(50 * BIT, 55 * BIT);
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
	LPANIMATION_SET animationSet = animation_sets->Get(type);
	CurAnimation = animationSet->Get(StateName);
}

void BigJason::Render() {

	int alpha = Camera::GetInstance()->isInTransition ? 0 : 255;
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
	case DIK_S:
		if (timeStartAttack == TIME_DEFAULT) {
			timeStartAttack = GetTickCount();
		}
		IsFiring = true;
		break;
	case DIK_RIGHT:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
		}
		break;
	case DIK_LEFT:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
		}
		break;
	case DIK_UP:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
			//nx = 0;
			//ny = 1;
		}
		break;
	case DIK_DOWN:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
			//nx = 0;
			//ny = -1;
		}
		break;
	}
}

void BigJason::OnKeyUp(int key) {
	switch (key) {
	case DIK_RIGHT:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
		}
		break;
	case DIK_LEFT:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
		}
		break;
	case DIK_UP:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchPortal = false;
			IsTouchGate = false;
			//nx = 0;
			//ny = 1;
		}
		break;
	case DIK_DOWN:
		if (Allow[BIG_JASON] && (IsTouchGate || IsTouchPortal)) {
			playerBig->ChangeScene(scene_gate);
			IsTouchGate = false;
			IsTouchPortal = false;
			//nx = 0;
			//ny = -1;
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