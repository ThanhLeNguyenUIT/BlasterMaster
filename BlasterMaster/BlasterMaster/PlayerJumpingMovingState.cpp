#include "PlayerJumpingMovingState.h"
#include "PlayerMovingState.h"
#include "PlayerFallingState.h"
#include "PlayerFallingMovingState.h"

PlayerJumpingMovingState::PlayerJumpingMovingState() {

	player->renderOneFrame = false;

	if (!player->IsJumping) {
		player->vy = -CAR_JUMPING_SPEED_Y;
	}
	player->IsJumping = true;
	if (player->nx > 0) {
		player->vx = CAR_MOVING_SPEED;
		StateName = JUMPING_MOVING_RIGHT;
	}
	else {
		player->vx = -CAR_MOVING_SPEED;
		StateName = JUMPING_MOVING_LEFT;
	}
	player->stateBoundingBox = CAR_BOUNDING_BOX;
}

PlayerJumpingMovingState::~PlayerJumpingMovingState() {

}

void PlayerJumpingMovingState::Update() {
	if (player->vy > 0) {
		player->ChangeAnimation(new PlayerFallingMovingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingMovingState::HandleKeyboard() {
	
}