#include "PlayerJumpingState.h"
#include "PlayerJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"
#include "PlayerUpwardJumpingState.h"

PlayerJumpingState::PlayerJumpingState() {
	//player->allow[JUMPING] = false;
	player->renderOneFrame = true;
	if (!player->IsJumping) {
		player->vy = -SOPHIA_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		StateName = JUMPING_RIGHT;
	}
	else {
		StateName = JUMPING_LEFT;
	}
	player->stateBoundingBox = SOPHIA_BOUNDING_BOX;
}

PlayerJumpingState::~PlayerJumpingState() {

}

void PlayerJumpingState::Update() {
	if (player->vy > 0) {
		player->ChangeAnimation(new PlayerFallingState(), BACK_TO_NORMAL);
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerJumpingMovingState(), BACK_TO_NORMAL);
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerJumpingMovingState(), BACK_TO_NORMAL);
	}
	else if (keyCode[DIK_UP]) {
		player->ChangeAnimation(new PlayerUpwardJumpingState(), BACK_TO_NORMAL);
	}
}

