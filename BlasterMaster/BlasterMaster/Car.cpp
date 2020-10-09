
#include "Car.h"
#include "Goomba.h"
#include "Brick.h"
#include "Bullet.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
#include "PlayerDeadState.h"
#include "PlayerJumpingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"

CCar* CCar::_instance = NULL;

CCar::CCar() :CGameObject() {
	AdAnimation(400, STANDING_RIGHT);
	AdAnimation(401, STANDING_LEFT);
	AdAnimation(500, MOVING_RIGHT);
	AdAnimation(501, MOVING_LEFT);
	AdAnimation(400, JUMPING_RIGHT);
	AdAnimation(401, JUMPING_LEFT);
	AdAnimation(400, FALLING_RIGHT);
	AdAnimation(401, FALLING_LEFT);
    AdAnimation(510, UPWARD_RIGHT);
    AdAnimation(511, UPWARD_LEFT);
	AdAnimation(512, UP_RIGHT);
	AdAnimation(513, UP_LEFT);
	
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

		IsJumping = false;
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny == -1) vy = 0;
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

	CurAnimation->Render(x, y, alpha);

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
	if (nx > 0) {
		bullet->AdAnimation(800);
		bullet->SetPosition(x + CAR_BBOX_WIDTH, y + 7 / CAR_BBOX_HEIGHT);
		bullet->SetState(BULLET_STATE_MOVING_RIGHT);
	}
	else {
		bullet->AdAnimation(800);
		bullet->SetPosition(x, y + 7 / CAR_BBOX_HEIGHT);
		bullet->SetState(BULLET_STATE_MOVING_LEFT);
	}
	//bullet->AdAnimation(801);
	
	if (bullets.size() < 3) {
		bullets.push_back(bullet);
	}
}

void CCar::DeleteBullet() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->GetX() >= x + 150.0f || bullets[i]->GetX() <= x - 150.0f) {
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

void CCar::ChangeAnimation(PlayerState* newState) {
	delete state;
	state = newState;
	state->StateName = newState->StateName;
	CurAnimation = animations[newState->StateName];
}

void CCar::OnKeyDown(int key) {
	switch (key) {
	case DIK_SPACE:
		if (!IsJumping && allow[JUMPING])
		{
			if ((keyCode[DIK_RIGHT]))
			{
				vx = CAR_MOVING_SPEED;
				nx = 1;
				ChangeAnimation(new PlayerJumpingState());
			}
			else if ((keyCode[DIK_LEFT]))
			{
				vx = -CAR_MOVING_SPEED;
				nx = -1;
				ChangeAnimation(new PlayerJumpingState());
			}
			else
			{
				ChangeAnimation(new PlayerJumpingState());
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
	
}

void CCar::Revival() {
	SetPosition(5.0f, 60.0f);
	allow[JUMPING] = true;
	allow[MOVING] = true;
	ChangeAnimation(new PlayerStandingState());
}