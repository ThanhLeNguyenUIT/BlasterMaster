#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerUpwardState.h"

PlayerJumpingState::PlayerJumpingState() {

	if (player->allow[SOPHIA]) {
		player->renderOneFrame = true;
		player->vy = -SOPHIA_JUMPING_SPEED_Y;
		
		if (player->nx > 0) {
			StateName = SOPHIA_JUMPING_RIGHT;
		}
		else {
			StateName = SOPHIA_JUMPING_LEFT;
		}
		player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
	}
	else if (player->allow[JASON]) {
		playerSmall->vy = -JASON_JUMP_SPEED_Y;
		playerSmall->IsJumping = true;
		if (playerSmall->nx > 0) {
			StateName = JASON_JUMPING_RIGHT;
		}
		else {
			StateName = JASON_JUMPING_LEFT;
		}
		playerSmall->stateBoundingBox = JASON_BOUNDING_BOX;
	}
}

PlayerJumpingState::~PlayerJumpingState() {

}

void PlayerJumpingState::Update() {
	if (player->allow[SOPHIA]) {
		if (player->vy > 0) {
			player->ChangeAnimation(new PlayerFallingState(), NORMAL);
			return;
		}
	}
	else if (player->allow[JASON]) {
		if (playerSmall->vy > 0) {
			playerSmall->ChangeAnimation(new PlayerFallingState());
			return;
		}
	}
	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		if (player->allow[SOPHIA]) {
			player->nx = 1;
			player->ChangeAnimation(new PlayerJumpingMovingState(), NORMAL);
		}
		else if (player->allow[JASON]) {
			playerSmall->nx = 1;
			playerSmall->ChangeAnimation(new PlayerJumpingMovingState());
		}
	}
	else if (keyCode[DIK_LEFT]) {
		if (player->allow[SOPHIA]) {
			player->nx = -1;
			player->ChangeAnimation(new PlayerJumpingMovingState(), NORMAL);
		}
		else if (player->allow[JASON]) {
			playerSmall->nx = -1;
			playerSmall->ChangeAnimation(new PlayerJumpingMovingState());
		}
	}
	else if (keyCode[DIK_UP]) {
		if(player->allow[SOPHIA])
			player->ChangeAnimation(new PlayerUpwardState(), NORMAL);
	}
}

