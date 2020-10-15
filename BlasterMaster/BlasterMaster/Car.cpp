
#include "Car.h"
#include "Goomba.h"
#include "Brick.h"
#include "Bullet.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerDeadState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"

CCar* CCar::_instance = NULL;

CCar::CCar() :CGameObject() {
	AdAnimation(101, STANDING_RIGHT);
	AdAnimation(102, STANDING_LEFT);
	AdAnimation(201, MOVING_RIGHT);
	AdAnimation(202, MOVING_LEFT);
	AdAnimation(401, JUMPING_RIGHT);
	AdAnimation(402, JUMPING_LEFT);
	AdAnimation(501, JUMPING_MOVING_RIGHT);
	AdAnimation(502, JUMPING_MOVING_LEFT);
	AdAnimation(601, FALLING_RIGHT);
	AdAnimation(602, FALLING_LEFT);
	AdAnimation(701, FALLING_MOVING_RIGHT);
	AdAnimation(702, FALLING_MOVING_LEFT);
    AdAnimation(801, UPWARD_RIGHT);
    AdAnimation(802, UPWARD_LEFT);
	AdAnimation(901, UPWARD_MOVING_RIGHT);
	AdAnimation(902, UPWARD_MOVING_LEFT);
	AdAnimation(801, UPWARD_JUMPING_RIGHT);
	AdAnimation(802, UPWARD_JUMPING_LEFT);
	AdAnimation(901, UPWARD_JUMPING_MOVING_RIGHT);
	AdAnimation(902, UPWARD_JUMPING_MOVING_LEFT);
	IsStop = true;
	tag = PLAYER;
}

CCar::~CCar() {

}

void CCar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	
	vy += CAR_GRAVITY*dt;
	
	state->Update();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(dt, coObjects);
	}
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->GetState() == BULLET_STATE_HIT) {
			bullets.erase(bullets.begin() + i);
		}
	}

	// turn off collision when die 
	
	CalcPotentialCollisions(coObjects, coEvents);
	


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

		if (nx != 0) vx = 0;
		if (ny == -1) {
			vy = 0;
			IsJumping = false;
		}
		if (ny == 1)
		{
			y += dy;
			IsJumping = true;
		}
		
		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						/*vy = -CAR_JUMP_DEFLECT_SPEED;*/
					}
				}
				/*else if (e->nx != 0)
				{
					SetState(CAR_STATE_DIE);
				}*/
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CCar::Render() {
	int alpha = 255;

	if (!IsUp) {
		if (state->StateName == STANDING_RIGHT)
		rev = false;
		CurAnimation->Render(x, y, alpha, idFrame, renderOneFrame);
	}
	else {
		rev = true;
		if (state->StateName == UPWARD_MOVING_RIGHT || state->StateName == UPWARD_MOVING_LEFT
			|| state->StateName == UPWARD_JUMPING_MOVING_RIGHT || state->StateName == UPWARD_JUMPING_MOVING_LEFT)
			rev = false;
		CurAnimation->Render(x, y, alpha, idFrame, renderOneFrame, rev);
	}
	
	RenderBoundingBox();

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}
}

//void CCar::SetState(int state) {
//	CGameObject::SetState(state);
//	switch (state) {
//	case CAR_STATE_MOVING_RIGHT:
//		vx = CAR_MOVING_SPEED;
//		nx = 1;
//		break;
//	case CAR_STATE_MOVING_LEFT:
//		vx = -CAR_MOVING_SPEED;
//		nx = -1;
//		break;
//	case CAR_STATE_JUMP_RIGHT:
//		if (y < 100) {
//			vx = CAR_MOVING_SPEED;
//			nx = 1;
//		}
//		break;
//	case CAR_STATE_JUMP_LEFT:
//		if (y < 100) {
//			vx = -CAR_MOVING_SPEED;
//			nx = -1;
//		}
//		break;
//	case CAR_STATE_JUMP:
//		vy = -CAR_JUMP_SPEED_Y;
//	case CAR_STATE_IDLE:
//		vx = 0;
//		break;
//	case CAR_STATE_DIE:
//		vy = -CAR_DIE_DEFLECT_SPEED;
//		break;
//	case CAR_STATE_FIRE:
//		isFiring = true;
//		AddBullet();
//		DeleteBullet();
//		isFiring = false;
//		break;
//	case CAR_STATE_NOT_FIRE:
//		isFiring = false;
//		break;
//	}
//}

void CCar::AddBullet() {
	bullet = new CBullet;
	if (!IsUp) {
		if (nx > 0) {
			bullet->AdAnimation(2004);
			bullet->SetPosition(x + CAR_BBOX_WIDTH, y + 7 / CAR_BBOX_HEIGHT);
			bullet->SetState(BULLET_STATE_MOVING_RIGHT);
		}
		else {
			bullet->AdAnimation(2005);
			bullet->SetPosition(x, y + 7 / CAR_BBOX_HEIGHT);
			bullet->SetState(BULLET_STATE_MOVING_LEFT);
		}
	}
	else {
		if (nx != 0) {
			bullet->AdAnimation(2006);
			bullet->SetPosition(x + CAR_BBOX_WIDTH/3, y);
			bullet->SetState(BULLET_STATE_MOVING_UP);
		}
	}

	if (bullets.size() < 3) {
		bullets.push_back(bullet);
	}
}

void CCar::DeleteBullet() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->GetX() >= x + 150.0f || bullets[i]->GetX() <= x - 150.0f) {
			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i]->GetY() <= y - 100.0f) {
			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i]->GetState() == BULLET_STATE_HIT) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

void CCar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (stateBoundingBox == CAR_BOUNDING_BOX) {
		right = x + CAR_BBOX_WIDTH;
		bottom = y + CAR_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == CAR_UP_BOUNDING_BOX) {
		right = x + CAR_UP_BBOX_WIDTH;
		bottom = y + CAR_UP_BBOX_HEIGHT;
	}
	
}

CCar* CCar::GetInstance() {
	if (_instance == NULL) {
		_instance = new CCar();
	}
	return _instance;
}


void CCar::ChangeAnimation(PlayerState* newState, int stateId) {
	delete state;
	if (stateId == 1) {
		renderOneFrame = false;
		idFrame = CurAnimation->currentFrame * 2;
	}
	else if (stateId == 2) {
		renderOneFrame = true;
		if (CurAnimation->currentFrame == 0 || CurAnimation->currentFrame == 7) {
			idFrame = 0;
		}
		else if (CurAnimation->currentFrame == 1 || CurAnimation->currentFrame == 2) {
			idFrame = 1;
		}
		else if (CurAnimation->currentFrame == 3 || CurAnimation->currentFrame == 4) {
			idFrame = 2;
		}
		else if (CurAnimation->currentFrame == 5 || CurAnimation->currentFrame == 6) {
			idFrame = 3;
		}
	}
	else if (stateId == 3) {
		idFrame = CurAnimation->currentFrame;
	}

	state = newState;

	CurAnimation = animations[newState->StateName];

}

void CCar::OnKeyDown(int key) {
	switch (key) {
	case DIK_SPACE:
		if (!IsUp) {
			if (!IsJumping)
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = CAR_MOVING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerJumpingMovingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -CAR_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerJumpingMovingState());
				}
				else
				{
					ChangeAnimation(new PlayerJumpingState(),3);
				}
			}
		}
		else {
			if (!IsJumping)
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = CAR_MOVING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -CAR_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState());
				}
				else
				{
					ChangeAnimation(new PlayerUpwardJumpingState());
				}
			}
		}
		break;
	case DIK_S:
		IsFiring = true;
		AddBullet();
		DeleteBullet();
		IsFiring = false;
		break;
	}
}

void CCar::OnKeyUp(int key) {
	switch (key) {
	case DIK_UPARROW:
		IsUp = false;
		CurAnimation->currentFrame = -1;
		y = y + (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT);
		ChangeAnimation(new PlayerStandingState());
		break;
	/*case DIK_RIGHT:
		if (IsUp) 
			y = y + (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT);
		break;
	case DIK_LEFT:
		if (IsUp)
			y = y + (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT);
		break;*/
	}
}

void CCar::Revival() {
	SetPosition(5.0f, 60.0f);
	allow[JUMPING] = true;
	allow[MOVING] = true;
	ChangeAnimation(new PlayerStandingState());
}