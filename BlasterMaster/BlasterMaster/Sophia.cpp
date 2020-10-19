#include <algorithm>
#include <assert.h>

#include "Sophia.h"
#include "Game.h"

#include "PlayerState.h"
#include "PlayerFallingState.h"
//#include "PlayerDeadState.h"
#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
//#include "PlayerUpwardJumpingState.h"
//#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerStandingState.h"

Sophia* Sophia::_instance = NULL;

Sophia::Sophia() :GameObject() {
	IsStop = true;
	//ChangeAnimation(new PlayerStandingState());
	tag = PLAYER;
}

Sophia::~Sophia() {

}

void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	// Calculate dx, dy 
	GameObject::Update(dt);

	// Simple fall down

	vy += SOPHIA_GRAVITY * dt;

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
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		Goomba* goomba = dynamic_cast<Goomba*>(e->obj);

		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny < 0)
		//		{
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				/*vy = -Sophia_JUMP_DEFLECT_SPEED;*/
		//			}
		//		}
		//		/*else if (e->nx != 0)
		//		{
		//			SetState(Sophia_STATE_DIE);
		//		}*/
		//	}
		//}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Sophia::ChangeAnimation(PlayerState* newState, int stateId) {
	delete state;
	//AnimationSets* animation_sets = AnimationSets::GetInstance();
	/*if (stateId == 1) {
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
	}*/

	state = newState;
	
	//CurAnimationSet = animation_sets->Get(SOPHIA_ANIMATIONS_SET);
}

void Sophia::Render() {
	int alpha = 255;
	animation_set->at(state->StateName)->Render(x, y, alpha);
	RenderBoundingBox();

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Render();
	}
}

void Sophia::AddBullet() {
	bullet = new Bullet();
	AnimationSets* animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(SOPHIA_BULLET_ANIMATION_SET);
	if (!IsUp) {
		if (nx > 0) {

			bullet->animation_set = ani_set;
			bullet->animation_set->at(SOPHIA_BULLET_SMALL_ANI_RIGHT);
			bullet->SetPosition(x + SOPHIA_BBOX_WIDTH, y + 7 / SOPHIA_BBOX_HEIGHT);
			bullet->SetState(BULLET_STATE_MOVING_RIGHT);
		}
		else {
			bullet->animation_set = ani_set;
			bullet->animation_set->at(SOPHIA_BULLET_SMALL_ANI_LEFT);
			bullet->SetPosition(x, y + 7 / SOPHIA_BBOX_HEIGHT);
			bullet->SetState(BULLET_STATE_MOVING_LEFT);
		}
	}
	else {
		if (nx != 0) {
			bullet->animation_set = ani_set;
			bullet->animation_set->at(SOPHIA_BULLET_SMALL_ANI_UP);
			bullet->SetPosition(x + SOPHIA_BBOX_WIDTH / 3, y);
			bullet->SetState(BULLET_STATE_MOVING_UP);
		}
	}

	if (bullets.size() < 3) {
		bullets.push_back(bullet);
	}
}

void Sophia::DeleteBullet() {
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

void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (stateBoundingBox == SOPHIA_BOUNDING_BOX) {
		right = x + SOPHIA_BBOX_WIDTH;
		bottom = y + SOPHIA_BBOX_HEIGHT;
	}
	else if (stateBoundingBox == SOPHIA_UP_BOUNDING_BOX) {
		right = x + SOPHIA_UP_BBOX_WIDTH;
		bottom = y + SOPHIA_UP_BBOX_HEIGHT;
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
		if (!IsUp) {
			if (!IsJumping)
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = SOPHIA_MOVING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerJumpingMovingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -SOPHIA_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerJumpingMovingState());
				}
				else
				{
					ChangeAnimation(new PlayerJumpingState());
				}
			}
		}
		/*else {
			if (!IsJumping)
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = SOPHIA_MOVING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -SOPHIA_MOVING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerUpwardJumpingMovingState());
				}
				else
				{
					ChangeAnimation(new PlayerUpwardJumpingState());
				}
			}
		}*/
		break;
	case DIK_S:
		IsFiring = true;
		AddBullet();
		DeleteBullet();
		IsFiring = false;
		break;
	case DIK_A:
		Reset();
	}
}

void Sophia::OnKeyUp(int key) {
	switch (key) {
	case DIK_UPARROW:
		IsUp = false;
		CurAnimationSet->at(state->StateName)->currentFrame = -1;
		y = y + (SOPHIA_UP_BBOX_HEIGHT - SOPHIA_BBOX_HEIGHT);
		ChangeAnimation(new PlayerStandingState());
		break;
	}
}

void Sophia::Reset() {
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
	ChangeAnimation(new PlayerStandingState());
}