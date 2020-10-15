#include "PlayerUpwardJumpingMovingState.h"
#include "PlayerUpwardJumpingState.h"
#include "PlayerUpwardState.h"

PlayerUpwardJumpingMovingState::PlayerUpwardJumpingMovingState() {

	player->IsUp = true;

	if (!player->IsJumping) {
		player->vy = -CAR_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		player->vx = CAR_MOVING_SPEED;
		StateName = UPWARD_JUMPING_MOVING_RIGHT;
	}
	else {
		player->vx = -CAR_MOVING_SPEED;
		StateName = UPWARD_JUMPING_MOVING_LEFT;
	}
	player->stateBoundingBox = CAR_UP_BOUNDING_BOX;
}

PlayerUpwardJumpingMovingState::~PlayerUpwardJumpingMovingState() {

}

void PlayerUpwardJumpingMovingState::Update() {
	if (!player->IsJumping) {
		player->ChangeAnimation(new PlayerUpwardState());
		player->y = player->y + (CAR_UP_BBOX_HEIGHT - CAR_BBOX_HEIGHT);
		return;
	}
	this->HandleKeyboard();
}

void PlayerUpwardJumpingMovingState::HandleKeyboard() {
	
}