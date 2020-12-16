#include "PlayerJumpingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpTurningState.h"
#include "PlayerUpperState.h"

PlayerJumpingState::PlayerJumpingState() {

	if (Allow[SOPHIA]) {
		player->RenderOneFrame = true;
		if(!player->IsJumping)
			player->vy = -SOPHIA_JUMPING_SPEED_Y;
		
		if (player->nx > 0) {
			player->StateName = SOPHIA_JUMPING_RIGHT;
		}
		else {
			player->StateName = SOPHIA_JUMPING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	else if (Allow[JASON]) {
		if(!playerSmall->IsJumping)
			playerSmall->vy = -JASON_JUMP_SPEED_Y;
		if (playerSmall->nx > 0) {
			playerSmall->StateName = JASON_JUMPING_RIGHT;
		}
		else {
			playerSmall->StateName = JASON_JUMPING_LEFT;
		}
		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerJumpingState::~PlayerJumpingState() {

}

void PlayerJumpingState::Update() {
	if (Allow[SOPHIA]) {
		if (player->vy > 0) {
			player->ChangeAnimation(new PlayerFallingState(), NORMAL);
			return;
		}
	}
	else if (Allow[JASON]) {
		if (playerSmall->vy > 0) {
			playerSmall->ChangeAnimation(new PlayerFallingState());
			return;
		}
	}
	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT] && keyCode[DIK_UP]) {
		if (Allow[SOPHIA])
			player->ChangeAnimation(new PlayerUpperState(), NORMAL);
	}
	else if (keyCode[DIK_LEFT] && keyCode[DIK_UP]) {
		if (Allow[SOPHIA])
			player->ChangeAnimation(new PlayerUpperState(), NORMAL);
	}
	else if (keyCode[DIK_RIGHT]) {
		if (Allow[SOPHIA]) {
			if (player->nx > 0) {
				player->nx = 1;
				player->vx = SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerJumpingState());
				player->RenderOneFrame = false;
			}
			else {
				player->vx = -SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerJumpTurningState());
				player->CurAnimation->currentFrame = -1;
				player->CurAnimation->isLastFrame = false;
			}
		}
		else if (Allow[JASON]) {
			playerSmall->nx = 1;
			playerSmall->vx = JASON_MOVING_SPEED;
			playerSmall->ChangeAnimation(new PlayerJumpingState());
		}
	}
	else if (keyCode[DIK_LEFT]) {
		if (Allow[SOPHIA]) {
			if (player->nx < 0) {
				player->nx = -1;
				player->vx = -SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerJumpingState());
				player->RenderOneFrame = false;
			}
			else {
				player->vx = SOPHIA_MOVING_SPEED;
				player->ChangeAnimation(new PlayerJumpTurningState());
				player->CurAnimation->currentFrame = -1;
				player->CurAnimation->isLastFrame = false;
			}
		}
		else if (Allow[JASON]) {
			playerSmall->nx = -1;
			playerSmall->vx = -JASON_MOVING_SPEED;
			playerSmall->ChangeAnimation(new PlayerJumpingState());
		}
	}
	if (keyCode[DIK_UP]) {
		if (Allow[SOPHIA])
			player->ChangeAnimation(new PlayerUpperState(), NORMAL);
	}
}

