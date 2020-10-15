#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerUpwardJumpingState.h"

PlayerUpwardJumpingState::PlayerUpwardJumpingState() {

	player->IsUp = true;

	if (!player->IsJumping) {
		player->vy = -CAR_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		StateName = UPWARD_JUMPING_RIGHT;
	}
	else {
		StateName = UPWARD_JUMPING_LEFT;
	}
	player->stateBoundingBox = CAR_UP_BOUNDING_BOX;
}

PlayerUpwardJumpingState::~PlayerUpwardJumpingState() {

}

void PlayerUpwardJumpingState::Update() {
	this->HandleKeyboard();
}

void PlayerUpwardJumpingState::HandleKeyboard() {
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeAnimation(new PlayerUpwardJumpingMovingState());
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeAnimation(new PlayerUpwardJumpingMovingState());
	}
}